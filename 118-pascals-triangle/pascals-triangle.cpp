class Solution {
public:
    void solve(int numRows, int row, vector<vector<int>>& vec) {
        if (row >= numRows)
            return;
        if (row == 0) {
            vec.push_back({1});
            solve(numRows, row + 1, vec);
            return;
        }
        if (row == 1) {
            vec.push_back({1, 1});
            solve(numRows, row + 1, vec);
            return;
        }
        vector<int> temp;
        int j = 0;
        for (int i = 0; i <= row; i++) {
            if (i == 0 || i == row)
                temp.push_back(1);
            else {

                int sum = vec[row - 1][j] + vec[row - 1][j + 1];
                temp.push_back(sum);
                j += 1;
            }
        }
        vec.push_back(temp);
        solve(numRows, row + 1, vec);
    }
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> v;
        solve(numRows, 0, v);
        return v;
    }
};