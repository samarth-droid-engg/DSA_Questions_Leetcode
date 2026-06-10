class Solution {
public:
    void solve(vector<vector<int>>& vt, vector<int>& candidates, vector<int>& v,
               int target, int index, int sum) {
        if (sum == target) {
            vt.push_back(v);
            return;
        }
        if (sum > target || index >= candidates.size())
            return;
        for (int i = index; i < candidates.size(); i++) {
            if (i > index && candidates[i] == candidates[i - 1])
                continue;
            v.push_back(candidates[i]);
            solve(vt, candidates, v, target, i + 1, sum + candidates[i]);
            v.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> vt;
        vector<int> v;
        sort(candidates.begin(), candidates.end());
        solve(vt, candidates, v, target, 0, 0);
        return vt;
    }
};