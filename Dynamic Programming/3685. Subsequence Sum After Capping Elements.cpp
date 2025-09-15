class Solution {
public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n  = nums.size();
        vector<int>sum(k+1); sum[0] = 1;
        vector<bool>res(n);

        for(int i = 0, x = 1; x<=n; ++x){
            while(i < n&& nums[i]<= x){
                //只能从大到小, 如果从小到大，一个num就被用多次
                for(int j = k; j-nums[i] >=0; --j){
                    if(sum[j-nums[i]]) {
                        sum[j] = 1;
                    }
                }
                ++i;
            }
            int max_replace = n - i;
            for(int j = 0; j <= max_replace && x*j <= k; ++j){
                if(sum[k - x*j])
                {
                    res[x-1] = true;
                    break;
                }
            }
        }

        return res;
    }
};


