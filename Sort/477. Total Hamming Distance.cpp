/*
477. Total Hamming Distance

The Hamming distance between two integers is the number of positions at which the corresponding bits are different.

Now your job is to find the total Hamming distance between all pairs of the given numbers.

Example:
Input: 4, 14, 2

Output: 6

Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
showing the four bits relevant in this case). So the answer will be:
HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
Note:
Elements of the given array are in the range of 0 to 10^9
Length of the array will not exceed 10^4.
*/


/*
由第三十二位到第0位，loop每个bit，
数当前bit位为1的个数为bitcount, 结果 res+= bitcount*(size-countsize) 如果全是1，size-countsize = 0; 如果全是0， bitcount = 0

比如
4 is 0100, 14 is 1110, and 2 is 0010
在第四位，有2个0， 1个1，在这位的不同有2，0100 与1110不用; 0010 与 1110不同
*/

class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int res = 0, n = nums.size();
        for(int b = 31; b>=0; b--){
            int bitcount = 0;
            for(auto num: nums){
                bitcount += num >> b & 1; //数在现在这个bit上有几个1
            }
            res += bitcount * (n-bitcount); //现在这个bit上的不同位，0的个数*1的个数
        }
        return res;
    }
};


class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int result = 0;
        for (int i = 0; i < 8 * sizeof(int); ++i) {
            vector<int> counts(2);
            for (const auto& num : nums) {
                ++counts[(num >> i) & 1];
            }
            result += counts[0] * counts[1];
        }
        return result;
    }
};


class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int size = nums.size();
        if(size < 2) return 0;
        int ans = 0;
        int *zeroOne = new int[2];
        while(true)
        {
            int zeroCount = 0;
            zeroOne[0] = 0;
            zeroOne[1] = 0;
            for(int i = 0; i < nums.size(); i++)
            {
                if(nums[i] == 0) zeroCount++;
                zeroOne[nums[i] % 2]++;
                nums[i] = nums[i] >> 1;
            }
            ans += zeroOne[0] * zeroOne[1];
            if(zeroCount == nums.size()) return ans;
        }
    }
};