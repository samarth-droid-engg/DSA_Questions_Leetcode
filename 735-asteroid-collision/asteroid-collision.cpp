class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> st;

        for (int asteroid : asteroids) {

            // Collision is possible only when:
            // stack top is moving right (+) and current moves left (-)
            if (asteroid > 0) {
                st.push(asteroid);
            } else {
                while (!st.empty() && st.top() > 0 &&
                       st.top() < abs(asteroid)) {
                    st.pop();
                }

                // Equal size -> both destroy
                if (!st.empty() && st.top() > 0 && st.top() == abs(asteroid)) {
                    st.pop();
                }
                // Current asteroid survives if no bigger positive asteroid
                // exists
                else if (st.empty() || st.top() < 0) {
                    st.push(asteroid);
                }
            }
        }

        vector<int> ans;
        while (!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};