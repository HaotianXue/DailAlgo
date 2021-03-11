// https://leetcode.com/problems/merge-intervals/

// Approach i: sort
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        auto cmp = [](const vector<int>& v1, const vector<int>& v2) {
            if (v1[0] == v2[0]) return v1[1] < v2[1];
            return v1[0] < v2[0];
        };
        sort(intervals.begin(), intervals.end(), cmp);
        vector<vector<int>> res;
        for (auto &interval: intervals) {
            if (res.size() == 0 || interval[0] > res.back()[1]) {
                res.push_back({interval[0], interval[1]});
            } else {
                res.back()[1] = max(res.back()[1], interval[1]);
            }
        }
        return res;
    }
};

// Approach ii: use tree map
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        map<int, int> timeMap;
        
        for (auto &interval: intervals) {
            ++timeMap[interval[0]];
            --timeMap[interval[1]];
        }
        
        int cnt = 0, start;
        vector<vector<int>> res;
        for (auto &kv: timeMap) {
            if (cnt == 0) start = kv.first;
            // if cnt is 0 at this time, it means that an interval is finished
            if ((cnt += kv.second) == 0) {
                res.push_back({start, kv.first});
            }
        }
        return res;
    }
};