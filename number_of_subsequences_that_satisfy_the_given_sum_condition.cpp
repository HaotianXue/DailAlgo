// https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/

class Solution {
public:
    // Since order of the elements in the subsequence doesn’t matter, we can sort the input array.
    // Very similar to two sum, we use two pointers (i, j) to maintain a window, s.t. nums[i] +nums[j] <= target.
    // Then fix nums[i], any subset of (nums[i+1~j]) gives us a valid subsequence, 
    // thus we have 2^(j-(i+1)+1) = 2^(j-i) valid subsequence for window (i, j).
    int numSubseq(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 0) return 0;
        
        int modNum = 1e9 + 7;      
        vector<int> p(n + 1, 1);
        // pre-compute 2^0 - 2^n
        for (int i = 1; i <= n; ++i) {
            p[i] = (p[i - 1] << 1) % modNum; 
        }       
        sort(nums.begin(), nums.end());
        int res = 0;
        for (int i = 0, j = n - 1; i <= j; ++i) {
            while (i <= j && nums[i] + nums[j] > target) --j;
            if (i > j) continue;
            // In subarray nums[i~j]:
            // min = nums[i], max = nums[j]
            // nums[i] + nums[j] <= target
            // {nums[i], (j - i - 1 + 1 values)}
            // Any subset of the right part gives a valid subsequence 
            // in the original array. And There are 2^(j - i) ones.
            res = (res + p[j - i]) % modNum;
        }
        return res;
    }
};