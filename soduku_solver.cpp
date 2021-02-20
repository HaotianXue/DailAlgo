https://leetcode.com/problems/sudoku-solver/
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        // 需要check: column, row, box
        vector<vector<bool>> column(9, vector<bool>(10, false));
        vector<vector<bool>> row(9, vector<bool>(10, false));
        vector<vector<bool>> box(9, vector<bool>(10, false));
        
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') continue;
                int num = board[i][j] - '0';
                column[j][num] = true;
                row[i][num] = true;
                box[(i / 3) * 3 + (j / 3)][num] = true;
            }
        }
        
        function<bool(int)> dfs = [&](int id) {
            if (id == 81) return true;
            int x = id / 9, y = id % 9;
            if (board[x][y] != '.') return dfs(id + 1);
            for (int i = 1; i <= 9; ++i) {
                if (column[y][i]) continue;
                if (row[x][i]) continue;
                if (box[(x / 3) * 3 + (y / 3)][i]) continue;
                board[x][y] = i + '0';
                row[x][i] = true;
                column[y][i] = true;
                box[(x / 3) * 3 + (y / 3)][i] = true;
                if (dfs(id + 1)) return true;
                board[x][y] = '.';
                row[x][i] = false;
                column[y][i] = false;
                box[(x / 3) * 3 + (y / 3)][i] = false;
            }
            return false;
        };
        
        dfs(0);
    }
};