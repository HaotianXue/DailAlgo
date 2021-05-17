// https://leetcode.com/problems/score-of-parentheses/

class Solution {
public:
    int scoreOfParentheses(string s) {
        
        
        function<int(int, int)> score = [&](int start, int end) {
            if (end - start == 1) return 1; // base case: ()
            int match = 0;
            for (int i = start; i < end; ++i) {
                if (s[i] == '(') ++match;
                if (s[i] == ')') --match;
                if (match == 0) { // A + B
                    return score(start, i) + score(i + 1, end);
                }
            }
            return 2 * score(start + 1, end - 1); // (A) => 2 * A
        };
        
        return score(0, s.size() - 1);
        
    }
};