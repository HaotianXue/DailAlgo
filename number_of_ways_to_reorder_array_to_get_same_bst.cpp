// https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/

class Solution {
public:
    // For a given root (first element of the array), 
    // we can split the array into left children (nums[i] < nums[0]) and right children (nums[i] > nums[0]). 
    // Assuming there are l nodes for the left and r nodes for the right. 
    // We have C(l + r, l) different ways to insert l elements into a (l + r) sized array. 
    // Within node l or r nodes, we have ways(left) or ways(right) different ways to re-arrange those nodes. 
    // So the total # of ways is: C(l + r, l) * ways(l) * ways(r)
    int numOfWays(vector<int>& nums) {
        const int modNum = 1e9 + 7;
        
        int n = nums.size();
        // use yanghui triangle to compute C(i, j)
        vector<vector<int>> cnk(n + 1, vector<int>(n + 1, 1));
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                cnk[i][j] = (cnk[i - 1][j] + cnk[i - 1][j - 1]) % modNum;
            }
        }
        
        function<int(vector<int>&)> dfs = [&](vector<int>& nums) {
            if (nums.size() <= 2) return 1;
            vector<int> left;
            vector<int> right;
            for (int i = 1; i < nums.size(); ++i) {
                if (nums[i] > nums[0]) right.push_back(nums[i]);
                else left.push_back(nums[i]);
            }
            long res = cnk[nums.size() - 1][left.size()];
            res = (res * dfs(left)) % modNum;      
            res = (res * dfs(right)) % modNum;
            return static_cast<int>(res);
        };
        
        return dfs(nums) - 1;
        
    }
};