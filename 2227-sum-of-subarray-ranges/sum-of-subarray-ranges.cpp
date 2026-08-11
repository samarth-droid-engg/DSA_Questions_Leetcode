class Solution {
public:
    vector<int> nextSmaller(vector<int>& arr) {
        stack<int> st;
        vector<int> v;
        int n = arr.size();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && arr[st.top()] >= arr[i]) {
                st.pop();
            }
            if (st.empty()) {
                v.push_back(n);
            } else {
                v.push_back(st.top());
            }
            st.push(i);
        }
        reverse(v.begin(), v.end());
        return v;
    }
    vector<int> prevSmaller(vector<int>& arr) {
        stack<int> st;
        vector<int> v;
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[st.top()] > arr[i]) {
                st.pop();
            }
            if (st.empty()) {
                v.push_back(-1);
            } else {
                v.push_back(st.top());
            }
            st.push(i);
        }
        return v;
    }
    vector<int> nextGreater(vector<int>& arr) {
        stack<int> st;
        vector<int> v;
        int n = arr.size();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && arr[st.top()] <= arr[i]) {
                st.pop();
            }
            if (st.empty()) {
                v.push_back(n);
            } else {
                v.push_back(st.top());
            }
            st.push(i);
        }
        reverse(v.begin(), v.end());
        return v;
    }
    vector<int> prevGreater(vector<int>& arr) {
        stack<int> st;
        vector<int> v;
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            while (!st.empty() && arr[st.top()] < arr[i]) {
                st.pop();
            }
            if (st.empty()) {
                v.push_back(-1);
            } else {
                v.push_back(st.top());
            }
            st.push(i);
        }
        return v;
    }
    long long minSubArraySum(vector<int>& arr) {
        auto next = nextSmaller(arr);
        auto prev = prevSmaller(arr);
        long long sum = 0;
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            long long left = i - prev[i];
            long long right = next[i] - i;

            long long contribution = (arr[i] * left) * right;

            sum = (sum + contribution);
        }
        return sum;
    }
    long long maxSubArraySum(vector<int>& arr) {
        auto next = nextGreater(arr);
        auto prev = prevGreater(arr);
        long long sum = 0;
        int n = arr.size();
        for (int i = 0; i < n; i++) {
            long long left = i - prev[i];
            long long right = next[i] - i;

            long long contribution = (arr[i] * left) * right;

            sum = (sum + contribution);
        }
        return sum;
    }
    long long subArrayRanges(vector<int>& nums) {
        auto minSum = minSubArraySum(nums);
        auto maxSum = maxSubArraySum(nums);
        return maxSum - minSum;
    }
};