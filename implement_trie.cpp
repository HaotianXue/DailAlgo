// https://leetcode.com/problems/implement-trie-prefix-tree/
class TrieNode {
public:
    vector<TrieNode*> sons;
    bool isWord;
    string word;
    
    TrieNode() {
        sons = vector<TrieNode*>(26, NULL);
        isWord = false;
    }
    
};

class Trie {
public:
    
    TrieNode* root;
    
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* node = root;
        for (char c: word) {
            int offset = c - 'a';
            if (!node->sons[offset]) node->sons[offset] = new TrieNode();
            node = node->sons[offset];
        }
        node->isWord = true;
        node->word = word;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* node = root;
        for (char c: word) {
            int offset = c - 'a';
            if (!node->sons[offset]) return false;
            node = node->sons[offset];
        }
        return node->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c: prefix) {
            int offset = c - 'a';
            if (!node->sons[offset]) return false;
            node = node->sons[offset];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */