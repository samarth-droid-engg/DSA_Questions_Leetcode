# 🚀 DSA GitHub Pusher

A Chrome/Edge browser extension that **automatically pushes your accepted DSA solutions to GitHub** the moment you get an "Accepted" verdict on LeetCode, GeeksForGeeks, or Codeforces.

No manual copy-paste. No forgetting to commit. Just solve and ship.

---

## ✅ Supported Platforms

| Platform | Detection Method | Code Extraction |
|---|---|---|
| LeetCode | Fetch interception (API) | Submission response + Monaco editor |
| GeeksForGeeks | DOM mutation observer | CodeMirror editor |
| Codeforces | DOM mutation observer | Submission detail page |

---

## 📁 Repo Structure (auto-generated)

```
your-dsa-repo/
├── LeetCode/
│   ├── Easy/
│   │   └── 0001-Two-Sum/
│   │       ├── solution.cpp
│   │       └── README.md
│   ├── Medium/
│   └── Hard/
├── GeeksForGeeks/
└── Codeforces/
```

---

## 🔧 Setup Steps

### Step 1 — Create a GitHub Repository

1. Go to [github.com/new](https://github.com/new)
2. Name it `DSA-Solutions` (or anything you prefer)
3. Set it to **Public** (so recruiters can see it)
4. Initialize with a README ✅
5. Click **Create repository**

---

### Step 2 — Generate a GitHub Personal Access Token

1. Go to → [github.com/settings/tokens/new](https://github.com/settings/tokens/new?scopes=repo&description=DSA-GitHub-Pusher)
2. Give it a name: `DSA-GitHub-Pusher`
3. Set expiration: `No expiration` (or 1 year)
4. Under **Scopes**, check: ✅ `repo` (full control of private repos)
5. Click **Generate token**
6. **Copy the token immediately** — you won't see it again!

> ⚠️ Keep your token secret. Don't commit it anywhere.

---

### Step 3 — Load the Extension in Chrome

1. Open Chrome and go to `chrome://extensions/`
2. Enable **Developer mode** (toggle, top-right)
3. Click **Load unpacked**
4. Select the `dsa-github-pusher/` folder (this folder)
5. The extension icon (🚀) should appear in your toolbar

---

### Step 4 — Configure the Extension

1. Click the 🚀 extension icon
2. Fill in:
   - **GitHub Username**: your GitHub username
   - **Repository Name**: `DSA-Solutions` (or whatever you named it)
   - **Personal Access Token**: paste the token from Step 2
3. Select which platforms you want active
4. Click **Save Configuration** — it validates your token live

---

### Step 5 — Solve & Auto-Push!

1. Go to LeetCode (or GFG / Codeforces)
2. Solve a problem and submit
3. When verdict is **Accepted**:
   - A green toast appears on the page ✅
   - Your solution is pushed to GitHub automatically
   - A browser notification fires
4. Check your repo — the file is there 🎉

---

## 🛠️ Development & Customization

### Folder structure

```
dsa-github-pusher/
├── manifest.json          # Extension config (MV3)
├── background.js          # Service worker — GitHub API calls
├── content_leetcode.js    # LeetCode detection + code extraction
├── content_gfg.js         # GeeksForGeeks detection
├── content_cf.js          # Codeforces detection
├── popup.html             # Settings UI
├── popup.js               # Settings logic
└── icons/
    ├── icon48.png
    └── icon128.png
```

### Adding a new platform

1. Create `content_yourplatform.js`
2. Detect acceptance (intercept fetch, or watch DOM)
3. Build a `payload` object matching the structure in `background.js`
4. Call `chrome.runtime.sendMessage({ type: "PUSH_TO_GITHUB", payload })`
5. Add the content script to `manifest.json` under `content_scripts`

---

## 🔐 Security Notes

- Your GitHub token is stored in `chrome.storage.sync` — it's encrypted and tied to your Chrome profile
- Token is **never** sent anywhere except `api.github.com`
- You can revoke the token anytime at [github.com/settings/tokens](https://github.com/settings/tokens)

---

## 📌 Icons

The extension needs icons. You can:
- Create simple 48×48 and 128×128 PNG files named `icon48.png` and `icon128.png` in the `icons/` folder
- Or grab free ones from [flaticon.com](https://flaticon.com) (search "code" or "github")
- Or use this one-liner to create placeholder icons with ImageMagick:
  ```bash
  mkdir -p icons
  # Install ImageMagick if needed: sudo apt install imagemagick
  convert -size 128x128 xc:#238636 -fill white -gravity Center \
    -pointsize 60 -annotate 0 "🚀" icons/icon128.png
  convert -size 48x48 xc:#238636 icons/icon48.png
  ```

---

Built with ❤️ — No third-party dependencies. Pure browser extension APIs + GitHub REST API.
