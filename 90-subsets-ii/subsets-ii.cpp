class Solution {
public:
    void solve(vector<int>& nums, vector<vector<int>>& vt, vector<int>& ans,
               int index) {
        if (index == nums.size()) {
            if (find(vt.begin(), vt.end(), ans) == vt.end())
                vt.push_back(ans);
            return;
        }
        // exlude
        solve(nums, vt, ans, index + 1);
        // include
        ans.push_back(nums[index]);
        solve(nums, vt, ans, index + 1);
        ans.pop_back();
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> vt;
        vector<int> ans;
        sort(nums.begin(), nums.end());
        solve(nums, vt, ans, 0);
        return vt;
    }
};