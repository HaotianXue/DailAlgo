// https://leetcode.com/problems/build-binary-expression-tree-from-infix-expression


/**
 * Definition for a binary tree node.
 * struct Node {
 *     char val;
 *     Node *left;
 *     Node *right;
 *     Node() : val(' '), left(nullptr), right(nullptr) {}
 *     Node(char x) : val(x), left(nullptr), right(nullptr) {}
 *     Node(char x, Node *left, Node *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // Standard parser implementation based on this BNF
    // s := expression
    // expression := term | term { [+,-] term] }
    // term := factor | factor { [*,/] factor] }
    // factor :== digit | '(' expression ')'
    // digit := [0..9]
    Node* expTree(string s) {
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
            char rightBracket = tokens[pos++];
            return exp;
        } else {
            return new Node(tokens[pos++]);
        }
    }
    
};