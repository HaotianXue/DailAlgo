// https://leetcode.com/problems/non-overlapping-intervals/

// Approach i: greedy
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