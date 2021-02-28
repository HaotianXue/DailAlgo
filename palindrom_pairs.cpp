// https://leetcode.com/problems/palindrome-pairs/
class TrieNode {
public:
    int id;
    vector<TrieNode*> sons;
    vector<int> pos;
    bool isNum;
    
    TrieNode() {
        id = -1;
        sons = vector<TrieNode*>(26, NULL);
        isNum = false;
    }
};


class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        
        vector<vector<int>> res;
        if (words.size() == 0) return res;
            
        TrieNode* root = new TrieNode();
        
        function<void(string&, int)> insert = [&](string& word, int index) {
            TrieNode* node = root;
            for (int i = word.size() - 1; i >= 0; --i) {
                if (isPalindrome(word, 0, i)) node->pos.push_back(index);
                int offset = word[i] - 'a';
                if (!node->sons[offset]) node->sons[offset] = new TrieNode();
                node = node->sons[offset];
            }
            node->isNum = true;
            node->pos.push_back(index);
            node->id = index;
        };
        
        function<void(string&, int)> search = [&](string& word, int index) {
            TrieNode* node = root;
            for (int i = 0; i < word.size(); ++i) {
                if (node->id >= 0 && node->id != index && isPalindrome(word, i, word.size() - 1)) {
                    res.push_back({index, node->id});
                }
                int offset = word[i] - 'a';
                if (!node->sons[offset]) return;
                node = node->sons[offset];
            }
            for (int i: node->pos) {
                if (i == index) continue;
                res.push_back({index, i});
            }
        };
        
        for (int i = 0; i < words.size(); ++i) {
            insert(words[i], i);
        }
        for (int i = 0; i < words.size(); ++i) {
            search(words[i], i);
        }
        
        return res;
        
        
        
        
    }
    
    bool isPalindrome(string& s, int start, int end) {
        while (start < end) {
            if (s[start] != s[end]) return false;
            ++start;
            --end;
        }
        return true;
    }
    
};