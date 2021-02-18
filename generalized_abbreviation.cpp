// https://leetcode.com/problems/generalized-abbreviation/
class Solution {
public:
    vector<string> generateAbbreviations(string word) {
        vector<string> res;
        if (word.size() == 0) return res;
        
        // 决策树在叶子结点才添加结果
        function<void(int, int, string)> dfs = [&](int pos, int count, string state) {
            if (pos == word.size()) {
                if (count > 0) {
                    state += to_string(count);
                }
                res.push_back(state);
                return;
            }
            // 不缩写 => 把之前count要加上
            dfs(pos + 1, 0, state + (count == 0 ? "" : to_string(count)) + word[pos]);
            // 缩写
            dfs(pos + 1, count + 1, state);
        };
        
        dfs(0, 0, "");
        
        return res;
    }
};