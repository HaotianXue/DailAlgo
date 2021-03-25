// https://leetcode.com/problems/replace-the-substring-for-balanced-string/

class Solution {
public:
    // two pointers: [i, j] is the interval we want to replace
    // as long as each of chars apperas <= n/4 outside [i, j] => [i, j] is legal
    // for each j, we want to find the closest i such that s is balanced after [i, j] is replaced
    int balancedString(string s) {
        int n = s.size();
        
        unordered_map<char, int> count = {{'Q', 0}, {'W', 0}, {'E', 0}, {'R', 0}};
        
        auto isValid = [&]() {
            return count['Q'] <= n / 4 && count['W'] <= n / 4 && count['E'] <= n / 4 && count['R'] <= n / 4;
        };
        
        for (char& c: s) ++count[c];
        
        if (isValid()) return 0;
        
        int start = 0, minLen = n;
        
        for (int end = 0; end < n; ++end) {
            --count[s[end]]; // enter the sliding window
            while (start <= end && isValid()) {
                minLen = min(minLen, end - start + 1);
                ++count[s[start++]]; // left pointer of sliding window move one ahead
            }
        }
        
        return minLen;
    }
};