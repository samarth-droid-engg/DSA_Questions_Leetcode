class Solution {
public:
    void solve(vector<string>& st, const string& digits, string& ans,
               const unordered_map<int, string>& mp, int index) {
        if (index == digits.length()) {
            st.push_back(ans);
            return;
        }
        int n = digits[index] - '0';
        const string& p = mp.at(n);
        for (int i = 0; i < p.length(); i++) {
            ans += p[i];
            solve(st, digits, ans, mp, index + 1);
            ans.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return {};
        unordered_map<int, string> mp;
        char ch = 'a';
        for (int i = 2; i <= 9; i++) {
            string s = "";
            s += ch;
            if (i == 7 || i == 9) {
                for (int j = 0; j < 3; j++) {
                    s = s + (++ch);
                }
            } else {
                for (int j = 0; j < 2; j++) {
                    s = s + (++ch);
                }
            }
            mp[i] = s;
            ch++;
        }
        vector<string> st;
        string ans = "";
        solve(st, digits, ans, mp, 0);
        return st;
    }
};