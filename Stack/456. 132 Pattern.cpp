/*
456. 132 Pattern


Given a sequence of n integers a1, a2, ..., an, a 132 pattern is a subsequence ai, aj, 
ak such that i < j < k and ai < ak < aj. Design an algorithm that takes a list of n numbers as input and checks whether there is a 132 pattern in the list.

Note: n will be less than 15,000.

Example 1:
Input: [1, 2, 3, 4]

Output: False

Explanation: There is no 132 pattern in the sequence.
Example 2:
Input: [3, 1, 4, 2]

Output: True

Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
Example 3:
Input: [-1, 3, 2, 0]

Output: True

Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].


*/


/*
QUESTION: To search for a subsequence (s1,s2,s3) such that s1 < s3 < s2.

INTUITION: Suppose we want to find a 123 sequence with s1 < s2 < s3, we just need to find s3, 
followed by s2 and s1. Now if we want to find a 132 sequence with s1 < s3 < s2, we need to switch up the order of searching. 
we want to first find s2, followed by s3, then s1.

DETECTION: More precisely, we keep track of highest value of s3 for each valid (s2 > s3) pair
 while searching for a valid s1 candidate to the left. 
 Once we encounter any number on the left that is smaller than the largest s3 we have seen so far, 
 we know we found a valid sequence, since s1 < s3 implies s1 < s2.

ALGORITHM: We can start from either side but I think starting from the right allow us to finish in a single pass. 
The idea is to start from end and search for valid (s2,s3) pairs, 
we just need to remember the largest valid s3 value, using a stack will be effective for this purpose. 
A number becomes a candidate for s3 if there is any number on the left bigger than it.

CORRECTNESS: As we scan from right to left, we can easily keep track of the largest s3 value of all (s2,s3) candidates encountered so far.
 Hence, each time we compare nums[i] with the largest candidate for s3 within the interval nums[i+1]...nums[n-1] we are effectively asking the question: 
 Is there any 132 sequence with s1 = nums[i]? Therefore, if the function returns false, there must be no 132 sequence.

IMPLEMENTATION:

Have a stack, each time we store a new number, we first pop out all numbers that are smaller than that number. 
The numbers that are popped out becomes candidate for s3.
We keep track of the maximum of such s3 (which is always the most recently popped number from the stack).
Once we encounter any number smaller than s3, we know we found a valid sequence since s1 < s3 implies s1 < s2.
RUNTIME: Each item is pushed and popped once at most, the time complexity is therefore O(n).

EXAMPLE:
i = 6, nums = [ 9, 11, 8, 9, 10, 7, 9 ], S1 candidate = 9, S3 candidate = None, Stack = Empty
i = 5, nums = [ 9, 11, 8, 9, 10, 7, 9 ], S1 candidate = 7, S3 candidate = None, Stack = [9]
i = 4, nums = [ 9, 11, 8, 9, 10, 7, 9 ], S1 candidate = 10, S3 candidate = None, Stack = [9,7]
i = 3, nums = [ 9, 11, 8, 9, 10, 7, 9 ], S1 candidate = 9, S3 candidate = 9, Stack = [10]
i = 2, nums = [ 9, 11, 8, 9, 10, 7, 9 ], S1 candidate = 8, S3 candidate = 9, Stack = [10,9] We have 8<9, sequence (8,10,9) found!

*/


/*
寻找 s1 < s3 < s2: 从后往前寻找最大的s3, stack是ascending stack,里面的数都是由小变大的，
s2是比s3小一点点的数,且要保证s2是s3后最大的s2, 这样可以给s1 空间，只要s1 比s2小，就可以返回true了

当看到nums[i] > stack.top() 时，pop stack,直到stack top比nums[i] 大
(最后一个pop的数为s2,因为s2是比s3小一点的数)，再push nums[i] 

****  一直都死需要最大的s2点，****
比如 10, 8, 12, 0,4  
在12位置，12, s2 = 4, 
在10的位置,  s2 = 8

不会出现s2 下降的情况
比如 10, 1, 12, 0,4  
在1的位置，就return了，不会push 1 进ascending stack,

*/



class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int s2 = numeric_limits<int>::min();
        stack<int>ascendingstack;
        for(int i = nums.size()-1; i>=0; i--){
            if(nums[i] < s2) return true;
            while(!ascendingstack.empty() && nums[i] > ascendingstack.top() ){
                s2 = ascendingstack.top(); ascendingstack.pop();
            }
            ascendingstack.push(nums[i]);
        }
        return false;
    }
};


//use vector itself as stack
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        int s2 = numeric_limits<int>::min();
        int index = nums.size();
        for(int i = nums.size()-1; i>=0; i--){
            if(nums[i] < s2) return true;
            while(index < nums.size() && nums[i] > nums[index]){
                s2 = nums[index++];
            }
            nums[--index] = nums[i];
        }
        return false;
    }
};



/*

也是descending stack, 因为minv 逐渐缩小过程

从左向右loop的，寻找当前nums[i],最大的window(最大值和最小值)
stk pair first存当前最小值，second存的在当前最小的minimum s1时的s3的最大值

stk是按照first顺序从小变大的,top的是first最小的，最底下是first最大的,越晚push的first越小

pop时候如果 first < nums[i] < second, return true
如果 first < second < nums[i], 表示当前second过小


不可以删除stack中 nums[i] <= first < second, 可能当前nums[i]过小，stack是按照first排序的，并不是按照second排序的
且有可能这个second是array最大的second，之后的有个数 nums[j] 可能大于 nums[i], first < nums[j] < second
比如[1,3,-1,8,-7,-3,6]

*/
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        if(nums.size()<3) return false;
        stack<pair<int,int>>stk; //fist the minimum value
        //stack是first (mininum ascending stack)
        int minv = nums[0];
        stk.push({nums[0],nums[0]});
        for(int i = 1; i<nums.size(); i++){
            if(nums[i] <= minv) minv = nums[i];
            else{
                while(!stk.empty() && nums[i] > stk.top().first){ //如果 nums[i] < stk.top().first, stk 前面也是nums[i], 因为stk.top().first 逐渐变小 
                    if(nums[i] < stk.top().second) return true;
                    else stk.pop();
                }
                /*
                
                不可以加 if(!stk.empty() && nums[i] <= stk.top().first) stk.pop(); 比如[3,5,0,3,4]， 或者[1,3,-1,8,-7,-3,6]
                */
                stk.push({minv,nums[i]});//push进当前的窗口
            }
        }
        return false;
    }
};
