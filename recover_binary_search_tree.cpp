// https://leetcode.com/problems/recover-binary-search-tree/
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
    
    // O(n) time, O(h) space
    void recoverTree(TreeNode* root) {
        
        function<void(TreeNode*)> inOrder = [&](TreeNode* root) {
            if (!root) return;
            inOrder(root->left);
            
            if (prev && prev->val > root->val) {
                if (!first) first = prev;
                second = root;
            }
            prev = root;
            
            inOrder(root->right);
        };
        
        inOrder(root);
        swap(first->val, second->val);
        
    }
    
private:
    TreeNode* first, * second, * prev;
    
    
};