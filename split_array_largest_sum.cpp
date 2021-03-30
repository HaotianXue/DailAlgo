// https://leetcode.com/problems/split-array-largest-sum/

class Solution {
public:
    
    long long accu_sum(vector<int> &nums, int start, int end) {
        long long sum = 0;
        for (int i = start; i <= end; ++i) {
            sum += nums[i];
        }
        return sum;
    }

    long long get_max(vector<int> &nums) {
        long long max = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            if (max < nums[i]) max = nums[i];
        }
        return max;
    }

    int num_groups(vector<int> &nums, long long upper) {
        long long sum = 0;
        int num = 1;
        for (const int &n: nums) {
            if (sum + n > upper) {
                sum = n;
                ++num;
            } else {
                sum += n;
            }
        }
        return num;
    }
    
    int splitArray(vector<int>& nums, int m) {
        long long l = get_max(nums);
        long long r = accu_sum(nums, 0, nums.size() - 1);
        while (l + 1 < r) {
            long long upper = l + (r - l) / 2;
            if (num_groups(nums, upper) > m) {
                l = upper + 1;
            } else {
                r = upper;
            }
        }
        if (num_groups(nums, l) <= m) {
            return l;
        }
        if (num_groups(nums, r) <= m) {
            return r;
        }
        return -1;
    }
};