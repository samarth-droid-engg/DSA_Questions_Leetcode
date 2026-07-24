class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        bool notC = false;
        string ans = "", st = "";
        for (int i = n - 1; i >= 0; i--) {
            if (!notC) {
                st = "";
                notC = 1;
            }
            if (s[i] == ' ') {
                if (st.size() != 0) {
                    reverse(st.begin(), st.end());
                    ans += st;
                    ans.push_back(' ');
                    notC = 0;
                }
                continue;
            }
            cout << s[i] << endl;
            st.push_back(s[i]);
            if (i == 0 && !st.empty()) {
                reverse(st.begin(), st.end());
                ans += st;
            }
        }
        if (!ans.empty() && ans.back() == ' ') {
            ans.pop_back();
        }
        return ans;
    }
};