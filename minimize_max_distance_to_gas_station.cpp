https://leetcode.com/problems/minimize-max-distance-to-gas-station/

class Solution {
public:
    double minmaxGasDist(vector<int>& stations, int k) {
        
        int n = stations.size();
        double left = 0, right = stations[n - 1] - stations[0];
        
        auto isValid = [&](double dis) -> bool {
            int count = 0;
            for (int i = 0; i < n - 1; ++i) {
                count += ceil((stations[i + 1] - stations[i]) / dis) - 1;
            }
            return count <= k;
        };
        
        while (right - left > 1e-6) {
            double mid = left + (right - left) / 2;
            if (isValid(mid)) right = mid;
            else left = mid;
        }
        
        return right;
    }
};