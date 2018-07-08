/*
645. Set Mismatch

The set S originally contains numbers from 1 to n. 
But unfortunately, due to the data error, one of the numbers in the set got duplicated to another number in the set, 
which results in repetition of one number and loss of another number.

Given an array nums representing the data status of this set after the error. 
Your task is to firstly find the number occurs twice and then find the number that is missing. Return them in the form of an array.

Example 1:
Input: nums = [1,2,2,4]
Output: [2,3]
Note:
The given array size will in the range [2, 10000].
The given array's numbers won't have any order.



*/
/*
Xor先找出unique的digit，然后

*/

class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int unique = 0;
        for(int i = 0; i<nums.size();i++){
            unique = unique ^ i+1 ^ nums[i];
        }
        unique &= -unique;
        vector<int>res(2);
        for(int i = 0; i<nums.size();i++){
            if(i+1 & unique) res[0] ^= i+1;
            else res[1] ^= i+1;

            if(nums[i] & unique) res[0] ^= nums[i];
            else res[1] ^= nums[i];
        }
        for(auto i: nums)
            if(res[1] == i){
                swap(res[0],res[1]); 
                break;
            }
        return res;
    }
};



class Solution {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        int x_xor_y = 0;
        for (int i = 0; i < nums.size(); ++i) {
            x_xor_y ^= nums[i] ^ (i + 1);
        }
        int bit = x_xor_y & ~(x_xor_y - 1);
        vector<int> result(2);
        for (int i = 0; i < nums.size(); ++i) {
            result[static_cast<bool>(nums[i] & bit)] ^= nums[i];
            result[static_cast<bool>((i + 1) & bit)] ^= i + 1;
        }
        if (find(nums.begin(), nums.end(), result[0]) == nums.end()) {
            swap(result[0], result[1]);
        }
        return result;
    }
};


// Time:  O(n)
// Space: O(1)
class Solution2 {
public:
    vector<int> findErrorNums(vector<int>& nums) {
        vector<int> result(2);
        for (const auto& i : nums) {
            if (nums[abs(i) - 1] < 0) {  // twice
                result[0] = abs(i);
            } else {
                nums[abs(i) - 1] *= -1;
            }
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > 0) {  // missing
                result[1] = i + 1;
            } else {
                nums[i] *= -1;
            }
        }
        return result;
    }
};