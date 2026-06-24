class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size();
        int sumM = nums[0], summ = nums[0], maxSum = nums[0], minSum = nums[0];
        for (int i = 1; i < n; i++) {
            sumM = max(sumM + nums[i], nums[i]);
            summ = min(summ + nums[i], nums[i]);
            minSum = min(minSum, summ);
            maxSum = max(maxSum, sumM);
        }
        return (abs(maxSum) > abs(minSum)) ? abs(maxSum) : abs(minSum);
    }
};