class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int res = 1;
        int l = 0; 
        int bit = 0; 
        for(int i = 0; i < nums.size(); ++i){
            while (bit & nums[i]) {
                bit = bit & (~nums[l++]); //negate every digits for nums[l]
            }
            bit |= nums[i];
            res = max(res, i - l + 1);
        }
        return res;
    }
};


class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int res = 1;
        int l = 0; 
        int bit = 0; 
        for(int i = 0; i < nums.size(); ++i){
            while (bit & nums[i]) {
                bit = bit ^ nums[l++]; //negate every digits for nums[l]
            }
            bit |= nums[i];
            res = max(res, i - l + 1);
        }
        return res;
    }
};



class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int l = 0; 
        int bit = 0; 
        int n = nums.size();
        for(int i = 0; i < n; ++i){
            if (bit & nums[i]) {
                bit = bit & (~nums[l++]); //negate every digits for nums[l]
            }
            bit |= nums[i];
        }
        return n - l;
    }
};