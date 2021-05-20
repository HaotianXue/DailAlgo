// https://leetcode.com/problems/different-ways-to-add-parentheses/

namespace Op {
    int add(int a, int b) { return a + b; }
    int minus(int a, int b) { return a - b; }
    int multiply(int a, int b) { return a * b; }
}

class Solution {
public:
    // 1 涉及括号组合类的一般要使用dfs。这里并不是真实添加括号，每个符号将表达式分为left,right两部分。对应的结果集合组合计算。
    // 2 递归遍历left, right部分，直到表达式为纯数字。 对于 表达式exp，可以使用map缓存结果，递归遍历时可以快速返回结果
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