// https://leetcode.com/problems/beautiful-arrangement
class Solution {
public:
    int countArrangement(int n) {
        if (n <= 1) return 1;
        int visited = 0; // 用bitmask代替bool数组
        int res = 0;
        
        function<void(int)> dfs = [&](int curIndex) {
            if (curIndex == n + 1) {
                ++res;
                return;
            }
            for (int i = n; i >= 1; --i) { // 从大的数开始搜索分支少
                int bit = 1 << i;
                if (visited & bit) continue;
                if (i % curIndex != 0 && curIndex % i != 0) continue;
                visited ^= bit; // 把i的位置标记为1
                dfs(curIndex + 1);
                visited ^= bit;
            }
        };
        
        dfs(1);
        
        return res;
    }
};