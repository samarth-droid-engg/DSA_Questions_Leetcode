class Solution {
public:
    void solve(vector<int>& nums, vector<vector<int>>& vt, int index) {
        if (index == nums.size()) {
            vt.push_back(nums);
            return;
        }
        for (int i = index; i < nums.size(); i++) {
            swap(nums[i], nums[index]);
            solve(nums, vt, index + 1);
            swap(nums[i], nums[index]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> vt;
        solve(nums, vt, 0);
        return vt;
    }
};