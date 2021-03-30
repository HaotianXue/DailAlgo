// https://leetcode.com/problems/target-sum/

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int sum = 0, n = nums.size();
        for (int num: nums) sum += num;
        if (sum < S) return 0;
        vector<vector<int>> dp(2, vector<int>(2 * sum + 1, 0));
        dp[0][sum] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 2 * sum + 1; ++j) {
                dp[i % 2][j] = 0;
                if (j < 2 * sum + 1 - nums[i - 1]) {
                    dp[i % 2][j] += dp[(i - 1) % 2][j + nums[i - 1]];
                } 
                if (nums[i - 1] <= j) {
                    dp[i % 2][j] += dp[(i - 1) % 2][j - nums[i - 1]];
                }
            }
        }
        return dp[n % 2][sum + S];
    }
};