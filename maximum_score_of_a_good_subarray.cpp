https://leetcode.com/problems/maximum-score-of-a-good-subarray/

class Solution {
public:
    // two pointers start from k (one from k to left and the other from k to right)
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        int res = 0;
        for (int i = k, j = k, m = nums[k]; ;) {
            res = max(res, m * (j - i + 1));
            if (j - i + 1 == n) break;
            int left = i ? nums[i - 1] : -1;
            int right = j + 1 < n ? nums[j + 1] : -1;
            if (left >= right) {
                m = min(m, nums[--i]);
            } else {
                m = min(m, nums[++j]);
            }
        }
        return res;
    }
};