class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size();
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            int minE = INT_MAX;
            int maxE = INT_MIN;
            for (int j = i; j < n; j++) {
                minE = min(minE, nums[j]);
                maxE = max(maxE, nums[j]);
                sum += (maxE - minE);
            }
        }
        return sum;
    }
};