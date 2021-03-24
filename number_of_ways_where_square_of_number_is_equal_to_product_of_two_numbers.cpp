// https://leetcode.com/problems/number-of-ways-where-square-of-number-is-equal-to-product-of-two-numbers/

class Solution {
public:
    int numTriplets(vector<int>& nums1, vector<int>& nums2) {
        
        auto count = [](vector<int>& nums1, vector<int>& nums2) {
            int n1 = nums1.size(), n2 = nums2.size();
            unordered_map<int, int> m2;
            
            for (int i = 0; i < n2; ++i) ++m2[nums2[i]];
            
            int res = 0;
            for (long x: nums1) {
                for (auto& [y, c]: m2) {
                    long r = x * x / y;
                    if (x * x % y || !m2.count(r)) continue;
                    if (r == y) res += c * (c - 1);
                    else res += c * m2[r];
                }
            }
            return res / 2;
        };
        
        return count(nums1, nums2) + count(nums2, nums1);
        
    }

};