https://leetcode.com/problems/divide-chocolate/

class Solution {
public:
    
    int maximizeSweetness(vector<int>& sweetness, int K) {
        
        if (sweetness.size() == 0) return 0;
        
        int left = INT_MAX, right = 0;
        for (int s: sweetness) {
            left = min(left, s);
            right += s;
        }
        
        if (K + 1 == 1) return right;
        if (K + 1 == sweetness.size()) return left;
        
        auto canSplit = [&](int target) -> bool {
            int num = 1, accumulated = 0;
            for (int s: sweetness) {
                if ((accumulated += s) > target) { // split the chocolate once cur value exceeds the target(min sweetness)
                    ++num;
                    accumulated = 0;
                } 
            }
            return num <= K + 1;
        };
        
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (canSplit(mid)) right = mid;
            else left = mid;
        }
        
        if (canSplit(left)) return left;
        if (canSplit(right)) return right;
        
        return -1;
    }
    
};