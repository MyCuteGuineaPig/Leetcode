/*
42. Trapping Rain Water

https://leetcode.com/problems/trapping-rain-water/description/
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example, 
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.


*/

/*
一点一点提高safe level, 因为池子中的水由最矮的一端决定(木桶理论)
比如现在左端最高最矮的小于右端最高的，当前水量等于 左侧最高点leftmost(木桶矮的一段) - heights[i], 然后动左面的寻找下一个高点
用矮的一侧减去 heights[i] 因为怎么也肯定会有高的一侧作为另一边 去盛住水
                           __
比如 现在水是                |  |   
                   __      |  |__       __
             __   |  |__   |  |  |__   |  |
            |  |  |  |  |  |  |  |  |  |  |
    ------------------------------------------------------
          0  1  0  2   1  0  4  2  1  0  2
    index 0  1  2  3   4  5  6  7  8  9 10

          一开始leftmost = 0, rightmost  = 2, 动左侧的 到1, area = leftmost - h[i] = 0 - 0 = 0
          i = 1, j = 10, leftmost = 1, rightmost = 2, h[1] = 1, area = leftmost - h[i] =  1 - 1 = 0
          
          i = 2，j = 10,leftmost = 1, rightmost = 2, h[2] = 1, 因为左侧最矮，右侧怎么也有2作为另一端，所以这个点一定会被填上, area = area + 1 - 0 = 0 + 1 = 1
          i = 3， j = 10, leftmost = 2, rightmost = 2, h[3] = 2, area 不发生变化
          i = 4, j = 10, leftmost = 2, rightmost = 2, h[4] = 1, 因为左侧最矮，area = area + 1 - 0 = 1 + 1 = 2
          i = 5, j = 10, leftmost = 2, rightmost = 2, h[5] = 0, 因为左侧最矮，area = area + 2 - 0 = 2 + 2 = 4
          i = 6, j = 10, leftmost = 4, rightmost = 2, h[10] = 2, area 不发生变化
          i = 6, j = 9, leftmost = 4, rightmost = 2, h[9] = 0, 因为右侧矮, area = area + 2-0 = 4 + 2 = 6
          i = 6, j = 8, leftmost = 4, rightmost = 2, h[8] = 1, 因为右侧矮, area = area + 2-1 = 6 + 1 = 7
          i = 6, j = 8, leftmost = 4, rightmost = 2, h[8] = 2, area 不发生变化 
          area = 7

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

class Solution {
public:
    int trap(vector<int>& height) {
        int l = 0, r = height.size()-1, level = 0, water = 0;
        while (l < r) {
            int lower = height[height[l] < height[r] ? l++ : r--];
            level = max(level, lower); //当前最低的水
            water += level - lower;
        }
        return water;
    }
};

class Solution {
public:
    int trap(vector<int>& height) {
        if ( height.size() <= 2 ) { return 0; }
        
        int i = 0, j = height.size()-1, area = 0;
        int leftmost = 0, rightmost = 0;
        
        while ( i < j ) {
            if ( height[i] < height[j] ) {
                leftmost = max(leftmost, height[i]);
                area += leftmost-height[i++];
            } else {
                rightmost = max(rightmost, height[j]);
                area += rightmost-height[j--];
            } 
        }
        return area;
    }
};





//DP 记录左右两边最高的高度
class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0;
        if(height.size()<2)
            return 0;
        vector<int> dp1(height.size(), 0);
        vector<int> dp2(height.size(), 0);
        int mx = 0;
        for(int i = 1; i < height.size(); i++){
            mx = max(mx, height[i-1]);
            dp1[i] = mx;
        }
        mx = 0;
        for(int i = height.size()-2; i>=0; i--){
            mx = max(mx, height[i+1]);
            dp2[i] = mx;
        }
        for(int i = 1; i <= height.size()-2; i++){
            res += max( min(dp1[i],dp2[i])-height[i], 0); //max(val, 0) 可能这个height[i]是新的最大高度,大于左右两侧的高度
        }
        return res;
    }
};


class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size(), l = 0, r = n - 1, water = 0, minHeight = 0;
        while (l < r) {
            while (l < r && height[l] <= minHeight) //逐步提高水的safe level，当小于等于当前level的递增或者递减
                water += minHeight - height[l++];
            while (r > l && height[r] <= minHeight) 
                water += minHeight - height[r--];
            minHeight = min(height[l], height[r]);
        }
        return water;
    }
};


class Solution {
public:
    int trap(vector<int>& height) {
        int sz=height.size(), highest=0, water=0;
        //from left to right, only consider the trap's left elevation
        for(int i=0; i<sz; i++){
            if(height[i]<highest) water+=highest-height[i];
            highest=max(highest, height[i]);
        }
        
        int prehighest=highest;
        highest=0;
        //from right to left, only consider the trap's right elevation, subtract the surplus water
        for(int i=sz-1; i>=0; i--){
            highest=max(height[i], highest);
            if(highest<prehighest) water-=prehighest-highest; //减去多算的水的高度
        }
        return water;
    }
};

/*
Descending Stack的解：

stack放的index, stack中index 表示的高度是梯度下降的，当出现新的高度大于stack的高度，先pop stack作为bar(长方形的底),
因为stack top的高度是现在stack中最低的高度， ( min(l, r) - bar )*(i - stk.top - 1) = 高*长
             
不能一次pop 很多，否则不好计算当中点起伏的高度

比如 现在水是
             __             __
            |  |           |  |
            |  |           |  |   
            |  |__    __   |  |
            |  |  |__|  |__|  | 
            |  |  |  |  |  |  |  
    ------------------------------------------------------
             5  2  1   2  1  5
    index    0  1  2   3  4  5

        
        当 i = 3是， h = 2, 大于stack.top中高度, stack [2,1,0] 代表高度是 [1,2,5]
                pop后, bar = 2, height[bar] = 1,  area = (2-1)*(3-1-1) = 1*1 = 1
    
        当 i = 5时， h = 5, 大于stack top高度, stack = [4,3,1,0] 代表高度是[1,2,2,5]
                先pop， bar 的高度是1, 
                area += (2-1)* (5-2-1) += 1; area = 2

                再pop 2, bar 高度是2, stack top高度还是2，高度不会有变化,

                再pop 2, bar 高度是2，stack top 高度是 5，
                area += (5-2) * (5-0-1) = 3 * 4 = 12; area = 14
        
        假如当 i = 5, 直接pop 到 stack.top() = 5(index = 0), 但是发现bar 高度是1 时，实际上有 还有高度为2 (index = 1, 3)的点，没有从高度重剔除，
                就算刨除所有大于1的点，但是发现 i = 2的点没有刨除，因为 i = 2 时，高度为1， 这个为1高度的水（左右两边高度为2）已经计算过了，应该也从结果中剔除

*/
class Solution {
public:
    int trap(vector<int>& height) {
        int water = 0, i = 0, bar = 0;  //descending stack 
        stack<int>stk; //放的是index
        while(i < height.size()){
            //cout<<"i "<<i<<endl;
            if(stk.empty() || height[i] <= height[stk.top()])
                stk.push(i++);
            else{
                //一次只pop 一个，一个块一个块的来，不能一次pop 很多个，否则不知道起伏的高度之前有没有算进高度
                bar = stk.top(); stk.pop(); //表示上一个处理的对象的高度，就是其次的高度
                int curwater = stk.empty() ? 0 : (min(height[i], height[stk.top()]) - height[bar])*(i-stk.top()-1); //empty 表示没有左侧的边界
                water += curwater;
            }
        }
        return water;
    }
};