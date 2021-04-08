https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/

class Solution {
public:
    
    // if a node is not null => it must has two children => check left and right recursively
    // if a node is null => it must be #
    bool isValidSerialization(string preorder) {
        int pos = 0, n = preorder.size();
        
        function<bool(int&)> isValid = [&](int& pos) {
            if (pos >= n) return false;
            if (isdigit(preorder[pos])) {
                while (isdigit(preorder[pos])) ++pos;
                return isValid(++pos) && isValid(++pos);
            }
            return preorder[pos++] == '#';
        };
        
        return isValid(pos) && pos == n;
    }
};