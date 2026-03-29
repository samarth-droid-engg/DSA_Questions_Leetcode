// content_cf.js
// Runs on codeforces.com — detects accepted submissions.
// CF shows verdict on the submissions page; we watch for "Accepted".

(function () {
  "use strict";
  if (window.__dsaPusherCFLoaded) return;
  window.__dsaPusherCFLoaded = true;

  console.log("[DSA Pusher] Codeforces content script loaded.");

  // Method 1: If we're on the submissions list page, watch for "Accepted" verdict
  // Method 2: On problem page, intercept the submit form result

  const observer = new MutationObserver(() => {
    // CF submission verdict cells
    const verdicts = document.querySelectorAll(".verdict-accepted");
    if (verdicts.length > 0) {
      // Find the most recent one (first row)
      const row = verdicts[0].closest("tr");
      if (row && !row.dataset.dsaPusherHandled) {
        row.dataset.dsaPusherHandled = "true";
        handleAccepted(row);
      }
    }
  });

  observer.observe(document.body, { childList: true, subtree: true });

  function handleAccepted(row) {
    console.log("[DSA Pusher] ✅ CF Accepted!");

    // Extract info from the submission row
    // CF table columns: #, When, Who, Problem, Lang, Verdict, Time, Memory
    const cells = row.querySelectorAll("td");
    const problemCell = cells[3];
    const langCell = cells[4];

    const problemLink = problemCell?.querySelector("a");
    const title = problemLink?.textContent?.trim() || "Unknown Problem";
    const problemHref = problemLink?.href || "";
    const language = langCell?.textContent?.trim().toLowerCase() || "cpp";

    // Fetch the source code from the submission page
    // CF shows source via submission ID
    const submissionId = cells[0]?.textContent?.trim();
    if (!submissionId) return;

    fetchCFSubmissionCode(submissionId, problemHref).then((code) => {
      const payload = {
        platform: "Codeforces",
        title,
        slug: title.toLowerCase().replace(/\s+/g, "-"),
        number: extractCFProblemNumber(problemHref),
        difficulty: "Unknown", // CF doesn't show difficulty directly
        language: normalizeCFLang(language),
        code,
        url: problemHref,
        notes: "",
      };

      chrome.runtime.sendMessage({ type: "PUSH_TO_GITHUB", payload }, (res) => {
        if (res?.success) showToast("🚀 Pushed to GitHub!");
        else showToast("❌ Push failed: " + (res?.error || "Unknown"));
      });
    });
  }

  async function fetchCFSubmissionCode(submissionId, problemHref) {
    // Extract contest ID from problem href
    const match = problemHref.match(/\/contest\/(\d+)\//);
    const contestId = match?.[1];
    if (!contestId) return "// Could not fetch code.";

    try {
      const url = `https://codeforces.com/contest/${contestId}/submission/${submissionId}`;
      const res = await fetch(url, { credentials: "include" });
      const html = await res.text();
      const parser = new DOMParser();
      const doc = parser.parseFromString(html, "text/html");
      // CF shows the code in a <pre id="program-source-text">
      const pre = doc.querySelector("#program-source-text");
      return pre?.textContent || "// Could not extract code.";
    } catch (_) {
      return "// Could not extract code.";
    }
  }

  function extractCFProblemNumber(href) {
    const match = href.match(/\/problem\/([A-Z0-9]+)/i);
    return match?.[1] || "";
  }

  function normalizeCFLang(lang) {
    if (/c\+\+/i.test(lang)) return "cpp";
    if (/java/i.test(lang)) return "java";
    if (/python/i.test(lang)) return "python3";
    if (/javascript/i.test(lang)) return "javascript";
    return lang.replace(/\s+/g, "").toLowerCase();
  }

  function showToast(message) {
    const existing = document.getElementById("dsa-pusher-toast");
    if (existing) existing.remove();
    const toast = document.createElement("div");
    toast.id = "dsa-pusher-toast";
    toast.textContent = message;
    toast.style.cssText = `
      position:fixed; bottom:24px; right:24px;
      background:#1a1a2e; color:#e2e8f0;
      padding:12px 20px; border-radius:8px;
      font-family:monospace; font-size:14px;
      z-index:999999; box-shadow:0 4px 20px rgba(0,0,0,0.4);
      border-left:3px solid #22c55e; max-width:340px;
    `;
    document.body.appendChild(toast);
    setTimeout(() => toast.remove(), 4000);
  }
})();
