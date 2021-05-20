https://leetcode.com/problems/unique-binary-search-trees/

class Solution {
public:
    int numTrees(int n) {
        return dfs(1, n);
    }
    
    int dfs(int left, int right) {
        string key = to_string(left) + '-' + to_string(right);
        if (cache.count(key)) return cache[key];
        if (left > right) return 1;
        
        int res = 0;
        for (int i = left; i <= right; ++i) {
            int leftCount = dfs(left, i - 1);
            int rightCount = dfs(i + 1, right);
            res += leftCount * rightCount;
        }
        
        return cache[key] = res;
    }
    
private:
    unordered_map<string, int> cache;
};