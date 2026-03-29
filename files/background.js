// background.js — Service Worker
// Handles all GitHub API communication.
// Content scripts send messages here; we do the actual push.

chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
  if (message.type === "PUSH_TO_GITHUB") {
    pushToGitHub(message.payload)
      .then((result) => sendResponse({ success: true, url: result.url }))
      .catch((err) => sendResponse({ success: false, error: err.message }));
    return true; // keeps the message channel open for async response
  }
});

/**
 * Push a solved problem to the user's GitHub repo.
 * @param {Object} payload
 * @param {string} payload.platform   - "LeetCode" | "GeeksForGeeks" | "Codeforces"
 * @param {string} payload.title      - Problem title, e.g. "Two Sum"
 * @param {string} payload.slug       - URL-safe slug, e.g. "two-sum"
 * @param {string} payload.number     - Problem number/ID, e.g. "1"
 * @param {string} payload.difficulty - "Easy" | "Medium" | "Hard"
 * @param {string} payload.code       - The accepted solution code
 * @param {string} payload.language   - Language slug, e.g. "cpp", "python3"
 * @param {string} payload.notes      - Optional: problem description snippet
 */
async function pushToGitHub(payload) {
  const config = await getConfig();

  if (!config.token || !config.username || !config.repo) {
    throw new Error("GitHub credentials not configured. Open the extension popup.");
  }

  const ext = languageToExtension(payload.language);
  const safeTitle = sanitizeFilename(payload.title);
  const number = payload.number ? `${payload.number}-` : "";
  const difficulty = payload.difficulty || "Unknown";

  // File path inside the repo:
  // e.g. LeetCode/Easy/0001-Two-Sum/solution.cpp
  const filePath = `${payload.platform}/${difficulty}/${number}${safeTitle}/solution${ext}`;

  const readmeContent = buildReadme(payload);
  const readmePath = `${payload.platform}/${difficulty}/${number}${safeTitle}/README.md`;

  const commitMessage = `✅ ${payload.platform} #${payload.number || ""} - ${payload.title} [${difficulty}]`;

  // Push solution file
  await upsertFile(config, filePath, payload.code, commitMessage);

  // Push README with problem details
  await upsertFile(config, readmePath, readmeContent, `docs: add README for ${payload.title}`);

  const url = `https://github.com/${config.username}/${config.repo}/blob/main/${filePath}`;

  // Fire a browser notification
  chrome.notifications.create({
    type: "basic",
    iconUrl: "icons/icon128.png",
    title: "✅ Pushed to GitHub!",
    message: `${payload.title} (${difficulty}) → ${config.repo}`,
  });

  return { url };
}

/**
 * Create or update a file in GitHub via the Contents API.
 */
async function upsertFile(config, path, content, message) {
  const apiUrl = `https://api.github.com/repos/${config.username}/${config.repo}/contents/${path}`;
  const headers = {
    Authorization: `token ${config.token}`,
    "Content-Type": "application/json",
    Accept: "application/vnd.github.v3+json",
  };

  // Check if file already exists (need its SHA to update)
  let sha = null;
  try {
    const getRes = await fetch(apiUrl, { headers });
    if (getRes.ok) {
      const existing = await getRes.json();
      sha = existing.sha;
    }
  } catch (_) {
    // File doesn't exist yet — that's fine
  }

  const body = {
    message,
    content: btoa(unescape(encodeURIComponent(content))), // UTF-8 safe base64
    ...(sha && { sha }), // include sha only if updating
  };

  const res = await fetch(apiUrl, {
    method: "PUT",
    headers,
    body: JSON.stringify(body),
  });

  if (!res.ok) {
    const err = await res.json();
    throw new Error(`GitHub API error: ${err.message}`);
  }

  return res.json();
}

/**
 * Build a simple README.md for the problem.
 */
function buildReadme(payload) {
  const date = new Date().toISOString().split("T")[0];
  return `# ${payload.number ? `#${payload.number} - ` : ""}${payload.title}

**Platform:** ${payload.platform}  
**Difficulty:** ${payload.difficulty || "N/A"}  
**Language:** ${payload.language}  
**Solved On:** ${date}  

${payload.url ? `**Problem Link:** [Open on ${payload.platform}](${payload.url})` : ""}

${payload.notes ? `## Problem Description\n\n${payload.notes}` : ""}

## Solution

See \`solution${languageToExtension(payload.language)}\`
`;
}

/** Map language slugs to file extensions */
function languageToExtension(lang) {
  const map = {
    cpp: ".cpp",
    "c++": ".cpp",
    c: ".c",
    java: ".java",
    python: ".py",
    python3: ".py",
    javascript: ".js",
    typescript: ".ts",
    go: ".go",
    rust: ".rs",
    kotlin: ".kt",
    swift: ".swift",
    csharp: ".cs",
    ruby: ".rb",
    scala: ".scala",
    php: ".php",
  };
  return map[lang?.toLowerCase()] || ".txt";
}

/** Make a string safe for use as a folder/file name */
function sanitizeFilename(name) {
  return name
    .replace(/[^a-zA-Z0-9\s-]/g, "")
    .trim()
    .replace(/\s+/g, "-");
}

/** Fetch saved config from chrome.storage */
async function getConfig() {
  return new Promise((resolve) => {
    chrome.storage.sync.get(
      ["githubToken", "githubUsername", "githubRepo"],
      (data) => {
        resolve({
          token: data.githubToken || "",
          username: data.githubUsername || "",
          repo: data.githubRepo || "DSA-Solutions",
        });
      }
    );
  });
}
