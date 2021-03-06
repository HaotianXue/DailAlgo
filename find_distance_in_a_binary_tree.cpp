// https://leetcode.com/problems/find-distance-in-a-binary-tree/
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

// Approach i: one pass
class Solution {
public:
    int findDistance(TreeNode* root, int p, int q) {
       if (p == q) return 0;
        
        function<int(TreeNode*, int, int, int)> getDist = [&](TreeNode* root, int p, int q, int depth) {
            if (!root) return 0;
            
            int left = getDist(root->left, p, q, depth + 1); // p or q's depth if found any
            int right = getDist(root->right, p, q, depth + 1);
            
            // if root is p or q(say p), we check if the other node q is on its subtree, if so, we use q's depth - p's depth
            // otherwise(the other node q is not on subtree) => we directly return p's depth
            if (root->val == p || root->val == q) return abs(max(left, right) - depth);
            
            // if both p and q lies on both sides of current root => current root is LCA of p and q
            // dist(root, p, q) = dist(root, p) + dist(root, q) - 2 * dist(root, LCA)
            if (left > 0 && right > 0) return left + right - 2 * depth;
            
            // either p or q or none of them is on subtree of current root
            // 1. either find p or q under current root => return that node's depth
            // 2. none of them found under current root => return 0
            return left > 0 ? left : right;
        };
        
        return getDist(root, p, q, 0);
        
    }
};

// Approach ii: first find lca and compute distance between lca and p/q
class Solution {
public:
    int findDistance(TreeNode* root, int p, int q) {
       
        function<TreeNode*(TreeNode*, int, int)> LCA = [&](TreeNode* node, int p, int q) {
            if (!node || node->val == p || node->val == q) return node;
            TreeNode* left = LCA(node->left, p, q);
            TreeNode* right = LCA(node->right, p, q);
            if (left && right) return node;
            return left ? left : right;
        };
        
        TreeNode* lca = LCA(root, p, q);
        
        function<pair<bool, int>(TreeNode*, int)> getDist = [&](TreeNode* node, int val) {
            if (!node) return make_pair(false, -1);
            if (node->val == val) return make_pair(true, 0);
            
            pair<bool, int> left = getDist(node->left, val);
            pair<bool, int> right = getDist(node->right, val);
            
            if (left.first) return make_pair(true, 1 + left.second);
            if (right.first) return make_pair(true, 1 + right.second);
            
            return make_pair(false, -1);
        };
        
        return getDist(lca, p).second + getDist(lca, q).second;
    }
};