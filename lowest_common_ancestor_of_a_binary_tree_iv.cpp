// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iv/
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
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
        unordered_set<TreeNode*> set(nodes.begin(), nodes.end());
        
        function<TreeNode*(TreeNode*)> LCA = [&](TreeNode* node) -> TreeNode* {
            if (!node) return NULL;
            if (set.count(node)) return node;
            
            TreeNode* left = LCA(node->left);
            TreeNode* right = LCA(node->right);
            
            if (left && right) return node;
            return left ? left : right;
        };
        
        return LCA(root);
    }
};