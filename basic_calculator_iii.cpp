https://leetcode.com/problems/basic-calculator-iii/


class Node {
public:
    char op;
    int val;
    Node* left;
    Node* right;
    Node() : op(' '), val(0), left(nullptr), right(nullptr) {}
    Node(int x) : op(' '), val(x), left(nullptr), right(nullptr) {}
    Node(char x, Node* left, Node* right) : op(x), val(0), left(left), right(right) {}
};

class Solution {
public:
    
    // Standard parser implementation based on this BNF
    // s := expression
    // expression := term | term { [+,-] term] }
    // term := factor | factor { [*,/] factor] }
    // factor :== {digit} | '(' expression ')'
    // digit := [0..9]
    int calculate(string s) {
        Node* root = expTree(s);
        return eval(root);
    }
    
    int eval(Node* root) { // in-order traversal
        if (root->left == nullptr && root->right == nullptr) return root->val;
        char op = root->op;
        int left = eval(root->left);
        int right = eval(root->right);
        if (op == '+') return left + right;
        if (op == '-') return left - right;
        if (op == '*') return left * right;
        if (op == '/') return left / right;
        return -1;
    }
    
    Node* expTree(string& s) {
        vector<char> tokens(s.begin(), s.end());
        int pos = 0;
        return parseExpression(tokens, pos);
    }
    
    Node* parseExpression(vector<char>& tokens, int& pos) {
        Node* lhs = parseTerm(tokens, pos);
        while (pos < tokens.size() && (tokens[pos] == '+' || tokens[pos] == '-')) {
            char op = tokens[pos++];
            Node* rhs = parseTerm(tokens, pos);
            lhs = new Node(op, lhs, rhs);
        }
        return lhs;
    }
    
    Node* parseTerm(vector<char>& tokens, int& pos) {
        Node* lhs = parseFactor(tokens, pos);
        while (pos < tokens.size() && (tokens[pos] == '*' || tokens[pos] == '/')) {
            char op = tokens[pos++];
            Node* rhs = parseFactor(tokens, pos);
            lhs = new Node(op, lhs, rhs);
        }
        return lhs;
    }
    
    Node* parseFactor(vector<char>& tokens, int& pos) {
        if (tokens[pos] == '(') {
            char leftBracket = tokens[pos++]; // consume left bracket
            Node* exp = parseExpression(tokens, pos);
            char rightBracket = tokens[pos++]; // consume right bracket
            return exp;
        } else {
            int res = 0;
            while (pos < tokens.size() && isdigit(tokens[pos])) {
                res = res * 10 + (tokens[pos++] - '0');
            }
            return new Node(res);
        }
    }
};