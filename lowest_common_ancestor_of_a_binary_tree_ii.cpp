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

// Approach i: dont use golbal variables
class resultType {
public:
    bool existP, existQ;
    TreeNode* node; // p or q or their LCA
    
    resultType(bool existP, bool existQ, TreeNode* node): existP(existP), existQ(existQ), node(node) {}
    
};


class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        
        // use dfs to search if Tree with given root has node p, q, and meanwhile find its LCA if p and q exists
        function<resultType(TreeNode*, TreeNode*, TreeNode*)> dfs = [&](TreeNode* root, TreeNode* p, TreeNode* q) -> resultType {
            if (!root || !p || !q) return resultType(false, false, NULL);
            resultType left = dfs(root->left, p, q);
            resultType right = dfs(root->right, p, q);
            
            bool existP = left.existP || right.existP || root == p;
            bool existQ = left.existQ || right.existQ || root == q;
            
            if (p == root || q == root) { // either p or q is root
                return resultType(existP, existQ, root);
            }
            if (left.node && right.node) { // p and q found on both sides
                return resultType(existP, existQ, root);
            }
            if (left.node) { // left subtree has p or q or its LCA
                return resultType(existP, existQ, left.node);
            }
            if (right.node) { // right subtree has p or q or its LCA
                return resultType(existP, existQ, right.node);
            }
            return resultType(false, false, NULL); // both p and q doesn't exist in tree
        }; 
        
        resultType res = dfs(root, p, q);
        if (res.existP && res.existQ) return res.node;
        return NULL;
    }
    
};


// Approach ii: use global variables
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