https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings/
class Solution {
public:

    // 类似子集的两种实现方式

    // method 1: 每次寻找以index开头的split方式
    int maxUniqueSplit(string s) {
        int n = s.size();
        if (n <= 1) return n;
        
        unordered_set<string> set;
        int res = 0;
        
        function<void(int)> dfs = [&](int index) {
            if (index == n) {
                res = max(res, (int)set.size());
                return;
            }
            
            for (int i = index; i < s.size(); ++i) {
                string curS = s.substr(index, i - index + 1);
                if (set.count(curS)) continue;
                set.insert(curS);
                dfs(i + 1);
                set.erase(curS);
            }
            
        };
        
        dfs(0);
        return res;
    }

    // method 2: 当前index选或不选(split or not)
    int maxUniqueSplit(string s) {
        int n = s.size();
        if (n <= 1) return n;
        
        unordered_set<string> set;
        int res = 0;
        
        function<void(int, string)> dfs = [&](int index, string carry) {
            if (index == n) {
                if (carry.size() == 0) {
                    res = max(res, (int)set.size());
                };
                return;
            }
            // split or not
            string curC = carry + s[index];
            if (!set.count(curC)) {
                set.insert(curC);
                dfs(index + 1, "");
                set.erase(curC);
            }
            dfs(index + 1, curC);
        };
        
        dfs(0, "");
        
        return res;
    }
};