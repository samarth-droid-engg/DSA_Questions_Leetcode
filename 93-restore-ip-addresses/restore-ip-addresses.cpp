class Solution {
public:
    vector<string> ans;
    void solve(string s, int index, int parts, string curr) {
        if (parts == 4) {
            if (index == s.length()) {
                curr.pop_back();
                ans.push_back(curr);
            }
            return;
        }
        for (int i = 0; i < 3; i++) {
            if (index + i + 1 > s.size()) {
                break;
            }
            string part = s.substr(index, i + 1);
            if (part.size() > 1 && part[0] == '0') {
                break;
            }
            if (stoi(part) > 255)
                break;
            solve(s, index + i + 1, parts + 1, curr + part + '.');
        }
    }
    vector<string> restoreIpAddresses(string s) {
        if (s.length() > 12 || s.length() < 4)
            return {};
        solve(s, 0, 0, "");
        return ans;
    }
};