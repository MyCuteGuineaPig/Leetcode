/*

646. Maximum Length of Pair Chain
https://leetcode.com/problems/maximum-length-of-pair-chain/description/

You are given n pairs of numbers. In every pair, the first number is always smaller than the second number.

Now, we define a pair (c, d) can follow another pair (a, b) if and only if b < c. Chain of pairs can be formed in this fashion.

Given a set of pairs, find the length longest chain which can be formed. You needn't use up all the given pairs. 
You can select pairs in any order.

Example 1:
Input: [[1,2], [2,3], [3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4]
Note:
The number of given pairs will be in the range [1, 1000].

*/

class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        if(pairs.size()<=1) return pairs.size();
        sort(pairs.begin(),pairs.end(), [](const vector<int> & a, const vector<int>&b){
            if(a[1]==b[1]) return a[0]<b[0]; else return a[1]<b[1];
        });
        int count = 0, end = INT_MIN;
        for(int i = 0; i<pairs.size();i++){
            if(pairs[i][0]>end){
                count++;
                end = pairs[i][1];
            }
        }
        return count;
    }
};