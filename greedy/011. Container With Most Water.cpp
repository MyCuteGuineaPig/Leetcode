/*

11. Container With Most Water
https://leetcode.com/problems/container-with-most-water/description/

Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai).
 n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). 
 Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.

*/

/*
解法：移到下一个高度，不能height[i+1] >= height[i] i就++ 或者height[j-1] >= height[j] j就--
这样可能错过最佳高度


比如 [1,2,4,3]
    i = 0, j = 3, h = min(1,3) = 1, water = (3-0)*1 = 1
    之后移动到下一个高度, i=1, j = 3, h = min(2,3) = 2, water = (3-1)*2 = 2,
    如果只看 height[i+1] >= height[i] i会直接到4，错过了最佳高度2

一定移动是移动小的值， why? 
比如有点 [a1,a2,...,a30], 已经知道a10 和 a20 是最大值，现在在a10, a21, 
a10 > a21, 下一步一定是移动 a21 -> a20, 
why a10 > a21 ? 如果 a21 > a10, 则area between (a10, a21) 大于 (a10, a20) (bc （21-10)*a10 > at most (20-10)*a10)


对于 （1，6）的情况，如果位置1的长度小于位置6的长度，那么对于位置1而言，它的最大面积已经求出来了，
因此右边的线如何移动是无所谓的。
也就是说（1，2）（1，3）（1，4）（1，5）的情况都可以不用考虑。
下一步就移动左边的线到位置2。如果位置2的长度大于位置6，那么位置6的最大面积已经求出来了。
同理左边的线再怎么移动都无所谓。于是再下一步就移动右边的线到位置5。以此类推。

*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        if(height.empty()) return 0;
        int i = 0, j = height.size()-1, h = 0, water = 0;
        while(i<j){
            h = min(height[i], height[j]);
            water = max(water, (j-i)*h);
            while( i<j && height[i] <= h) i++;
            while(i<j && height[j] <= h) j--;
        }
        return water;
    }
};


class Solution {
public:
    int maxArea(vector<int>& height) {
        int i = 0, j = height.size() - 1,  ans = -1, cur;
        while(i < j)
        {
            if(height[i] < height[j]) {
                cur = height[i] * (j - i);
                i ++;
            }
            else{
                cur = height[j] * (j - i);
                j --;
            }
            if(ans < cur) ans = cur;
        }
        return ans;
    }
};


class Solution {
public:
    int maxArea(vector<int> &height) {
        int l(0), r=height.size()-1, result(0);
        while(l < r){
            if(height[l] < height[r]){
                 result =  max(result, height[l] * (r - l));
                 int pivot = height[l++];
                 while(l < r && height[l] <= pivot) ++l;
            }else{
                 result = max(result, height[r] * (r - l));
                 int pivot = height[r--];
                 while(l < r && height[r] <= pivot) --r;
            }
        }
        return result;
    }
};



class Solution {
public:
    int maxArea(vector<int>& height) {
        int i = 0;
        int j = height.size()-1;
        int M = 0;
        while(i < j){
            if (height[i] < height[j]){
                M = max(M,height[i]*(j-i));
                i++;
            } else {
                M = max(M,height[j]*(j-i));
                j--;
            }
        }
        return M;
    }
};