class Solution {
public:
    bool checkValidString(string s) {
        int n = s.size();
        
        int N = 110;
        vector<vector<vector<int>>> memo(N, vector<vector<int>>(N, vector<int>(N, -1)));
        
        function<bool(int, int, int)> check = [&](int start, int leftCount, int rightCount) -> bool {
            if (memo[start][leftCount][rightCount] != -1) return memo[start][leftCount][rightCount];
            if (start == n) return leftCount == rightCount;
            if (rightCount > leftCount) return false;
            if (s[start] == '(') return memo[start][leftCount][rightCount] = check(start + 1, leftCount + 1, rightCount);
            if (s[start] == ')') return memo[start][leftCount][rightCount] = check(start + 1, leftCount, rightCount + 1);
            
            return memo[start][leftCount][rightCount] = check(start + 1, leftCount, rightCount) ||
                check(start + 1, leftCount + 1, rightCount) ||
                check(start + 1, leftCount, rightCount + 1);
        };
        
        return check(0, 0, 0);
    }
};