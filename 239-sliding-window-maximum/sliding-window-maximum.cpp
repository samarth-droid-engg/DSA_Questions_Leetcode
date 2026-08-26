class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> dq;
        vector<int> ans;
        for (int i = 0; i < k; i++) {
            if (dq.empty())
                dq.push_back(i);
            else {
                while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                    dq.pop_back();
                }
                dq.push_back(i);
            }
        }
        int element = nums[dq.front()];
        ans.push_back(element);
        for (int i = k; i < n; i++) {
            if (!dq.empty() && i - dq.front() >= k)
                dq.pop_front();
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
            int element = nums[dq.front()];
            ans.push_back(element);
        }
        return ans;
    }
};