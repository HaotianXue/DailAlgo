/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        return dfs(1, n);
    }
    
    vector<TreeNode*> dfs(int left, int right) {
        string key = to_string(left) + "_" + to_string(right);
        if (cache.count(key)) return cache[key];
    
        vector<TreeNode*> res;
        if (left > right) {
            res.push_back(nullptr);
            return cache[key] = res;
        }
        
        for (int i = left; i <= right; ++i) {
            vector<TreeNode*> leftRes = dfs(left, i - 1);
            vector<TreeNode*> rightRes = dfs(i + 1, right);
            
            for (auto l: leftRes) {
                for (auto r: rightRes) {
                    TreeNode* root = new TreeNode(i);
                    root->left = l;
                    root->right = r;
                    res.push_back(root);
                }
            }
        }
        
        return cache[key] = res;
        
    }
    
private:
    unordered_map<string, vector<TreeNode*>> cache;
};