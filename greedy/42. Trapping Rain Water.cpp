/*
42. Trapping Rain Water

https://leetcode.com/problems/trapping-rain-water/description/
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example, 
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.


*/


class Solution {
public:
    int trap(vector<int>& height) {
        int i = 0, j = height.size()-1, water = 0, leftmax = 0, rightmax = 0;
        while(i<j){
            leftmax = max(leftmax, height[i]);
            rightmax = max(rightmax, height[j]);
            if(leftmax<=rightmax){
                water += leftmax - height[i];
                i++;
            }else{
                water += rightmax - height[j];
                j--;
            }
            
        }
        return water;
    }
};


//Keep track of the maximum height from both forward directions backward directions, call them leftmax and rightmax.

//java 
public int trap(int[] A){
    int a=0;
    int b=A.length-1;
    int max=0;
    int leftmax=0;
    int rightmax=0;
    while(a<=b){
        leftmax=Math.max(leftmax,A[a]);
        rightmax=Math.max(rightmax,A[b]);
        if(leftmax<rightmax){
            max+=(leftmax-A[a]);       // leftmax is smaller than rightmax, so the (leftmax-A[a]) water can be stored
            a++;
        }
        else{
            max+=(rightmax-A[b]);
            b--;
        }
    }
    return max;
}