https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/

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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size(), m = postorder.size();
        
        function<TreeNode*(int, int, int, int)> dfs = [&](int inStart, int inEnd, int posStart, int posEnd) -> TreeNode* {
            if (inStart > inEnd || posStart > posEnd) return NULL;
            if (inStart == inEnd) return new TreeNode(inorder[inStart]);
            // find root
            int rootVal = postorder[posEnd];
            TreeNode* root = new TreeNode(rootVal);
            // find index of root in inorder
            int rootIndex;
            for (int i = 0; i < inorder.size(); ++i) {
                if (rootVal == inorder[i]) {
                    rootIndex = i;
                    break;
                }
            }
            // find num of nodes in left/right subtree
            int lenLeft = rootIndex - inStart;
            root->left = dfs(inStart, inStart + lenLeft - 1, posStart, posStart + lenLeft - 1);
            root->right = dfs(rootIndex + 1, inEnd, posStart + lenLeft, posEnd - 1);
            
            return root;
        };
        
        return dfs(0, n - 1, 0, m - 1);
        
    }
};