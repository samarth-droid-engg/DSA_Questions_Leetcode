// content_gfg.js
// Runs on geeksforgeeks.org — detects accepted submissions.

(function () {
  "use strict";
  if (window.__dsaPusherGFGLoaded) return;
  window.__dsaPusherGFGLoaded = true;

  console.log("[DSA Pusher] GFG content script loaded.");

  // GFG shows a result div after submission — watch for DOM changes
  const observer = new MutationObserver(() => {
    // GFG shows "Problem Solved Successfully" or similar text
    const resultEl =
      document.querySelector(".problems_header_feedback__C_sou") ||
      document.querySelector('[class*="feedback"]') ||
      document.querySelector(".result_box");

    if (resultEl && resultEl.textContent.toLowerCase().includes("success")) {
      observer.disconnect(); // stop watching after first detection
      handleAccepted();
    }
  });

  observer.observe(document.body, { childList: true, subtree: true });

  function handleAccepted() {
    console.log("[DSA Pusher] ✅ GFG Accepted!");

    const title =
      document.querySelector(".problems_header_description__t_MIg h3")
        ?.textContent ||
      document.title.replace("- GeeksForGeeks", "").trim();

    const difficulty =
      document.querySelector(".difficulty_level")?.textContent?.trim() ||
      "Unknown";

    // GFG uses CodeMirror
    let code = "// Could not extract code.";
    try {
      const cm = document.querySelector(".CodeMirror")?.CodeMirror;
      if (cm) code = cm.getValue();
    } catch (_) {}

    const langEl = document.querySelector(".active_lang") ||
      document.querySelector('[class*="language"]');
    const language = langEl?.textContent?.trim().toLowerCase() || "cpp";

    const payload = {
      platform: "GeeksForGeeks",
      title,
      slug: title.toLowerCase().replace(/\s+/g, "-"),
      number: "",
      difficulty: normalizeDifficulty(difficulty),
      language,
      code,
      url: window.location.href,
      notes: "",
    };

    chrome.runtime.sendMessage({ type: "PUSH_TO_GITHUB", payload }, (res) => {
      if (res?.success) showToast("🚀 Pushed to GitHub!");
      else showToast("❌ Push failed: " + (res?.error || "Unknown"));
    });
  }

  function normalizeDifficulty(d) {
    if (/easy/i.test(d)) return "Easy";
    if (/medium/i.test(d)) return "Medium";
    if (/hard/i.test(d)) return "Hard";
    return "Unknown";
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
