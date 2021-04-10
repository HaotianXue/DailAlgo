https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/

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
    TreeNode* recoverFromPreorder(string S) {    
        int n = S.size();
        int pos = 0, d = 0;
        
        function<TreeNode*(int)> dfs = [&](int depth) -> TreeNode* {
            if (pos >= n) return NULL;
            int rootVal = 0;
            while (isdigit(S[pos])) {
                rootVal = 10 * rootVal + (S[pos++] - '0');
            }
            TreeNode* root = new TreeNode(rootVal);
            int numDashes = 0;
            while (S[pos] == '-') {
                ++pos;
                ++numDashes;
            }
            d = numDashes;
            if (numDashes == depth + 1) { // has left child
                root->left = dfs(depth + 1);
            } else { // no children => leaf node, just return
                return root;
            }
            
            // check if it has right child
            if (d == depth + 1) {
                root->right = dfs(depth + 1);
            }
            
            return root;
            
        };
        
        return dfs(0);
        
    }
};