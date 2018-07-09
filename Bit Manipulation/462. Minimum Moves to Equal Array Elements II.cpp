/*
462. Minimum Moves to Equal Array Elements II

Given a non-empty integer array, find the minimum number of moves required to make all array elements equal, 
where a move is incrementing a selected element by 1 or decrementing a selected element by 1.

You may assume the array's length is at most 10,000.

Example:

Input:
[1,2,3]

Output:
2

Explanation:
Only two moves are needed (remember each move increments or decrements one element):

[1,2,3]  =>  [2,2,3]  =>  [2,2,2]

*/


/*

Suppose you have two endpoints A and B, when you want to find a point C that has minimum sum of distance between AC and BC, 
the point C will always between A and B. Draw a graph and you will understand it. Lets keep moving forward. 
After we locating the point C between A and B, we can define that

dis(AC) = c - a; dis(CB) = b - c;
sum = dis(AC) + dis(CB) = b - a.
b - a will be a constant value, given specific b and a. Thus there will be no difference between points among A and B.

In this problem, we set two boundaries, saying i and j, and we move the i and j to do the computation.

先sort，然后所有大的减小的和，就是解，因为要抹平大和小的之间的距离，不管最终到达的c点在哪里，大的点到c点 + 小的点到c点的距离一定是大的 - 小的
*/


class Solution {
public:
    int minMoves2(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int i = 0, j = nums.size()-1, res = 0;
        while(j>i){
            res += nums[j--] - nums[i++];
        }
        return res;
    }
};


//Quick Select  O(n) on average
class Solution {
public:
    int minMoves2(vector<int>& nums) {
        if(nums.empty()) return 0;
        nth_element(nums.begin(), nums.begin()+nums.size()/2, nums.end());
        int median = nums[nums.size()/2], res = 0;
        for(int i = 0; i<nums.size(); i++){
            res += max(median - nums[i], nums[i] - median);
        }
        return res;
    }
};


/*
median 好于mean是，中位数不用移动，否则要算上 mean - 中位数的距离
比如 [1,0,0,8,6] 
如果是中位数为最后的点 8-0 + (6-0) = 14
如果是平均数为最后的点 8-0 + (6-0) + （3-1） = 16

Intuitive solution might be making all the numbers the same as average.
However that does not always work 
[1,0,0,8,6]. average is 3, the total cost of making every number 3 is 16
However if we were to make every number 1, cost is 14.

Make every number the medium, instead of average would generate the smallest cost


0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1000000 show median better than mean




I have a simpler proof. The meet point must be somewhere between current min and max. 
No matter which point you pick, the total running length for min and max is the same, 
i.e. abs(min_point-meet_point)+abs(max_point-meet_point) = SOME_CONSTANT.

So, we can effectively reduce the problem size from n to n-2 by discarding min and max points. 
Do you see it? That is the definition of median, isn't it?

Let's have an example. suppose we have an array, [1,2,3,4,5,6,7]. 
The meet point must lie between 1 and 7. For any value in this range, 
the total running length for 1 and 7 is the same. So, array => [2,3,4,5,6]...


完整的数学证明: 
The Median Minimizes the Sum of Absolute Deviations (The L1 Norm)
https://math.stackexchange.com/questions/113270/the-median-minimizes-the-sum-of-absolute-deviations-the-l-1-norm


简单数学证明
https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/discuss/94951/3-line-C++-solution-with-rigorous-math-proof-(same-as-problem-%22Best-Meeting-Point%22)
*/