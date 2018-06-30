/*
523. Continuous Subarray Sum

Given a list of non-negative numbers and a target integer k, 
write a function to check if the array has a continuous subarray of size at least 2 that sums up to the multiple of k, 
that is, sums up to n*k where n is also an integer.

Example 1:
Input: [23, 2, 4, 6, 7],  k=6
Output: True
Explanation: Because [2, 4] is a continuous subarray of size 2 and sums up to 6.
Example 2:
Input: [23, 2, 6, 4, 7],  k=6
Output: True
Explanation: Because [23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.
Note:
The length of the array won't exceed 10,000.
You may assume the sum of all the numbers is in the range of a signed 32-bit integer.

*/


/*
求开始数到所有i的和的余数，如果现在这个的余数之前遇到过，表示，两个数之间有数的和正好整除k

We iterate through the input array exactly once, 
keeping track of the running sum mod k of the elements in the process. 
If we find that a running sum value at index j has been previously seen before in some earlier index i in the array, 
then we know that the sub-array (i,j] contains a desired sum.


(a+(n*x))%x is same as (a%x)
The main idea is that (x + n*k) mod k = x ,which x can be 0,1,...,k-1.

For e.g. in case of the array [23,2,6,4,7] the running sum is [23,25,31,35,42] and the remainders are [5,1,1,5,0].
We got remainder 5 at index 0 and at index 3. 
That means, in between these two indexes we must have added a number which is multiple of the k. 


*/


class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int,int>m = {{0,-1}};
        int sum = 0;
        for(int i = 0; i<nums.size();i++){
            sum += nums[i];
            if(k!=0) sum = sum % k;
            if(m.find(sum)!=m.end()){
                if(i - m[sum] > 1) 
                    return true;
            }
            else m[sum] = i;
        }
        return false;
    }
};

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_set<int>m;
        int sum = 0, pre = 0;
        for(int i = 0; i<nums.size();i++){
            sum += nums[i];
            if(k!=0) sum = sum % k;
            if(m.find(sum)!=m.end()){
                return true;
            }
            m.insert(pre);
            pre = sum;
        }
        return false;
    }
};


class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        // store mod values in unordered map
        // corner case
        if (nums.size() < 2) return false;
        if (k == 0) k = INT_MAX;
        unordered_map<int,int> myHash;
        myHash[0] = -1;
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum = (sum + nums[i]) % k;
            if (myHash.find(sum) == myHash.end()) {
                myHash[sum] = i;
            } else {
                if (i-myHash[sum] > 1)
                    return true;
            }
        }
        return false;
    }
};