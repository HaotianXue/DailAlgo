https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        
        int n = preorder.size(), m = inorder.size();
        
        // construct binary tree from preorder[preLeft:preRight + 1] and inorder[inLeft:inRight + 1]
        function<TreeNode*(int, int, int, int)> dfs = [&](int preLeft, int preRight, int inLeft, int inRight) ->TreeNode* {
            if (preLeft > preRight || inLeft > inRight) return NULL;
            if (preLeft == preRight) return new TreeNode(preorder[preLeft]);
            // find root
            int rootVal = preorder[preLeft];
            TreeNode* root = new TreeNode(rootVal);
            
            // find index of root in inorder
            int rootIndex;
            for (int i = inLeft; i <= inRight; ++i) {
                if (rootVal == inorder[i]) {
                    rootIndex = i; 
                    break;
                }
            }
            
            // find numer of nodes in subtree
            int lenLeft = rootIndex - inLeft;
            root->left = dfs(preLeft + 1, preLeft + lenLeft, inLeft, inLeft + lenLeft - 1);
            root->right = dfs(preLeft + lenLeft + 1, preRight, rootIndex + 1, inRight);
            
            return root;
                       
        };
        
        return dfs(0, n - 1, 0, m - 1);
        
    }
};