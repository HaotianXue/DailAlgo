https://leetcode.com/problems/predict-the-winner/

class Solution {
public:
    // dp[i][j]: max score the player1 could get by picking from interval [i, j]
    // player 1: dp[i][j] = max(nums[i] + dp[i + 1][j], nums[j] + dp[i][j - 1])
    // player 2: dp[i][j] = min(dp[i + 1][j], dp[i][j - 1])
    bool PredictTheWinner(vector<int>& nums) {
        
        int n = nums.size();
        
        vector<vector<int>> memo(n, vector<int>(n, -1));
        
        function<int(int, int, int)> dfs = [&](int i, int j, int turn) {
            if (i == j) return !turn ? nums[i] : 0;
            if (memo[i][j] != -1) return memo[i][j];
            if (!turn) memo[i][j] = max(nums[i] + dfs(i + 1, j, turn ^ 1), nums[j] + dfs(i, j - 1, turn ^ 1));
            else memo[i][j] = min(dfs(i + 1, j, turn ^ 1), dfs(i, j - 1, turn ^ 1));
            return memo[i][j];
        };
        
        return 2 * dfs(0, n - 1, 0) >= accumulate(nums.begin(), nums.end(), 0);
    }
};