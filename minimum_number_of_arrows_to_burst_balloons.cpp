// https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int n = points.size();
        
        if (n <= 1) return n;
        
        sort(points.begin(), points.end(), 
             [](const vector<int>& v1, const vector<int>& v2) {
                 if (v1[0] == v2[0]) return v1[1] < v2[1];
                 return v1[0] < v2[0];
             });
        
        int res = 1;
        int prevEnd = points[0][1];
        for (int i = 1; i < n; ++i) {
            int curStart = points[i][0];
            if (curStart <= prevEnd) {
                prevEnd = min(prevEnd, points[i][1]); // keep track of min end point otherwise we cannot hit previous one
                continue;
            }
            ++res;
            prevEnd = points[i][1];
        }
        return res;
    }
};