// https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted
class Solution {
public:
    
    // two pointers
    // Find the right most j such that arr[j – 1] > arr[j], if not found which means the entire array is sorted return 0. 
    // Then we have a non-descending subarray arr[j ~ n-1].
    // We maintain two pointers i, j, such that arr[0 ~ i] is non-descending and arr[i] <= arr[j] 
    // which means we can remove arr[i+1 ~ j-1] to get a non-descending array. 
    // Number of elements to remove is j – i – 1 .
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size();
        int j = n - 1;
        while (j > 0 && arr[j - 1] <= arr[j]) --j;
        if (j == 0) return 0;
        int ans = j; // remove arr[0 ~ j-1]
        for (int i = 0; i < n; ++i) {
          if (i > 0 && arr[i - 1] > arr[i]) break;
          while (j < n && arr[i] > arr[j]) ++j;      
          // arr[i] <= arr[j], remove arr[i + 1 ~ j - 1]
          ans = min(ans, j - i - 1);
        }
        return ans;    
    }
};