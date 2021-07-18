// https://leetcode.com/problems/number-of-squareful-arrays/

class Solution {
public:
    int numSquarefulPerms(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        
        sort(nums.begin(), nums.end());
        
        int res = 0;
        vector<int> curVec;
        vector<int> visited(n, 0);
        function<void()> dfs = [&]() {
            if (curVec.size() == n) {
                ++res;
                return;
            }
            
            for (int i = 0; i < n; ++i) {
                if (visited[i]) continue;
                if (i > 0 && !visited[i - 1] && nums[i] == nums[i - 1]) continue;
                if (curVec.size() > 0 && !isPerfect(curVec.back(), nums[i])) continue;
                
                curVec.push_back(nums[i]);
                visited[i] = 1;
                dfs();
                visited[i] = 0;
                curVec.pop_back();
            }
        };
        
        dfs();
        return res;
    }
    
    bool isPerfect(int x, int y) {
        int s = sqrt(x + y);
        return s * s == x + y;
    }
};