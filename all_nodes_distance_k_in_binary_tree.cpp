//https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        if (!root || !target) return {};
        res.clear();
        getDis(root, target, K);
        return res;        
    }
private:
    vector<int> res;
    
    int getDis(TreeNode* root, TreeNode* target, int K) {
        if (root == nullptr || target == nullptr) return -1;
        if (root == target) {
            collect(target, K);
            return 0;
        }
        int l = getDis(root->left, target, K);
        int r = getDis(root->right, target, K);
        
        if (l >= 0) {
            if (l == K - 1) res.push_back(root->val);
            collect(root->right, K - l - 2);
            return l + 1;
        }
        
        if (r >= 0) {
            if (r == K - 1) res.push_back(root->val);
            collect(root->left, K - r -2);
            return r + 1;
        }
        
        return -1;
    }
    
    void collect(TreeNode* root, int d) {
        if (root == nullptr || d < 0) return;
        if (d == 0) {
            res.push_back(root->val);
            return;
        }
        collect(root->left, d - 1);
        collect(root->right, d - 1);
    }
    
};