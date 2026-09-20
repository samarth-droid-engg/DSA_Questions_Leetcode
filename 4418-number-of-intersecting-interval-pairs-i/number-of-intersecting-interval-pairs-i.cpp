class Solution {
public:
    int countIntersectingIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size(), count = 0;
        for (int i = 0; i < n; i++) {
            int start = intervals[i][0];
            int end = intervals[i][1];
            for (int j = i + 1; j < n; j++) {
                int start2 = intervals[j][0];
                int end2 = intervals[j][1];
                if ((start2 == start) || (end2 == end) || (start2 == end) ||
                    (end2 == start) || (start2 >= start && end2 < end) ||
                    (start2 >= start && start2 < end) ||
                    (end2 >= start && end2 < end) ||
                    (start >= start2 && end < end2)) {
                    count++;
                }
            }
        }
        return count;
    }
};