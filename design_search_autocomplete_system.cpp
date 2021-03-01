// https://leetcode.com/problems/design-search-autocomplete-system/
struct cmp {
    bool operator() (const pair<string, int> &p1, const pair<string, int> &p2) const {
        if (p1.second != p2.second) {
            return p1.second > p2.second;
        }
        return p1.first < p2.first;
    }
};

class TrieNode {
public:
    vector<TrieNode*> sons;
    set<pair<string, int>, cmp> history;
    unordered_map<string, int> timeMap;
    
    TrieNode() {
        sons.resize(27, NULL);
    }
    
};


class Trie {
public:
    TrieNode* root;
    
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string &sentence, int time) {
        TrieNode* node = root;
        
        function<void(TrieNode*, string&, int)> updateHistory = [&](TrieNode* node, string &word, int time) {
            if (node->timeMap.count(word)) {
                int oldTime = node->timeMap[word];
                node->history.erase(make_pair(word, oldTime)); 
                node->history.insert(make_pair(word, time + oldTime));
                node->timeMap[word] = time + oldTime;
            } else {
                node->history.insert(make_pair(word, time));
                node->timeMap[word] = time;
            }
        };
        
        for (char &c: sentence) {
            int offset;
            if (c == ' ') offset = 26;
            else offset = c - 'a';
            if (!node->sons[offset]) node->sons[offset] = new TrieNode();
            updateHistory(node, sentence, time);
            node = node->sons[offset];
        }
        
        updateHistory(node, sentence, time);
    }
    
};


class AutocompleteSystem {
private:
    string curInput;
    Trie tree;
    TrieNode* curNode;
public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        curNode = tree.root;
        for (int i = 0; i < sentences.size(); ++i) {
            tree.insert(sentences[i], times[i]);
        }
    }
    
    vector<string> input(char c) {
        if (c == '#') {
            tree.insert(curInput, 1);
            curInput = "";
            curNode = tree.root;
            return {};
        }
        curInput += c;
        TrieNode* node = curNode;
        for (char &c: curInput) {
            int offset;
            if (c == ' ') offset = 26;
            else offset = c - 'a';
            if (!node->sons[offset]) return {};
            node = node->sons[offset];
        }
        auto history = node->history;
        vector<string> res;
        int count = 0;
        for (auto p: history) {
            if (count == 3) break;
            res.push_back(p.first);
            ++count;
        }
        return res;
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */