class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        unordered_map<int, int> cnt;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int l = 0, r = 0; 
        int res = 0;
        //first check the count for nums[i] -k ... nums[i].... nums[i] + k
        for(auto cur: nums) {
            while (r< n && nums[r] <= cur + k )
            {
                ++cnt[nums[r]];
                ++r;
            }
            while (l < n && nums[l] < cur - k)
                ++l;
            res = max(res, min(r-l, cnt[cur] + numOperations));
        }


        //second check the interval,  nums[r] - nums[l] < 2*k
        for(int l = 0, r = 0; r < n; ++l) {

            while(r < n && nums[r] - nums[l] <= 2*k)
                ++r;
            res = max(res, min(r - l , numOperations));
        }
        return res;
    }
};