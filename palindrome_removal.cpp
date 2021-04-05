https://leetcode.com/problems/palindrome-removal/

class Solution {
public:
    
    // dp[i][j]: min number of moves to remove arr[i] to arr[j]
    // default: dp[i][j] = dp[i][j - 1] + 1
    // when arr[j] == arr[k] => dp[i][j] = min{dp[i][k - 1] + dp[k + 1][j - 1]}
    // init: dp[i][i] = 1, dp[i][j] = 0 if i > j
    int minimumMoves(vector<int>& arr) {
        int n = arr.size();     
        
        vector<vector<int>> dp(n, vector<int>(n, -1));
        function<int(int, int)> dfs = [&](int i, int j) {
            if (i > j) return 0;
            if (i == j) return 1;
            if (dp[i][j] != -1) return dp[i][j];
            int res = dfs(i, j - 1) + 1;
            if (j > 0 && arr[j] == arr[j - 1]) {
                res = min(res, dfs(i, j - 2) + 1);
            }
            for (int k = i; k < j - 1; ++k) {
                if (arr[k] == arr[j]) {
                    res = min(res, dfs(i, k - 1) + dfs(k + 1, j - 1));
                }
            }
            return dp[i][j] = res;
        };
        
        return dfs(0, n - 1);
    }
};