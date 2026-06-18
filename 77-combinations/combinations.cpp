class Solution {
public:
    void solve(vector<vector<int>>& vt, vector<int>& v, int& n, int& k,
               int index) {
        if (v.size() == k) {
            vt.push_back(v);
            return;
        }
        for (int i = index; i <= n; i++) {
            v.push_back(i);
            solve(vt, v, n, k, i + 1);
            v.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> vt;
        vector<int> v;
        solve(vt, v, n, k, 1);
        return vt;
    }
};