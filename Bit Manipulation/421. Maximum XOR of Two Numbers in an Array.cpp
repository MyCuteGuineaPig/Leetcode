/*
421. Maximum XOR of Two Numbers in an Array

Given a non-empty array of numbers, a0, a1, a2, … , an-1, where 0 ≤ ai < 231.

Find the maximum result of ai XOR aj, where 0 ≤ i, j < n.

Could you do this in O(n) runtime?

Example:

Input: [3, 10, 5, 25, 2, 8]

Output: 28

Explanation: The maximum result is 5 ^ 25 = 28.

*/


/*
This algorithm's idea is:
to iteratively determine what would be each bit of the final result from left to right. 
And it narrows down the candidate group iteration by iteration. 
e.g. assume input are a,b,c,d,...z, 26 integers in total. 
In first iteration, if you found that a, d, e, h, u differs on the MSB(most significant bit), 
so you are sure your final result's MSB is set. 
Now in second iteration, you try to see if among a, d, e, h, u there are at least two numbers make the 2nd MSB differs, 
if yes, then definitely, the 2nd MSB will be set in the final result. 
And maybe at this point the candidate group shinks from a,d,e,h,u to a, e, h. 
Implicitly, every iteration, you are narrowing down the candidate group, 
but you don't need to track how the group is shrinking, you only cares about the final result.


example: Given [14, 11, 7, 2], which in binary are [1110, 1011, 0111, 0010].
Since the MSB is 3, I'll start from i = 3 to make it simplify.

i = 3, set = {1000, 0000}, max = 1000
i = 2, set = {1100, 1000, 0100, 0000}, max = 1100
i = 1, set = {1110, 1010, 0110, 0010}, max = 1100
i = 0, set = {1110, 1011, 0111, 0010}, max = 1100


set.contains(tmp ^ prefix)
//This is the most tricky part, coming from a fact that if a ^ b = c, then a ^ c = b;
// now we have the 'c', which is greedyTry, and we have the 'a', which is leftPartOfNum
// If we hope the formula a ^ b = c to be valid, then we need the b, 
// and to get b, we need a ^ c, if a ^ c exisited in our set, then we're good to go

从第32位开始到第0位逐渐缩小范围, 利用性质 a ^ b = c,  a ^ c = b, c是我们需要找的数，
每到一位就试下这位可不可以是1, temp = maxnum  | (1<<i)，如果可以是1，  a^c 也在set里面, 就update max number  maxnum = temp = maxnum | 1


*/

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int maxnum = 0, mask = 0;
        for(int i = 31; i>=0; i--){
            mask = mask | (1<<i);
            unordered_set<int>prefix;
            for(auto n: nums)
                prefix.insert(n & mask);
            if(prefix.size() == 1) continue;
            int temp = maxnum | (1<<i);
            
            for(auto n: prefix){
                if(prefix.find(n ^ temp) != prefix.end()){
                    maxnum = temp;
                    break;
                }
            }
        }
        return maxnum;
    }
};