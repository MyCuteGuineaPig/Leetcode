/*
594. Longest Harmonious Subsequence

We define a harmonious array is an array where the difference between its maximum value and its minimum value is exactly 1.

Now, given an integer array, you need to find the length of its longest harmonious subsequence among all its possible subsequences.

Example 1:
Input: [1,3,2,2,5,2,3,7]
Output: 5
Explanation: The longest harmonious subsequence is [3,2,2,2,3].
Note: The length of the input array will not exceed 20,000.

*/


//One pass
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int,int>m;
        int res = 0;
        for(auto i: nums){
            m[i]++;
            if(m.count(i+1))
                res = max(res, m[i] + m[i+1]);
            if(m.count(i-1))
                res = max(res, m[i] + m[i-1]);
        }
        return res;        
    }
};

//two pass
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int,int>m;
        for(auto i: nums) m[i]++;
        int res = 0;
        for(auto it: m)
            if(m.count(it.first+1))
                res = max(res, it.second + m[it.first+1]);
        return res;        
    }
};