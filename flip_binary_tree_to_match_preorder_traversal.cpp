https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/


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

    // Approach I
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        // pre-order traversal
        // 1. 定义布尔类型的递归，如果当前结点和子树已经不可能和给定的游历顺序匹配，则返回 false；否则返回 true。
        // 2. 当前结点为空，返回 true；如果当前结点的值和给定的游历顺序的下一个值不相等，返回 false；
        // 3. 通过了 2 之后，首先递归左子树和右子树，如果二者返回值都是 true，则返回 true；
        // 4. 如果 3 不成功，则递归右子树和左子树，如果二者返回值都是 true，则答案中记录当前结点，返回 true；
        // 5. 都不成功返回 false;
        vector<int> flips;
        int pos = 0;
        
        function<bool(TreeNode*)> dfs = [&](TreeNode* root) {
            if (!root) return true;
            if (root->val != voyage[pos]) return false;
            
            ++pos;
            
            if (dfs(root->left) && dfs(root->right)) {
                return true;
            }
            
            if (dfs(root->right) && dfs(root->left)) {
                flips.push_back(root->val);
                return true;
            }
            
            return false;
        };
        
        if (!dfs(root)) return {-1};
        return flips;
    }

    // Approach II
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        // pre-order traversal
        vector<int> flips;
        int pos = 0;
        
        function<bool(TreeNode*)> dfs = [&](TreeNode* root) {
            if (!root) return true;
            if (root->val != voyage[pos]) return false;
            
            if (root->left && root->left->val != voyage[pos + 1]) { // need flip
                swap(root->left, root->right);
                flips.push_back(root->val);
            }
            ++pos;
            if (!dfs(root->left)) return false;
            if (!dfs(root->right)) return false;
            return true;
        };
        
        if (!dfs(root)) return {-1};
        return flips;
    }
};