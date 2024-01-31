/*
So apply operation as many as possible,
it will sort the array on each bit,
from random array [1,0,1,0,1,0,0],
to a sorted array [0,0,0,0,1,1,1].
*/

class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        vector<int>cnt(30);
        const long mod = 1e9 + 7;
        for(int i = 0; i<30; ++i){
            for(auto x: nums){
                if((1 << i) & x){
                    ++cnt[i];
                }
            }
        }
        long ans = 0;
        for(int i = 0; i<k; ++i){
            long cur = 0;
            for(int j = 0; j<30; ++j){
                if(cnt[j]-->0){
                    cur = cur | 1<<j;
                }
            }
            ans = (ans + cur * cur % mod) % mod;
        }
        return ans;        
    }
};


class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> cnt(31, 0);
        
        for (int bit = 0; bit < 31; bit ++) {
            for (int j = 0; j < n; j ++) 
                if (nums[j] & (1 << bit)) cnt[bit] ++;
        }
        
        ll result = 0;
        
        for (int i = 0; i < k; i ++) {
            ll val = 0;
            
            for (int bit = 0; bit < 31; bit ++) {
                if (cnt[bit] < (i+1)) continue;
                val |= (1 << bit);
            }
            result = (result + val*val) % MOD;
        }
        return result;
    }
};