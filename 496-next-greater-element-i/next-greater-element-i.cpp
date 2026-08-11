class Solution {
public:
    unordered_map<int, int> nextGreater(vector<int> nums) {
        unordered_map<int, int> mp;
        stack<int> st;
        int n = nums.size();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && st.top() <= nums[i]) {
                st.pop();
            }
            if (st.empty()) {
                st.push(-1);
            }
            mp[nums[i]] = st.top();

            st.push(nums[i]);
        }
        return mp;
    }
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        auto st = nextGreater(nums2);
        vector<int> vt;
        for (int i = 0; i < nums1.size(); i++) {
            if (st.find(nums1[i]) != st.end()) {
                vt.push_back(st[nums1[i]]);
            }
        }
        return vt;
    }
};