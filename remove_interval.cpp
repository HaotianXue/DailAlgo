// https://leetcode.com/problems/remove-interval/
class Solution {
public:
    vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
        int n = intervals.size();
        vector<vector<int>> res;
        
        int i = 0;
        int start = toBeRemoved[0], end = toBeRemoved[1];
        
        while (i < n && intervals[i][1] <= start) res.push_back(intervals[i++]);
        
        while (i < n && end > intervals[i][0]) {
            if (start > intervals[i][0] && end < intervals[i][1]) { // intervals[i] contain [start, end]
                res.push_back({intervals[i][0], start});
                res.push_back({end, intervals[i][1]});
            } else if (start > intervals[i][0]) { // intersection: [intervals[i][0], start]
                res.push_back({intervals[i][0], start});
            } else if (end < intervals[i][1]) { // intersection: [end, intervals[i][1]]
                res.push_back({end, intervals[i][1]});
            }
            ++i;
        }
        
        while (i < n) res.push_back(intervals[i++]);
        
        return res;
    }
};