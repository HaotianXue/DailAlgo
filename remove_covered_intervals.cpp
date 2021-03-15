// https://leetcode.com/problems/remove-covered-intervals/

// Approach i
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n <= 1) return n;
        
        // start time increasing + end time decreasing (to make sure only previous can cover current)
        sort(intervals.begin(), intervals.end(), 
             [](vector<int>& v1, vector<int>& v2) {
                 if (v1[0] == v2[0]) return v2[1] < v1[1];
                 return v1[0] < v2[0];
        });
        
        int res = 0;
        int end = 0;
        for (int i = 0; i < n; ++i) {
            if (end < intervals[i][1]) {
                end = intervals[i][1];
                ++res;
            }
        }
        
        return res;
    }
};

// Approach ii
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n <= 1) return n;
        
        sort(intervals.begin(), intervals.end(), 
             [](vector<int>& v1, vector<int>& v2) {
                 if (v1[0] == v2[0]) return v1[1] < v2[1];
                 return v1[0] < v2[0];
        });
        
        int cnt = 0;
        int start = intervals[0][0], end = intervals[0][1];
        for (int i = 1; i < n; ++i) {
            if (intervals[i][0] <= start && end <= intervals[i][1]) {
                start = intervals[i][0];
                end = intervals[i][1];
                ++cnt;
            } else if (intervals[i][0] >= start && end >= intervals[i][1]) {
                ++cnt;
            } else {
                start = intervals[i][0];
                end = intervals[i][1];
            }
        }
        
        return n - cnt;
    }
};