// https://leetcode.com/problems/special-array-with-x-elements-greater-than-or-equal-x/

class Solution {
public:
    int specialArray(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return -1;
        // int left = *min_element(nums.begin(), nums.end());
        int left = 0;
        int right = *max_element(nums.begin(), nums.end());
        
        while (left + 1 < right) {
            int mid = (right - left) / 2 + left;
            int cnt = count(nums, mid); // numbers in nums that are >= mid
            if (cnt == mid) return mid;
            else if (cnt > mid) { // mid should be larger
                left = mid;
            } else {
                right = mid;
            }
        }
        
        if (count(nums, left) == left) return left;
        if (count(nums, right) == right) return right;
        
        return -1;
    }
    
    int count(vector<int>& nums, int num) { // numbers in nums that are >= num
        int cnt = 0;
        for_each(nums.begin(), nums.end(), [&](int x) { if (x >= num) ++cnt; });
        return cnt;
    }
    
};