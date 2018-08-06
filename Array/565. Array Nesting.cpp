/*
565. Array Nesting

A zero-indexed array A of length N contains all integers from 0 to N-1. 
Find and return the longest length of set S, where S[i] = {A[i], A[A[i]], A[A[A[i]]], ... } subjected to the rule below.

Suppose the first element in S starts with the selection of element A[i] of index = i, 
the next element in S should be A[A[i]], and then A[A[A[i]]]… By that analogy, 
we stop adding right before a duplicate element occurs in S.

Example 1:
Input: A = [5,4,0,3,1,6,2]
Output: 4
Explanation: 
A[0] = 5, A[1] = 4, A[2] = 0, A[3] = 3, A[4] = 1, A[5] = 6, A[6] = 2.

One of the longest S[K]:
S[0] = {A[0], A[5], A[6], A[2]} = {5, 6, 2, 0}
Note:
N is an integer within the range [1, 20,000].
The elements of A are all distinct.
Each element of A is an integer within the range [0, N-1].


*/


/*

Array Nesting 是能构成最大的循环，比如[5,4,0,3,1,6,2]

S[0] = 5, S[5] = 6, S[6] = 0, S[0] = 2, S[2] = 0;

因为是循环，所以起点无论是哪个点进入都可以得到完整的循环

Therefore the graph should consist of several cycles and the cycles have no "tails". 
That's why we can skip the visited nodes, where to begin in a visited cycle doesn't matter in this circumstance.

*/

class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int res = 0;
        for(int i = 0; i<nums.size(); i++){
            if(nums[i]!=-1){
                int cur = i, count = 0;
                while(nums[cur] != -1){
                    int next = nums[cur];
                    nums[cur] = -1;
                    cur = next;
                    count++;
                }
                res = max(res, count);
            }
        }
        return res;
    }
};


class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        auto result = 0;
        for (const auto& num : nums) {
            if (num != numeric_limits<int>::max()) {
                auto start = num, count = 0;
                while (nums[start] != numeric_limits<int>::max()) {
                    auto temp = start;
                    start = nums[start];
                    nums[temp] = numeric_limits<int>::max();
                    ++count;
                }
                result = max(result, count);
            }
        }
        return result;
    }
};


/*
reference: https://leetcode.com/problems/array-nesting/discuss/102442/Java-O(N)-time-O(1)-space-with-Explanation-and-Proof

与其pollute input array 不如给他们flag

The given condition that the index domain is the same as the value domain is frequently encountered in Leetcode problems. 
When we have this condition, I tend to think of using a technique I call inplace flag. 
Instead of using an extra visited array, we can just mutate the input array to reflect the flag information we want.

The usual inplace flagging techniques include:

- negating: negate to reflect one visit, use abs to get the original value. 
   This only works to detect odd numbers of previous occurrence. 
   It is not appropriate for this problem also because the value can actually be 0 in this problem, 
   so negating 0 does not really flag anything.
-  module (which I used here): add one n to reflect a visit. 把每个数都加n
   Mod n with the entry to get the original value.
-  sorting: put each number into its corresponding index.  通过swap 把每个数放在适当位置
   
This is not recoverable with O(1) space, so not considered here.
Regarding the problem of Input Pollution, it is actually easily fixable when using inplace flagging, 
albeit in a way some may argue imperfect. We can just recover the original input array before returning at the end. 
For negating, just do abs; for module method, just mod n at the end. 
This method fixes the problem in some situation but may still cause problem in a multithreading context.



Just some supplement.

From the statement "The array of size N contains number [0, N-1]", 
we can know that in-degree of all nodes are exactly one (n different edges for n nodes). 
Indegree 是1， 同一个点不会有两个点进入 比如[3,0,2,0] index 1 和 index 0 同时可以进入0

Therefore the graph should consist of several cycles and the cycles have no "tails". 
That's why we can skip the visited nodes, where to begin in a visited cycle doesn't matter in this circumstance.
*/