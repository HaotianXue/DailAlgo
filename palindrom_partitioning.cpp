// https://leetcode.com/problems/palindrome-partitioning/
class Solution {
public:
    /*
     * @param s: A string
     * @return: A list of lists of string
     */
    vector<vector<string>> partition(string &s) {
        // write your code here
        vector<vector<string>> res;
        vector<string> cur;
        
        dfs(s, 0, res, cur);
        return res;
    }
    
    // 暴力回溯: 搜索s[startIndex:]的所有分割方案
    void dfs(string &s, int startIndex, vector<vector<string>> &res, vector<string> &cur) {
        if (startIndex == s.size()) {
            res.push_back(cur);
            return;
        }
        
        for (int length = 1; length <= s.size() - startIndex; ++length) {
            string prefix = s.substr(startIndex, length);
            if (!isPalindrome(prefix)) continue;
            cur.push_back(prefix);
            dfs(s, startIndex + length, res, cur);
            cur.pop_back();
        }
        
    }

    vector<vector<string>> partition1(string &s) {
        // write your code here
        unordered_map<int, vector<vector<string>>> memo;
        
        return dfs(s, 0, memo);
    }
    
    // 回溯 + 记忆化搜索: 搜索s[startIndex:]的所有分割方案
    vector<vector<string>> dfs1(string &s, 
                               int startIndex, 
                               unordered_map<int, vector<vector<string>>> &memo) {
                                   
        if (memo.count(startIndex)) return memo[startIndex];
        
        vector<vector<string>> res;
        if (startIndex == s.size()) {
            return res;
        }
        
        // check s[startIndex:startIndex + 1], ...., s[startIndex:-1]
        // (s[startIndex:]在循环外考虑, 因为没有postfix)
        for (int length = 1; length < s.size() - startIndex; ++length) {
            string prefix = s.substr(startIndex, length);
            if (!isPalindrome(prefix)) continue;
            vector<vector<string>> postfixes = dfs(s, startIndex + length, memo);
            
            for (auto postfix: postfixes) {
                vector<string> partition = {prefix};
                partition.insert(partition.end(), postfix.begin(), postfix.end());
                res.push_back(partition);
            }
        }
        
        // check s[startIndex:]这一整体string是否是palindrome
        string entirStr = s.substr(startIndex, s.size() - startIndex);
        if (isPalindrome(entirStr)) {
            res.push_back({entirStr});
        }
        
        memo[startIndex] = res;
        return res;
    }
    
    bool isPalindrome(string &s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            if (s[left] != s[right]) return false;
            ++left;
            --right;
        }
        return true;
    }
    
};