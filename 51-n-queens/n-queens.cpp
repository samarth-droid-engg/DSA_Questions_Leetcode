class Solution {
public:
    bool isSafe(int row, int col, vector<vector<char>>& board) {
        // Only 3 directions are required to check
        // 1. backward
        // 2. Upper back diagonal
        // 3. Lower back diagonal

        // 1
        for (int j = col - 1; j >= 0; j--) {
            if (board[row][j] == 'Q')
                return false;
        }
        // 2
        int i = row - 1, j = col - 1;
        while (i >= 0 && j >= 0) {
            if (board[i][j] == 'Q')
                return false;
            i--;
            j--;
        }
        // 3
        i = row + 1;
        j = col - 1;
        while (i < board.size() && j >= 0) {
            if (board[i][j] == 'Q')
                return false;
            i++;
            j--;
        }
        return true;
    }
    void storeSolution(vector<vector<char>>& board, vector<vector<string>>& st,
                       int n) {
        vector<string> temp;
        for (int i = 0; i < n; i++) {
            string ans = "";
            for (int j = 0; j < n; j++) {
                char ch = board[i][j];
                ans.push_back(ch);
            }
            temp.push_back(ans);
        }
        st.push_back(temp);
    }
    void solve(vector<vector<string>>& st, vector<vector<char>>& board, int n,
               int colIndex) {
        if (colIndex >= n) {
            storeSolution(board, st, n);
            return;
        }
        for (int row = 0; row < n; row++) {
            if (isSafe(row, colIndex, board)) { // To check if valid position
                board[row][colIndex] = 'Q';
                solve(st, board, n, colIndex + 1);
                board[row][colIndex] = '.';
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        // Board Banao
        vector<vector<string>> st;
        vector<vector<char>> board(n, vector<char>(n, '.'));
        string s = "";
        solve(st, board, n, 0);
        return st;
    }
};