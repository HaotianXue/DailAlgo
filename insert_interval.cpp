// https://leetcode.com/problems/insert-interval/

// Approach i
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size();
        vector<vector<int>> res;
        if (n== 0) {
            res.push_back(newInterval);
            return res;
        }
        
        int start = newInterval[0], end = newInterval[1];
        
        int i = 0;
        while (i < n && intervals[i][1] < start) res.push_back(intervals[i++]);
        
        while (i < n && end >= intervals[i][0]) {
            start = min(start, intervals[i][0]);
            end = max(end, intervals[i][1]);
            ++i;
        }
        res.push_back({start, end});
        
        while (i < n) res.push_back(intervals[i++]);
        
        return res;
    }
};


// Approach ii
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        if (intervals.size() == 0) {
            res.push_back(newInterval);
            return res;
        }
        
        vector<vector<int>> times;
        bool inserted = false;
        // insert right before the first interval which start time greated than its start time
        for (int i = 0; i < intervals.size(); ++i) {
            if (inserted) {
                times.push_back(intervals[i]);
            } else {
                if (intervals[i][0] < newInterval[0]) {
                    times.push_back(intervals[i]);
                } else if (intervals[i][0] == newInterval[0]) {
                    if (intervals[i][1] < newInterval[1]) {
                        times.push_back(intervals[i]);
                        times.push_back(newInterval);
                    } else {
                        times.push_back(newInterval);
                        times.push_back(intervals[i]);
                    }
                    inserted = true;
                } else {
                    times.push_back(newInterval);
                    times.push_back(intervals[i]);
                    inserted = true;
                }
            }
        }
        if (!inserted) times.push_back(newInterval);
        
        for (int i = 0; i < times.size(); ++i) {
            if (res.size() == 0 || res.back()[1] < times[i][0]) {
                res.push_back(times[i]);
            } else {
                res.back()[1] = max(res.back()[1], times[i][1]);
            }
        }
        return res;
    }
};