// https://leetcode.com/problems/non-overlapping-intervals/

// Approach i: DP - 676ms O(n^2)
class Solution {
public:
    // first find the length of longest "increasing"/non-overlapping subsequence
    // answer is n - that length
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n <= 1) return 0;
        
        sort(intervals.begin(), intervals.end(), 
             [](vector<int>& v1, vector<int>& v2) {
                 if (v1[0] == v2[0]) return v1[1] < v2[1];
                 return v1[0] < v2[0];
        });
        
        vector<int> dp(n, 1);
        for (int i = 0; i < n; ++i) {
            int start = intervals[i][0];
            for (int j = 0; j < i; ++j) {
                if (intervals[j][1] <= start) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        
        int maxLen = 0;
        for (int i = 0; i < n; ++i) {
            maxLen = max(maxLen, dp[i]);
        }
        
        return n - maxLen;
    }
};

// Approach ii: DP(memo search using dfs) - 1100ms O(n^2)
class Solution {
public:
    // first find the length of longest "increasing"/non-overlapping subsequence
    // answer is n - that length
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n <= 1) return 0;
        
        sort(intervals.begin(), intervals.end(), 
             [](vector<int>& v1, vector<int>& v2) {
                 if (v1[0] == v2[0]) return v1[1] < v2[1];
                 return v1[0] < v2[0];
        });
        
        vector<int> memo(n, -1);
        function<int(int)> dfs = [&](int curEnd) {
            if (memo[curEnd] != -1) return memo[curEnd];
            if (curEnd == 0) return memo[curEnd] = 1;
            int res = 1;
            int start = intervals[curEnd][0], end = intervals[curEnd][1];
            for (int i = 0; i < curEnd; ++i) {
                if (start >= intervals[i][1]) {
                    res = max(res, dfs(i) + 1);
                } 
            }
            return memo[curEnd] = res;
        };
        
        int maxLen = 0;
        for (int i = 0; i < intervals.size(); ++i) {
            maxLen = max(maxLen, dfs(i));
        }
        return n - maxLen;
    }
};

// Approach iii: greedy - 12ms O(nlogn)
class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n <= 1) return 0;
        
        sort(intervals.begin(), intervals.end(), 
            [](vector<int>& v1, vector<int>& v2) {
                if (v1[1] == v2[1]) return v1[0] < v2[0];
                return v1[1] < v2[1];
            });
        
        int res = 0, end = INT_MIN;
        for (auto& t: intervals) {
            if (t[0] >= end) end = t[1];
            else {
                ++res;
            }
        }
        return res;
    }
};