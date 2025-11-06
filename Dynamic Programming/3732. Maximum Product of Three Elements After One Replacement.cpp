class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        vector<long long> dpmax = {max(nums[0], nums[1]), nums[0] * 1LL * nums[1]},
        dpmin = {min(nums[0], nums[1]), nums[0] * 1LL * nums[1]};
        for (int i = 2; i < nums.size(); ++i) {
            const long long x = nums[i];
            dpmax[1] = max(dpmax[1], max(dpmax[0] * x, dpmin[0] * x));
            dpmin[1] = min(dpmin[1], min(dpmax[0] * x, dpmin[0] * x));
            dpmax[0] = max(dpmax[0], x);
            dpmin[0] = min(dpmin[0], x);
        }
        return max(max(dpmax[1] * 100000, dpmin[1] * 100000), max(dpmax[1] * -100000, dpmin[1] * -100000));
    }
};