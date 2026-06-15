// Sawal bol rha h ki mujhe word bnana h board mein pehle dhund kr pehla
class Solution {
public:
    bool solve(vector<vector<char>>& board, string& word, int row, int col,
               int index) {

        if (index == word.size())
            return true;

        if (row < 0 || col < 0 || row >= board.size() || col >= board[0].size())
            return false;

        if (board[row][col] != word[index])
            return false;

        char temp = board[row][col];
        board[row][col] = '#';

        bool found = solve(board, word, row + 1, col, index + 1) ||
                     solve(board, word, row - 1, col, index + 1) ||
                     solve(board, word, row, col + 1, index + 1) ||
                     solve(board, word, row, col - 1, index + 1);

        board[row][col] = temp;

        return found;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int row = board.size();
        int col = board[0].size();
        int index = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (board[i][j] == word[index]) {
                    if (solve(board, word, i, j, 0)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};