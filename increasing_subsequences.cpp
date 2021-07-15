// https://leetcode.com/problems/increasing-subsequences/
class Solution {
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {  
        int n = nums.size();
        vector<vector<int>> res;
        if (n == 0) return res;
        
        vector<int> curSet;
        function<void(int)> dfs = [&](int index) {
            if (curSet.size() >= 2) {
                res.push_back(curSet);
            }
            // each number can only be used once in the same depth
            unordered_set<int> seen;
            for (int i = index; i < n; ++i) {
                if (curSet.size() > 0 && nums[i] < curSet.back()) continue;
                if (seen.count(nums[i])) continue;
                seen.insert(nums[i]);
                curSet.push_back(nums[i]);
                dfs(i + 1);
                curSet.pop_back();
            }
        };
        
        dfs(0);
        return res;
    }
};