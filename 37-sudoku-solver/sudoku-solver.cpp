class Solution {
public:
    bool isSafe(vector<vector<char>>& board, int row, int col, char ch) {
        // Row check
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == ch)
                return false;
        }
        // Col Check
        for (int i = 0; i < 9; i++) {
            if (board[i][col] == ch)
                return false;
        }
        // Check for 3x3 matrix
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;

        for (int i = startRow; i < startRow + 3; i++) {
            for (int j = startCol; j < startCol + 3; j++) {
                if (board[i][j] == ch)
                    return false;
            }
        }
        return true;
    }
    bool solve(vector<vector<char>>& board, int row, int col) {
        if (row == 9)
            return true;

        int nextRow = row;
        int nextCol = col + 1;

        if (nextCol == 9) {
            nextRow++;
            nextCol = 0;
        }
        if (board[row][col] != '.') {
            return solve(board, nextRow, nextCol);
        }
        for (char ch = '1'; ch <= '9'; ch++) {
            if (isSafe(board, row, col, ch)) {
                board[row][col] = ch;
                if (solve(board, nextRow, nextCol))
                    return true;
                board[row][col] = '.';
            }
        }
        return false;
    }
    void solveSudoku(vector<vector<char>>& board) {
        // Yeh pass krdia function
        solve(board, 0, 0);
    }
};