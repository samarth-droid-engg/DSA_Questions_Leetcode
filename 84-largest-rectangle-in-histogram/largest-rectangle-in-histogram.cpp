class Solution {
public:
    void nextSmallerIndex(vector<int>& arr, vector<int>& next) {
        stack<int> st;
        st.push(-1);
        int sz = arr.size();
        for (int i = sz - 1; i >= 0; i--) {
            // int element = arr[i];
            while (st.top() != -1 && arr[st.top()] >= arr[i]) {
                st.pop();
            }
            // matlab ab chota h element se
            next.push_back(st.top());
            st.push(i);
        }
        reverse(next.begin(), next.end());
    }
    void prevSmallerIndex(vector<int>& arr, vector<int>& prev) {
        stack<int> st;
        st.push(-1);
        for (int i = 0; i < arr.size(); i++) {
            // int element = arr[i];
            //   Check for bada
            while (st.top() != -1 && arr[st.top()] >= arr[i]) {
                st.pop();
            }
            // ab chota mila
            prev.push_back(st.top());
            st.push(i);
        }
    }
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        long long maxArea = 0;
        vector<int> prev;
        vector<int> next;
        prevSmallerIndex(heights, prev);
        nextSmallerIndex(heights, next);
        for (int i = 0; i < n; i++) {
            if (next[i] == -1)
                next[i] = n;

            int width = next[i] - prev[i] - 1;
            long long area = 1LL * heights[i] * width;
            maxArea = max(area, maxArea);
        }
        return (int)maxArea;
    }
};