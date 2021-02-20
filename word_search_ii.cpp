// https://leetcode.com/problems/word-search-ii/
class TrieNode {
public:
    vector<TrieNode*> sons;
    bool isWord;
    string word;
    
    TrieNode() {
        sons.resize(26, NULL);
        isWord = false;
    }
    
    ~TrieNode() {
        for (auto son: sons) {
            delete son;
        }
    }
    
};

class Trie {
public:
    TrieNode* root;
    
    Trie() {
        root = new TrieNode();
    }
    
    ~Trie() {
        delete root;
    }
    
    void insert(string word) {
        TrieNode* curNode = root;
        for (char c: word) {
            int offset = c - 'a';
            if (!curNode->sons[offset]) {
                curNode->sons[offset] = new TrieNode();
            }
            curNode = curNode->sons[offset];
        }
        curNode->isWord = true;
        curNode->word = word;
    }
       
};



class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if (board.size() == 0 || words.size() == 0) return {};
        Trie tree;
        for (string w: words) {
            tree.insert(w);
        }
        
        int n = board.size(), m = board[0].size();
        
        function<bool(int, int)> isValid = [&](int x, int y) {
            return x >= 0 && x < n && y >= 0 && y < m;
        };
        
        vector<string> res;
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        
        function<void(int, int, TrieNode*)> dfs = [&](int x, int y, TrieNode* node) {
            if (node == NULL) return;
            if (node->isWord) {
                node->isWord = false;
                res.push_back(node->word); 
            }
            int dirs[2][4] = {{1, -1, 0, 0}, {0, 0, 1, -1}};
            
            for (int i = 0; i < 4; ++i) {
                int dx = x + dirs[0][i];
                int dy = y + dirs[1][i];
                if (!isValid(dx, dy)) continue;
                if (visited[dx][dy]) continue;
                int offset = board[dx][dy] - 'a';
                if (!node->sons[offset]) continue;
                visited[dx][dy] = true;
                dfs(dx, dy, node->sons[offset]);
                visited[dx][dy] = false;
            }
        };
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0 ; j < m; ++j) {
                int offset = board[i][j] - 'a';
                if (!tree.root->sons[offset]) continue;
                visited[i][j] = true;
                dfs(i, j, tree.root->sons[offset]);
                visited[i][j] = false;
            }
        }
        
        return res;
    }
    
};