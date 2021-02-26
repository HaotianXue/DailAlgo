// https://leetcode.com/problems/maximum-xor-with-an-element-from-array/
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
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        sort(nums.begin(), nums.end());
        for (int i = 0; i < queries.size(); ++i) {
            queries[i].push_back(i);
        }
        auto cmp = [](const vector<int>& q1, const vector<int>& q2) {return q1[1] < q2[1];};
        sort(queries.begin(), queries.end(), cmp);
        
        Trie tree;
        function<int(int)> search = [&](int num) {
            TrieNode* node = tree.root;
            int sum = 0;
            for (int i = 31; i >= 0; --i) {
                if (!node) return -1;
                int curBit = (num >> i) & 1;
                if (node->sons[curBit ^ 1]) {
                    sum |= (1 << i);
                    node = node->sons[curBit ^ 1];
                } else {
                    node = node->sons[curBit];
                }
            }
            return sum;
        };
        
        vector<int> res(queries.size());
        int i = 0;
        for (auto q: queries) {
            // insert nums that are <= m of current query => search safely on the Trie
            while (i < nums.size() && nums[i] <= q[1]) {
                tree.insert(nums[i++]);
            } 
            res[q[2]] = search(q[0]);
        }
        return res;
    }
};