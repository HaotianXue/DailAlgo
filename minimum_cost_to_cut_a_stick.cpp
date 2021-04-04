https://leetcode.com/problems/minimum-cost-to-cut-a-stick/

class Solution {
public:
    
    // 1. calculate small sticks
    // 2. merge sticks
    // dp[i][j]: min cost to merge sticks(from i-th to j-th) to one complete stick
    int minCost(int n, vector<int>& cuts) {
        int m = cuts.size();
        
        sort(cuts.begin(), cuts.end());
        
        // store small sticks
        vector<int> arr(m + 1);
        int last = 0;
        
        for (int i = 0; i < m; ++i) {
            arr[i] = cuts[i] - last;
            last = cuts[i];
        }
        arr[m++] = n - last; // cuts.size() + 1 sticks
        
        vector<vector<int>> dp(m, vector<int>(m, 1e9));
        
        for (int i = 0; i < m; ++i) {
            dp[i][i] = 0;
        }
        
        for (int len = 2; len <= m; ++len) { // len: number of sticks
            for (int i = 0; i + len <= m; ++i) {
                int j = i + len - 1;
                // compute length after merge
                int sum = 0;
                for (int k = i; k <= j; ++k) sum += arr[k];
                
                for (int k = i; k < j; ++k) { // try out every position of current interval's last merged
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + sum);
                }
            }
        }
        // min cost of mergeing 0-th to (m - 1)th sticks
        return dp[0][m - 1];
    }
};