// https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/
class TrieNode {
public:
    vector<TrieNode*> sons;
    
    TrieNode() {
        sons = vector<TrieNode*>(2, NULL);
    }
    
};

class Trie {
public:
    TrieNode* root;
    
    Trie() {
        root = new TrieNode();
    }
    
    void insert(int num) {
        TrieNode* node = root;
        for (int i = 31; i >= 0; --i) {
            int curBit = (num >> i) & 1;
            if (!node->sons[curBit]) node->sons[curBit] = new TrieNode();
            node = node->sons[curBit];
        }
    }
    
};


class Solution {
public:
    /**
     * @param nums: 
     * @return: the maximum result of ai XOR aj, where 0 ≤ i, j < n
     */
    int findMaximumXOR(vector<int> &nums) {
        // Write your code here
        if (nums.size() == 0) return 0;
        Trie tree;
        for (int& num: nums) {
            tree.insert(num);
        }
        int res = INT_MIN;
        for (int& num: nums) {
            TrieNode* node = tree.root;
            int curSum = 0;
            for (int i = 31; i >= 0; --i) {
                int curBit = (num >> i) & 1;
                if (node->sons[curBit ^ 1]) {
                    curSum |= (1 << i);
                    node = node->sons[curBit ^ 1];
                } else { // same as current bit => xor -> 0(no need to add to sum)
                    node = node->sons[curBit];
                }
            }
            res = max(res, curSum);
        }
        return res;
    }
};
