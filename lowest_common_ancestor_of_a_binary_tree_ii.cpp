// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-ii/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        bool foundP = false, foundQ = false;
        
        function<TreeNode*(TreeNode*, TreeNode*, TreeNode*)> LCA = [&](TreeNode* root, TreeNode* p, TreeNode* q)->TreeNode* {
            if (!root || !p || !q) return NULL;
            
            // dfs should first reach leaves(as we need to search entire tree)
            TreeNode* left = LCA(root->left, p, q);
            TreeNode* right = LCA(root->right, p, q);
            
            if (root == p) {
                foundP = true;
                return root;
            }
            if (root == q) {
                foundQ = true;
                return root;
            }
            if (left && right) return root;
            return left ? left : right;
        };
        
        TreeNode* res = LCA(root, p, q);
        if (foundP && foundQ) return res;
        return NULL;        
    }
    
};