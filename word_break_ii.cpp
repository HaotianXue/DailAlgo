// https://leetcode.com/problems/word-break-ii/
class TrieNode {
public:
    unordered_map<char, TrieNode*> sons;
    string word;
    bool isWord;
    
    TrieNode() {
        isWord = false;
    }
};

class Trie {
public:
    TrieNode* root;
    
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string &word) {
        TrieNode* node = root;
        for (char c: word) {
            if (!node->sons.count(c)) node->sons[c] = new TrieNode();
            node = node->sons[c];
        }
        node->word = word;
        node->isWord = true;
    }
    
};

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        if (wordDict.size() == 0) return {};
        
        Trie tree;
        for (string word: wordDict) {
            tree.insert(word);
        }

        unordered_map<int, vector<string>> memo;
        
        // 搜索以s[pos:]的所有可能的句子
        function<vector<string>(int, TrieNode*)> dfs = [&](int pos, TrieNode* node) {
            if (memo.count(pos)) return memo[pos];
            vector<string> res;
            if (pos == s.size()) return res;
            TrieNode* cur = node;
            int len;
            for (len = 1; len <= s.size() - pos; ++len) {
                if (!cur->sons.count(s[pos + len - 1])) break;
                cur = cur->sons[s[pos + len - 1]];
                if (!cur->isWord) continue;
                string prefix = s.substr(pos, len);
                if (len == s.size() - pos) {
                    res.push_back(prefix);
                }
                vector<string> postfixes = dfs(pos + len, node);
                for (string postfix: postfixes) {
                    res.push_back(prefix + " " + postfix);
                }
            }
            memo[pos] = res;
            return res;
            
        };
        
        return dfs(0, tree.root);
    }
};