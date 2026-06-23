class Solution {
public:
    int binarySearch(vector<int>& nums, int target, bool leftMost) {
        int s = 0, e = nums.size() - 1;
        int left = -1, right = -1;
        while (s <= e) {
            int mid = s + (e - s) / 2;
            if (leftMost) {
                if (nums[mid] > target) {
                    e = mid - 1;
                } else if (nums[mid] < target) {
                    s = mid + 1;
                } else {
                    left = mid;
                    e = mid - 1;
                }
            } else {
                if (nums[mid] > target) {
                    e = mid - 1;
                } else if (nums[mid] < target) {
                    s = mid + 1;
                } else {
                    right = mid;
                    s = mid + 1;
                }
            }
        }
        return (leftMost) ? left : right;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = binarySearch(nums, target, true);
        int right = binarySearch(nums, target, false);
        return {left, right};
    }
};