// https://leetcode.com/problems/meeting-rooms/
class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        if (intervals.size() == 0) return true;
        
        auto cmp = [](vector<int>& v1, vector<int>& v2) {
            if (v1[0] == v2[0]) return v1[1] < v2[1];
            return v1[0] < v2[0];
        };
        
        sort(intervals.begin(), intervals.end(), cmp);
        
        for (int i = 0; i < intervals.size() - 1; ++i) {
            if (intervals[i][1] > intervals[i + 1][0]) return false;
        }
        return true;
    }
};