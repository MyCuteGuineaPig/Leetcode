class Solution {
public:
    int maximumXOR(vector<int>& nums) {
        int ans = 0; 
        for(int i = 27; i>=0; --i){
            for (auto x: nums){
                if((1 << i) & x){
                    ans = (ans | 1<<i);
                }
            }
        }
        return ans;
    }
};



class Solution {
public:
    int maximumXOR(vector<int>& nums) {
        int res = 0;
        for (int a : nums)
            res |= a;
        return res;
    }
};


class Solution {
public:
    int maximumXOR(vector<int>& nums) {
        return reduce(nums.begin(), nums.end(), 0, bit_or());
    }
};

class Solution {
public:
    int maximumXOR(vector<int>& nums) {
        return accumulate(begin(nums), end(nums), 0, bit_or<int>());
    }
};