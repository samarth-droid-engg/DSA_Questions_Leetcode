class Solution {
public:
    void solve(vector<int>& nums, vector<vector<int>>& vt, int index) {
        if (index == nums.size()) {
            vt.push_back(nums);
            return;
        }
        unordered_map<int, bool> mp;
        for (int i = index; i < nums.size(); i++) {
            if (mp.find(nums[i]) != mp.end())
                continue;
            mp[nums[i]] = true;
            swap(nums[i], nums[index]);
            solve(nums, vt, index + 1);
            swap(nums[i], nums[index]);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> vt;
        solve(nums, vt, 0);
        return vt;
    }
};