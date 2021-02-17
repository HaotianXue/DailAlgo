// https://leetcode.com/problems/generate-parentheses/
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        string curStr = "";
        vector<string> res;
        function<void(int, int)> dfs = [&](int leftNum, int rightNum) {
            if (leftNum == n && rightNum == n) {
                res.push_back(curStr);
                return;
            }
            
            if (leftNum < n) {
                // 加左括号
                curStr += "(";
                dfs(leftNum + 1, rightNum);
                curStr.pop_back();
            }
            // 加右括号(当且仅当当前左括号数大于右括号数时)
            if (leftNum > rightNum) {
                curStr += ")";
                dfs(leftNum, rightNum + 1);
                curStr.pop_back();
            }
        };
        
        dfs(0, 0);
        return res;
    }
};