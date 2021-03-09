// https://leetcode.com/problems/meeting-rooms-ii/
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) return 0;
        
        vector<pair<int, int>> times(intervals.size() * 2); // first: time, second: indicator(start or end time)
        
        for (int i = 0; i < intervals.size(); ++i) {
            times[i * 2] = {intervals[i][0], 1};
            times[i * 2 + 1] = {intervals[i][1], -1};
        }
        
        auto cmp = [](const pair<int, int>& p1, const pair<int, int>& p2) {
            if (p1.first == p2.first) return p1.second < p2.second;
            return p1.first < p2.first;
        };
        
        sort(times.begin(), times.end(), cmp);
        
        int res = 0, cnt = 0;
        for (int i = 0; i < times.size(); ++i) {
            if (times[i].second == 1) ++cnt; // start time
            else --cnt; // end time
            // cnt += times[i].second;
            res = max(res, cnt);
        }
        return res;
    }
};