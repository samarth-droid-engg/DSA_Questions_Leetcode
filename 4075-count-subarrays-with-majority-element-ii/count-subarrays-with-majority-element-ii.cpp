class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        int size = 2 * n + 2;
        vector<int> bit(size + 1, 0);

        auto update = [&](int i) {
            for (i++; i <= size; i += i & (-i))
                bit[i]++;
        };
        auto query = [&](int i) {
            int s = 0;
            for (i++; i > 0; i -= i & (-i))
                s += bit[i];
            return s;
        };

        long long ans = 0;
        int prefix = 0;
        update(prefix + n); // insert P[0] = 0

        for (int r = 0; r < n; r++) {
            prefix += (nums[r] == target) ? 1 : -1;
            int idx = prefix + n;
            ans += query(idx - 1); // count earlier prefixes strictly smaller
            update(idx);
        }
        return ans;
    }
};