class Solution {
public:
    long long countIntersectingIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<int> ends;

        for (auto& interval : intervals) {
            ends.push_back(interval[1]);
        }

        sort(ends.begin(), ends.end());

        long long nonIntersecting = 0;

        for (auto& it : intervals) {
            int start = it[0];

            int count =
                lower_bound(ends.begin(), ends.end(), start) - ends.begin();

            nonIntersecting += count;
        }

        long long totalPairs = 1LL * n * (n - 1) / 2;

        return totalPairs - nonIntersecting;
    }
};