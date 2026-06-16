class Solution {
public:
    bool isPalindrome(string s) {
        int i = 0;
        int j = s.length() - 1;
        while (i < j) {
            if (s[i] != s[j])
                return false;
            i++;
            j--;
        }
        return true;
    }
    void solve(vector<vector<string>>& st, string& s, vector<string>& ans,
               int index) {
        if (index == s.length()) {
            st.push_back(ans);
            return;
        }
        string temp = "";
        for (int i = index; i < s.length(); i++) {
            temp += s[i];
            if (isPalindrome(temp)) {
                ans.push_back(temp);
                solve(st, s, ans, i + 1);
                ans.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> st;
        vector<string> ans;
        solve(st, s, ans, 0);
        return st;
    }
};