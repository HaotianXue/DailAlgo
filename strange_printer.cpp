// https://leetcode.com/problems/strange-printer/

class Solution {
public:
    
    // dp[i][j]: minimum number of turns to print from s[i] -> s[j]
    // default behaviour: dp[i][j] = dp[i][k - 1] + 1
    // if s[k] == s[j] => dp[i][j] = min(dp[i][k], dp[k + 1][j - 1]), i <= k < j
    // init: dp[i][i] = 1, dp[i][j] = 0 (if i > j <=> empty string)
    int strangePrinter(string s) {
        int n = s.size();
        
        vector<vector<int>> dp(n, vector<int>(n, -1));
        
        function<int(int, int)> dfs = [&](int i, int j) {
            if (i > j) return 0;
            if (i == j) return 1;
            if (dp[i][j] != -1) return dp[i][j];
            
            int res = dfs(i, j - 1) + 1;
            
            for (int k = i; k < j; ++k) {
                if (s[k] == s[j]) {
                    res = min(res, dfs(i, k) + dfs(k + 1, j - 1));
                }
            }
            return dp[i][j] = res;
        };
        
        return dfs(0, n - 1);
    }
};