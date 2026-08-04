class Solution {
public:
    int minAddToMakeValid(string s) {
        int ans = 0;
        stack<int> st;
        for (auto ch : s) {
            if (ch == '(') {
                st.push('(');
                ++ans;
            } else {
                if (!st.empty()) {
                    st.pop();
                    --ans;
                } else {
                    ++ans;
                }
            }
        }
        return ans;
    }
};