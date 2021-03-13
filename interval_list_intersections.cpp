// https://leetcode.com/problems/interval-list-intersections/
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vector<vector<int>> res;
        if (firstList.size() == 0 || secondList.size() == 0) return res;
        
        vector<pair<int, int>> times;
        for (int i = 0; i < firstList.size(); ++i) {
            times.push_back({firstList[i][0], 1});
            times.push_back({firstList[i][1], -1});
        }
        for (int i= 0; i < secondList.size(); ++i) {
            times.push_back({secondList[i][0], 1});
            times.push_back({secondList[i][1], -1});
        }
        
        auto cmp = [](const pair<int, int>& p1, const pair<int, int>& p2) {
            if (p1.first == p2.first) return p2.second < p1.second;
            return p1.first < p2.first;
        };
        sort(times.begin(), times.end(), cmp);
        
        int cnt = 0, start = 0;
        for (auto p: times) {
            if (p.second == 1 && cnt + p.second == 2) {
                start = p.first;
            } else if (p.second == -1 && cnt + p.second == 1) {
                res.push_back({start, p.first});
            }
            cnt += p.second;
        }
        return res;
    }
};