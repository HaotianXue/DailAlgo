https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings/
class Solution {
public:
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