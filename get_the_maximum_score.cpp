// https://leetcode.com/problems/get-the-maximum-score/

class Solution {
public:
    // two pointers + dp
    // dp[i]: max sum score with nums[i] ended
    // we could only have two choices when we face the same number
    // otherwise we could have to just keep going
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        int modNum = 1e9 + 7;
        int n1 = nums1.size(), n2 = nums2.size();
        
        vector<long> dp1(n1 + 1, 0);
        vector<long> dp2(n2 + 1, 0);
        
        int i = 0, j = 0;
        
        while (i < n1 || j < n2) {
            if (i < n1 && j < n2 && nums1[i] == nums2[j]) {
                long maxI = i > 0 ? dp1[i - 1]: 0;
                long maxJ = j > 0 ? dp2[j - 1]: 0;
                dp1[i] = dp2[j] = max(maxI, maxJ) + nums1[i];
                ++i; 
                ++j;
            } else if (i < n1 && (j == n2 || nums1[i] < nums2[j])) {
                dp1[i] = (i > 0 ? dp1[i - 1]: 0) + nums1[i];
                ++i;
            } else if (j < n2 && (i == n1 || nums2[j] < nums1[i])) {
                dp2[j] = (j > 0 ? dp2[j - 1]: 0) + nums2[j];
                ++j;
            }
        }
        
        return max(dp1[n1 - 1], dp2[n2 - 1]) % modNum;
    }
};