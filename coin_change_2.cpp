// https://leetcode.com/problems/coin-change-2/

class Solution {
public:
    // dp[i][j]: number of ways of first i coins to make up j amount
    // dp[i][j] = dp[i - 1][j] + sum{dp[i - 1][j - k * coins[i]]}
    int change_2D(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= amount; ++j) {
                for (int k = 0; k <= j / coins[i - 1]; ++k) {
                    dp[i][j] += dp[i - 1][j - k * coins[i - 1]];
                }
            }
        }
        return dp[n][amount];
    }
    
    // one-dim optimization: dp[j] = dp[j] + dp[j - coins[i]]
    int change_1D(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = coins[i - 1]; j <= amount; ++j) {
                dp[j] += dp[j - coins[i - 1]];
            }
        }
        return dp[amount];
    }
    
    // memo search
    int change(int amount, vector<int>& coins) {
        
        unordered_map<string, int> dp;
        
        // use dfs to search the number of combinations of "firstN" coins to make up "amount"
        function<int(int, int)> dfs = [&](int amount, int firstN) {
            if (amount == 0) return 1;
            if (firstN == 0) return 0;
            string s = to_string(amount) + "-" + to_string(firstN);
            if (dp.count(s)) return dp[s];
            // determine whether pick current coin or not
            int include = 0, exclude = 0;
            if (amount - coins[firstN - 1] >= 0) include += dfs(amount - coins[firstN - 1], firstN);
            exclude += dfs(amount, firstN - 1);
            return dp[s] = include + exclude;
        };
        
        return dfs(amount, coins.size());
        
    }
    
};