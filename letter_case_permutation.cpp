// https://leetcode.com/problems/letter-case-permutation/
class Solution {
public:
    vector<string> letterCasePermutation(string S) {
        vector<string> res;
        
        function<void(int, string)> dfs = [&](int pos, string cur) {
            if (pos == S.size()) {
                res.push_back(cur);
                return;
            }
            if (S[pos] >= 'a' && S[pos] <= 'z') {
                dfs(pos + 1, cur + string(1, S[pos] - 32));
            } else if (S[pos] >= 'A' && S[pos] <= 'Z') {
                dfs(pos + 1, cur + string(1, S[pos] + 32));
            }
            dfs(pos + 1, cur + S[pos]);
        };
        
        dfs(0, "");
        return res;
    }
};