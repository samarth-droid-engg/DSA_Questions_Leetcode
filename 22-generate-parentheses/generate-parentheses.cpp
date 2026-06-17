class Solution {
public:
    void solve(vector<string>& st, string& ans, const int& n, int obrC,
               int cbrC) {
        if (obrC == n && cbrC == n) {
            st.push_back(ans);
            return;
        }
        if (obrC > n || cbrC > n) {
            return;
        }
        if (cbrC > obrC) {
            return;
        }
        // exclude(closed)
        ans += ')';
        solve(st, ans, n, obrC, cbrC + 1);
        ans.pop_back();
        // include(open)
        ans += '(';
        solve(st, ans, n, obrC + 1, cbrC);
        ans.pop_back();
    }
    vector<string> generateParenthesis(int n) {
        vector<string> st;
        string ans = "";
        // openBracket count and closedBracket count
        solve(st, ans, n, 0, 0);
        return st;
    }
};