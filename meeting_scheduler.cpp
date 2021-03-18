// https://leetcode.com/problems/meeting-scheduler/
class Solution {
public:
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        // find first two slots that intersect
        // determine the length of intersect and compare it with duration
        // if so => return
        // otherwise the one finish eailer move to next slot
        
        auto cmp = [](const vector<int>& v1, const vector<int>& v2) {
            if (v1[0] == v2[0]) return v1[1] < v2[1];
            return v1[0] < v2[0];
        };
        
        sort(slots1.begin(), slots1.end(), cmp);
        sort(slots2.begin(), slots2.end(), cmp);
        
        int i = 0, j = 0;
        int n1 = slots1.size(), n2 = slots2.size();
        
        auto hasIntersection = [](vector<int>& i1, vector<int>& i2) {
            if (i1[1] < i2[0] || i1[0] > i2[1]) return false;
            return true;
        };
        
        while (i < n1 && j < n2) {
            vector<int> i1 = slots1[i], i2 = slots2[j];
            if (!hasIntersection(i1, i2)) {
                if (i1[1] < i2[0]) ++i;
                else ++j;
            } else {
                int start = max(i1[0], i2[0]);
                int end = min(i1[1], i2[1]);
                if (end - start >= duration) return {start, start + duration};
                else {
                    if (i1[1] < i2[1]) ++i;
                    else ++j;
                }
            }
        }
        return {};
    }
};