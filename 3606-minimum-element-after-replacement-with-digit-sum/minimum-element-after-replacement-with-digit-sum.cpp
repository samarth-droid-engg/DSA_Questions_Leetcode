class Solution {
public:
    int sumOfDigits(int n) {
        int ans = 0;
        while (n > 0) {
            int digit = n % 10;
            ans += digit;
            n /= 10;
        }
        return ans;
    }
    int minElement(vector<int>& nums) {
        int n = nums.size();
        int minE = INT_MAX;
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            nums[i] = sumOfDigits(num);
            minE = min(minE, nums[i]);
        }
        return minE;
    }
};