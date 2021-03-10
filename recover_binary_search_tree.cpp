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

// Morris Traversal: O(n) time, O(1) space
class Solution {
public:
    
    
    // https://ghh3809.github.io/2018/08/06/morris-traversal/
    // https://www.acwing.com/solution/LeetCode/content/181/
    // https://github.com/grandyang/leetcode/issues/99
    void recoverTree(TreeNode* root) {
        
        if (!root) return;
        
        TreeNode* first = NULL, * second = NULL, * prev = NULL;
        
        TreeNode* node = root;
        
        auto visitNode = [&](TreeNode* node) {
            if (prev && prev->val > node->val) {
                if (!first) first = prev;
                second = node;
            }
            prev = node;
        };
        
        while (node) {
            if (!node->left) { // no left subtree => visit cur node and enter its right subtree
                visitNode(node);
                node = node->right;
            } else { // has left subtree => find cur node's precessor(say A)=> make A->right = node
                TreeNode* p = node->left;
                while (p->right && p->right != node) p = p->right;
                if (p->right) { // we have already visited p (as we already add link)
                    p->right = NULL; // remove the link
                    visitNode(node); // since node's precessor has been visited => all left subtree has been visited => visit cur node
                    node = node->right;
                }else { // we haven't visited this node
                    p->right = node; // add link to cur node as p is cur node's precessor
                    node = node->left;
                }
            }
        }
        swap(first->val, second->val);
    }
    
    
};



// O(n) time, O(h) space
class Solution {
public:
    
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