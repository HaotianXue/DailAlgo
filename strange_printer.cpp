// https://leetcode.com/problems/strange-printer/

class Solution {
public:
    int strangePrinter(string s) {
        int n = s.size();
        
        vector<vector<int>> dp(n, vector<int>(n, -1));
        
        function<int(int, int)> dfs = [&](int i, int j) {
            if (i > j) return 0;
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