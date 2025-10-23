class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int res = 0, l = 0, zero_count = 0;
        for(int i = 0; i < nums.size(); ++i){
            zero_count += nums[i] == 0;
            while (zero_count > k) {
                zero_count -= nums[l++] == 0;
            }
            res = max(res, i - l + 1);
        }
        return res;
    }
};

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int res = 0, l = 0, zero_count = 0;
        for(int i = 0; i < nums.size(); ++i){
            zero_count += nums[i] == 0;
            if (zero_count > k)
                zero_count -= nums[l++] == 0;
        }
        return nums.size() - l;
    }
};