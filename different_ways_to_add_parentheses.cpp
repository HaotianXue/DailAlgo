// https://leetcode.com/problems/different-ways-to-add-parentheses/

namespace Op {
    int add(int a, int b) { return a + b; }
    int minus(int a, int b) { return a - b; }
    int multiply(int a, int b) { return a * b; }
}

class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        if (cache.count(expression)) return cache[expression];
        vector<int> res;
        for (int i = 0; i < expression.size(); ++i) {
            if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*') {
                // divide
                vector<int> left = diffWaysToCompute(expression.substr(0, i));
                vector<int> right = diffWaysToCompute(expression.substr(i + 1));
                
                function<int(int, int)> f;
                
                switch(expression[i]) {
                    case '+': f = Op::add; break;
                    case '-': f = Op::minus; break;
                    case '*': f = Op::multiply; break;
                }
                
                // combine answers(conquer)
                for (int a: left) {
                    for (int b: right) {
                        res.push_back(f(a, b));
                    }
                } 
            }
        }
        
        if (res.empty()) res.push_back(stoi(expression));
        
        return cache[expression] = res;
    }
    
private:
    unordered_map<string, vector<int>> cache;
};