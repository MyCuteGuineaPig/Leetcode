/*

First you may have feeling of using sliding window.
Then this idea get stuck in the middle.

This problem will be a very typical sliding window,
if it asks the number of subarrays with at most K distinct elements.

Just need one more step to reach the folloing equation:
exactly(K) = atMost(K) - atMost(K-1)


 */

class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        auto f = [&](this auto && f, int kk){
            unordered_map<int, int>mp;
            int l = 0, res = 0, cnt = 0;
            for(int i = 0; i < nums.size(); ++i) {
                if(mp[nums[i]]++ == 0) {
                    ++cnt;
                }
                while (cnt > kk) {
                    if (--mp[nums[l++]] == 0) --cnt;
                }
                res += i - l + 1;
            }
            return res;
        };
        return f(k) - f(k-1);
    }
};