class Solution {
public:
    long long countIntersectingIntervals(vector<vector<int>>& intervals) {
        long long count = 0;
        sort(intervals.begin(), intervals.end());
        priority_queue<int, vector<int>, greater<int>> pq;
        for (auto& it : intervals) {
            int start = it[0], end = it[1];
            while (!pq.empty() && pq.top() < start) {
                pq.pop();
            }
            count += pq.size();
            pq.push(end);
        }
        return count;
    }
};