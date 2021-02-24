// https://leetcode.com/problems/prefix-and-suffix-search

// Approach 1: build two tries: one for prefix and the other one for suffix
class TrieNode {
public:
    vector<TrieNode*> sons;
    vector<int> startingWords; // index of words
    bool isWord;
    
    TrieNode() {
        sons = vector<TrieNode*>(26, NULL);
        isWord = false;
    }
    
};

class Trie {
public:
    TrieNode* preRoot, * sufRoot;
    
    Trie() {
        preRoot = new TrieNode();
        sufRoot = new TrieNode();
    }
    
    void insert(string &word, int index) {
        TrieNode* node = preRoot;
        for (char &c: word) {
            int offset = c - 'a';
            if (!node->sons[offset]) node->sons[offset] = new TrieNode();
            node->startingWords.push_back(index);
            node = node->sons[offset];
        }
        node->startingWords.push_back(index);
        node->isWord = true;
        
        node = sufRoot;
        for (int i = word.size() - 1; i >= 0; --i) {
            int offset = word[i] - 'a';
            if (!node->sons[offset]) node->sons[offset] = new TrieNode();
            node->startingWords.push_back(index);
            node = node->sons[offset];
        }
        node->startingWords.push_back(index);
        node->isWord = true;
    }
    
    int getWordIndexByPreSuff(string& prefix, 
                              string& suffix) {
        TrieNode* node = preRoot;
        for (char &c: prefix) {
            int offset = c - 'a';
            if (!node->sons[offset]) return -1;
            node = node->sons[offset];
        }
        vector<int> preWords = node->startingWords;
        node = sufRoot;
        for (int i = suffix.size() - 1; i >= 0; --i) {
            int offset = suffix[i] - 'a';
            if (!node->sons[offset]) return -1;
            node = node->sons[offset];
        }
        vector<int> sufWords = node->startingWords;
        for (int i = preWords.size() - 1, j = sufWords.size() - 1; i >= 0 &&j >= 0; ) {
            if (preWords[i] == sufWords[j]) return preWords[i];
            if (preWords[i] > sufWords[j]) --i;
            else --j;
        }
        return -1;
    }
    
};


class WordFilter {
private:
    Trie tree;
public:
    WordFilter(vector<string>& words) {
        for (int i = 0; i < words.size(); ++i) {
            tree.insert(words[i], i);
        }
    }
    
    int f(string prefix, string suffix) {
        return tree.getWordIndexByPreSuff(prefix, suffix);
    }
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(prefix,suffix);
 */