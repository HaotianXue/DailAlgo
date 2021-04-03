https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/

class Solution {
public:
    // binary search to search for answers
    int shipWithinDays(vector<int>& weights, int D) {
        int left = *max_element(weights.begin(), weights.end());
        int right = accumulate(weights.begin(), weights.end(), 0);
        
        auto isValid = [&](int capacity) {
            int daysRequired = 1, accumulated = 0;
            for (int w: weights) {
                if ((accumulated += w) > capacity) {
                    accumulated = w;
                    ++daysRequired;
                } 
            }
            return daysRequired <= D;
        };
        
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (!isValid(mid)) left = mid;
            else right = mid;
        }
        
        if (isValid(left)) return left;
        if (isValid(right)) return right;
        
        return -1;
    }
};