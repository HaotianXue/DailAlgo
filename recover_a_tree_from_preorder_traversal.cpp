// https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/

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

    // Approach I: 每次先算dash的数量和当前深度做比较
    TreeNode* recoverFromPreorder(string S) {    
        int i = 0;
        
        auto getD = [](string& s, int& i) {
            int d = 0;
            while (i < s.length() && s[i] == '-') {
                ++d; 
                ++i;
            }
            return d;
        };
        
        auto getVal = [](string& s, int& i) {
            int val = 0;
            while (i < s.length() && isdigit(s[i]))
                val = val * 10 + (s[i++] - '0');       
            return val;
        };
        
        // Check the current depth and expected depth, if don’t match, return nullptr.
        // https://zxi.mytechroad.com/blog/leetcode/leetcode-weekly-contest-132/
        function<TreeNode*(int)> recover = [&](int depth) -> TreeNode* {
            const int d = getD(S, i);
            if (d != depth) { 
                i -= d; 
                return nullptr; 
            }    
            auto root = new TreeNode(getVal(S, i));
            root->left = recover(d + 1);    
            root->right = recover(d + 1);
            return root; 
        };
        
        
        
        return recover(0);
        
    }

    // Approach II: 算当前节点后面的dash数量, 与当前深度+1做比较看是否是自己的左/右孩子
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
            // right now d is the number of dashes of the node right next to the current root's left child
            if (d == depth + 1) {
                root->right = dfs(depth + 1);
            }
            
            return root;
            
        };
        
        return dfs(0);
        
    }
};