// https://leetcode.com/problems/design-add-and-search-words-data-structure
class TrieNode {
public:
    vector<TrieNode*> sons;
    bool isWord;
    
    TrieNode() {
        sons = vector<TrieNode*>(26, NULL);
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
        for (char &c: word) {
            int offset = c - 'a';
            if (!node->sons[offset]) node->sons[offset] = new TrieNode();
            node = node->sons[offset];
        }
        node->isWord = true;
    }
    
};

class WordDictionary {
private:
    Trie tree;
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        
    }
    
    void addWord(string word) {
        tree.insert(word);
    }
    
    bool search(string word) {
        function<bool(TrieNode*, int)> dfs = [&](TrieNode* node, int pos) {
            if (!node) return false;
            if (pos == word.size()) return node->isWord;
            if (word[pos] >= 'a' && word[pos] <= 'z') {
                int offset = word[pos] - 'a';
                if (!node->sons[offset]) return false;
                return dfs(node->sons[offset], pos + 1);
            } else if (word[pos] == '.') {
                for (int i = 0; i < 26; ++i) {
                    if (!node->sons[i]) continue;
                    if (dfs(node->sons[i], pos + 1)) return true;
                }
            }
            return false;
        };
        
        return dfs(tree.root, 0);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */