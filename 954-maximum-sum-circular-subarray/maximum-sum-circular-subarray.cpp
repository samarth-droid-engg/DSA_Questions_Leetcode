class Solution {
public:
    int minSubarraySum(vector<int>& nums) {
        int n = nums.size();
        int sum = nums[0], minSum = nums[0];
        for (int i = 1; i < n; i++) {
            sum = min(sum + nums[i], nums[i]);
            minSum = min(minSum, sum);
        }
        return minSum;
    }
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = nums.size();
        // Calculate three sum: TotalSum, MinSubarraySum, MaxSubarraySum
        // Also calculate Circular sum using: TotalSum - minSubarraySum
        // (Assuming that circularone is maximum)
        int sum = 0;
        int totalSum = 0, maxSum = nums[0];
        for (int i = 0; i < n; i++) {
            totalSum += nums[i];
            sum = max(nums[i], sum + nums[i]);
            maxSum = max(maxSum, sum);
        }
        int minSum = minSubarraySum(nums);
        int minCircularSubarraySum = totalSum - minSum;
        return (maxSum > 0) ? max(minCircularSubarraySum, maxSum) : maxSum;
    }
};