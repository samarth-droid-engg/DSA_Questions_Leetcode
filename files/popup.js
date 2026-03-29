// popup.js

document.addEventListener("DOMContentLoaded", () => {
  const usernameEl = document.getElementById("username");
  const repoEl = document.getElementById("repo");
  const tokenEl = document.getElementById("token");
  const saveBtn = document.getElementById("saveBtn");
  const toggleBtn = document.getElementById("toggleToken");
  const toast = document.getElementById("toast");
  const statusBar = document.getElementById("statusBar");
  const statusText = document.getElementById("statusText");

  // ── Load saved config ──────────────────────────────────────────────────────
  chrome.storage.sync.get(
    ["githubToken", "githubUsername", "githubRepo", "platforms", "stats"],
    (data) => {
      usernameEl.value = data.githubUsername || "";
      repoEl.value = data.githubRepo || "DSA-Solutions";
      tokenEl.value = data.githubToken || "";

      // Platform toggles
      const platforms = data.platforms || {
        leetcode: true,
        gfg: true,
        codeforces: true,
      };
      document.querySelectorAll(".platform-toggle").forEach((el) => {
        const key = el.dataset.platform;
        if (platforms[key] === false) el.classList.remove("active");
      });

      // Stats
      const stats = data.stats || { total: 0, today: 0, streak: 0 };
      document.getElementById("statTotal").textContent = stats.total;
      document.getElementById("statToday").textContent = stats.today;
      document.getElementById("statStreak").textContent = stats.streak;

      // Status
      if (!data.githubToken || !data.githubUsername) {
        setStatus("error", "⚠ Configure your GitHub credentials below");
      }
    }
  );

  // ── Save config ────────────────────────────────────────────────────────────
  saveBtn.addEventListener("click", async () => {
    const username = usernameEl.value.trim();
    const repo = repoEl.value.trim();
    const token = tokenEl.value.trim();

    if (!username || !repo || !token) {
      showToast("All fields are required", "err");
      return;
    }

    // Validate token by hitting GitHub API
    saveBtn.textContent = "Verifying…";
    saveBtn.disabled = true;

    try {
      const res = await fetch("https://api.github.com/user", {
        headers: { Authorization: `token ${token}` },
      });

      if (!res.ok) throw new Error("Invalid token");

      const user = await res.json();
      if (user.login.toLowerCase() !== username.toLowerCase()) {
        throw new Error(`Token belongs to "${user.login}", not "${username}"`);
      }
    } catch (e) {
      showToast("❌ " + e.message, "err");
      saveBtn.textContent = "Save Configuration";
      saveBtn.disabled = false;
      return;
    }

    // Collect platform toggles
    const platforms = {};
    document.querySelectorAll(".platform-toggle").forEach((el) => {
      platforms[el.dataset.platform] = el.classList.contains("active");
    });

    chrome.storage.sync.set(
      { githubToken: token, githubUsername: username, githubRepo: repo, platforms },
      () => {
        showToast("✅ Saved! Extension is active.", "ok");
        setStatus("ok", `Pushing to ${username}/${repo}`);
        saveBtn.textContent = "Save Configuration";
        saveBtn.disabled = false;
      }
    );
  });

  // ── Token visibility toggle ────────────────────────────────────────────────
  toggleBtn.addEventListener("click", () => {
    tokenEl.type = tokenEl.type === "password" ? "text" : "password";
    toggleBtn.textContent = tokenEl.type === "password" ? "👁" : "🙈";
  });

  // ── Platform toggle click ──────────────────────────────────────────────────
  document.querySelectorAll(".platform-toggle").forEach((el) => {
    el.addEventListener("click", () => el.classList.toggle("active"));
  });

  // ── Helpers ────────────────────────────────────────────────────────────────
  function showToast(message, type = "ok") {
    toast.textContent = message;
    toast.className = `toast ${type} show`;
    setTimeout(() => toast.classList.remove("show"), 3000);
  }

  function setStatus(type, message) {
    statusBar.className = `status-bar ${type === "error" ? "error" : ""}`;
    statusText.textContent = message;
  }
});
