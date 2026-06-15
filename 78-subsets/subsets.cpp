class Solution {
public:
    void solve(vector<int>& nums, vector<vector<int>>& vt, vector<int>& ans,
               int index) {
        if (index == nums.size()) {
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
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> vt;
        vector<int> ans;
        solve(nums, vt, ans, 0);
        return vt;
    }
};