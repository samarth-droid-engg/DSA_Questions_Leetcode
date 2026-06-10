class Solution {
public:
    void solve(vector<vector<int>>& vt, vector<int>& candidates, vector<int>& v,
               int sum, int& target, int index) {
        if (index >= candidates.size())
            return;
        if (sum > target) {
            return;
        }
        if (sum == target) {
            vt.push_back(v);
            return;
        }
        for (int i = index; i < candidates.size(); i++) {
            v.push_back(candidates[i]);
            solve(vt, candidates, v, sum + candidates[i], target, i);
            v.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> vt;
        vector<int> v;
        solve(vt, candidates, v, 0, target, 0);
        return vt;
    }
};