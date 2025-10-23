class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        auto f = [&](this auto && f, int goal){
            int res = 0, l = 0, tot = 0;
            for(int i = 0; i < nums.size(); ++i) {
                tot += nums[i];
                //这是l <= i
                while (l <= i && tot > goal) {
                    tot -= nums[l++];
                }
                res += i - l + 1;
            }  
            return res;
        };
        return f(goal) - f(goal-1);
    }
};


class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        unordered_map<int, int> mp;
        int tot = 0;
        int res = 0;
        mp[0] = 1;
        for(int i = 0; i < nums.size(); ++i){
            tot += nums[i];
            res += mp[tot-goal];
            mp[tot] += 1;
        }
        return res;
    }
};