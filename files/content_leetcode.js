// content_leetcode.js
// Runs on leetcode.com pages.
// Intercepts fetch calls to detect when a submission is "Accepted",
// then grabs the code + problem metadata and sends it to background.js.

(function () {
  "use strict";

  // Prevent double-injection
  if (window.__dsaPusherLeetcodeLoaded) return;
  window.__dsaPusherLeetcodeLoaded = true;

  console.log("[DSA Pusher] LeetCode content script loaded.");

  // ─── Intercept fetch ───────────────────────────────────────────────────────
  const originalFetch = window.fetch;

  window.fetch = async function (...args) {
    const response = await originalFetch.apply(this, args);
    const url = typeof args[0] === "string" ? args[0] : args[0]?.url || "";

    // LeetCode polls this endpoint to check submission result
    if (url.includes("/submissions/detail/") && url.includes("/check")) {
      const clone = response.clone();
      clone
        .json()
        .then((data) => {
          if (data?.status_msg === "Accepted") {
            console.log("[DSA Pusher] ✅ Accepted submission detected!", data);
            handleAcceptedSubmission(data, url);
          }
        })
        .catch(() => {}); // silently ignore parse errors
    }

    return response;
  };

  // ─── Also intercept XMLHttpRequest (fallback) ──────────────────────────────
  const OrigXHR = window.XMLHttpRequest;
  window.XMLHttpRequest = function () {
    const xhr = new OrigXHR();
    const originalOpen = xhr.open.bind(xhr);
    let requestUrl = "";

    xhr.open = function (method, url, ...rest) {
      requestUrl = url;
      return originalOpen(method, url, ...rest);
    };

    xhr.addEventListener("load", function () {
      if (
        requestUrl.includes("/submissions/detail/") &&
        requestUrl.includes("/check")
      ) {
        try {
          const data = JSON.parse(xhr.responseText);
          if (data?.status_msg === "Accepted") {
            console.log("[DSA Pusher] ✅ Accepted (XHR)!", data);
            handleAcceptedSubmission(data, requestUrl);
          }
        } catch (_) {}
      }
    });

    return xhr;
  };

  // ─── Handle accepted submission ────────────────────────────────────────────
  function handleAcceptedSubmission(data, checkUrl) {
    // Extract submission ID from URL like /submissions/detail/123456789/check
    const match = checkUrl.match(/\/submissions\/detail\/(\d+)\//);
    const submissionId = match ? match[1] : null;

    // Get problem info from the current page URL
    // e.g. https://leetcode.com/problems/two-sum/
    const problemInfo = extractProblemInfoFromPage();

    const payload = {
      platform: "LeetCode",
      title: problemInfo.title,
      slug: problemInfo.slug,
      number: problemInfo.number,
      difficulty: problemInfo.difficulty,
      language: data.lang || "unknown",
      code: data.code || extractCodeFromEditor(),
      url: window.location.href,
      notes: problemInfo.description,
    };

    // If code isn't in the check response, fetch the submission detail
    if (!payload.code && submissionId) {
      fetchSubmissionCode(submissionId).then((code) => {
        payload.code = code;
        sendToBackground(payload);
      });
    } else {
      sendToBackground(payload);
    }
  }

  /**
   * Extract problem metadata from the page DOM.
   * LeetCode renders problem info in the page — we scrape it.
   */
  function extractProblemInfoFromPage() {
    const slug =
      window.location.pathname.match(/\/problems\/([^/]+)/)?.[1] || "unknown";

    // Problem title: look for the <title> tag or a heading
    let title =
      document.title
        .replace("- LeetCode", "")
        .replace(/^\d+\.\s*/, "")
        .trim() || slug;

    // Problem number: often in the title like "1. Two Sum"
    const numberMatch = document.title.match(/^(\d+)\./);
    const number = numberMatch ? numberMatch[1] : "";

    // Difficulty badge
    let difficulty = "Unknown";
    const difficultyEl =
      document.querySelector('[class*="text-difficulty-easy"]') ||
      document.querySelector('[class*="text-difficulty-medium"]') ||
      document.querySelector('[class*="text-difficulty-hard"]') ||
      document.querySelector(".text-olive") || // older LC
      document.querySelector(".text-yellow") ||
      document.querySelector(".text-pink");

    if (difficultyEl) {
      const text = difficultyEl.textContent.trim();
      if (text.match(/easy/i)) difficulty = "Easy";
      else if (text.match(/medium/i)) difficulty = "Medium";
      else if (text.match(/hard/i)) difficulty = "Hard";
    }

    // Try to get problem description (first 300 chars for README)
    let description = "";
    const descEl = document.querySelector('[data-track-load="description_content"]');
    if (descEl) {
      description = descEl.textContent.slice(0, 400).trim() + "...";
    }

    return { slug, title, number, difficulty, description };
  }

  /**
   * Try to grab code from the Monaco editor on the page.
   * This is a fallback if the check API doesn't include code.
   */
  function extractCodeFromEditor() {
    try {
      // Monaco exposes its models globally
      const models = window.monaco?.editor?.getModels();
      if (models && models.length > 0) {
        return models[models.length - 1].getValue();
      }
    } catch (_) {}

    // Fallback: read from CodeMirror
    try {
      const cmInstance = document.querySelector(".CodeMirror")?.CodeMirror;
      if (cmInstance) return cmInstance.getValue();
    } catch (_) {}

    return "// Could not extract code automatically. Please paste your solution.";
  }

  /**
   * Fetch the actual submission detail page to get the code
   * (used when the /check endpoint doesn't return code directly).
   */
  async function fetchSubmissionCode(submissionId) {
    try {
      const res = await originalFetch(
        `https://leetcode.com/submissions/detail/${submissionId}/`,
        { credentials: "include" }
      );
      const html = await res.text();
      // LC embeds submission data in a <script> tag as JSON
      const match = html.match(/submissionCode:\s*'(.*?)(?<!\\)',/s);
      if (match) {
        return decodeURIComponent(JSON.parse(`"${match[1]}"`));
      }
    } catch (_) {}
    return extractCodeFromEditor();
  }

  /** Send payload to background.js for GitHub push */
  function sendToBackground(payload) {
    if (!payload.code || payload.code.trim() === "") {
      console.warn("[DSA Pusher] No code found, skipping push.");
      return;
    }

    console.log("[DSA Pusher] Sending to background:", payload);
    chrome.runtime.sendMessage(
      { type: "PUSH_TO_GITHUB", payload },
      (response) => {
        if (chrome.runtime.lastError) {
          console.error("[DSA Pusher] Message error:", chrome.runtime.lastError);
          return;
        }
        if (response?.success) {
          console.log("[DSA Pusher] 🚀 Pushed to GitHub:", response.url);
          showToast("🚀 Solution pushed to GitHub!");
        } else {
          console.error("[DSA Pusher] Push failed:", response?.error);
          showToast("❌ Push failed: " + (response?.error || "Unknown error"));
        }
      }
    );
  }

  /** Show a small toast on the page so the user knows what happened */
  function showToast(message) {
    const existing = document.getElementById("dsa-pusher-toast");
    if (existing) existing.remove();

    const toast = document.createElement("div");
    toast.id = "dsa-pusher-toast";
    toast.textContent = message;
    toast.style.cssText = `
      position: fixed;
      bottom: 24px;
      right: 24px;
      background: #1a1a2e;
      color: #e2e8f0;
      padding: 12px 20px;
      border-radius: 8px;
      font-family: monospace;
      font-size: 14px;
      z-index: 999999;
      box-shadow: 0 4px 20px rgba(0,0,0,0.4);
      border-left: 3px solid #22c55e;
      max-width: 340px;
      transition: opacity 0.3s;
    `;
    document.body.appendChild(toast);
    setTimeout(() => {
      toast.style.opacity = "0";
      setTimeout(() => toast.remove(), 300);
    }, 4000);
  }
})();
