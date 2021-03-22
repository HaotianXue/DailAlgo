// https://leetcode.com/problems/grumpy-bookstore-owner/
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
        // keep a sliding window of size X
        int base = 0;
        int window = 0, bestWindow = 0;
        for (int i = 0; i < customers.size(); ++i) {
            (grumpy[i] ? window: base) += customers[i];
            if (i >= X && grumpy[i - X]) window -= customers[i - X];
            bestWindow = max(window, bestWindow);
        }
        return base + bestWindow;
    }
};