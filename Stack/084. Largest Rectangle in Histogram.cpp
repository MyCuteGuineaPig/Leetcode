/*
84. Largest Rectangle in Histogram

Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, 
find the area of largest rectangle in the histogram.


Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].


The largest rectangle is shown in the shaded area, which has area = 10 unit.

Example:

Input: [2,1,5,6,2,3]
Output: 10

*/


/*

We traverse all bars from left to right, 
maintain a stack of bars. Every bar is pushed to stack once. 
A bar is popped from stack when a bar of smaller height is seen. 
When a bar is popped, we calculate the area with the popped bar as smallest bar. 
How do we get left and right indexes of the popped bar – the current index tells us the ‘right index’ and index of previous item in stack is the ‘left index’.


stk push的index
stk 是height ascending stack, 数是从小往大的，top的数是最大的数
遇见h[i] 比stk的top小的， 长方形的高是h[stk.top()], 长方形的长是从在这点之前一点, 到上一个比h[stk.top()]小的width
    - 高就是h = h[stk.top()]
    - 然后pop stack，width = i-stk.top - 1,(因为不算i这个点，也不算pop后的top点，因为这个点比h矮)


    [2,1,2,5,4,6]           6
                   5     | - |
                 | - | 4 |   |
                 |   | - |   |
        2      2 |   |   |   |
       |— | 1 | -|   |   |   |
       |  | - |  |   |   |   |
        0   1   2   3   4  5

这里方便表示stack是ascending height, 用了height itself，实际上应该用height指的index
2. stack: 2
1. 遇到小的pop 2, l = 1-（-1)-1 = 1, h = 2, araa = 2. stack: 1 
2. stack:  1, 2
5, stack:  1, 2, 5
4, 遇到小的pop.top(5没了), l = 4-2-1 = 1, h = 5, area = 5, stack: 1, 2 ,4 
5. stack:  1, 2, 4, 6
6. 0:  a. pop 6,  l = 6 - 4 -1 = 1, h = 6,  area = 6, stack: 1, 2 ,4
       b. pop 4:  l = 6 - 2 - 1 = 3, h = 4, area = 12, stack: 1, 2
       c. pop 2:  l = 6 - 1 -1 = 4, h = 2, area = 8, stack: 1
       d. pop 3:  l = 6 -(-1)-1 = 6, h = 1, area = 6, stack: empty


*/

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int res = 0;
        heights.push_back(0);
        stack<int>stk;
        for(int i = 0; i<heights.size();i++){
            while(!stk.empty() && heights[stk.top()]>heights[i]){
                int h = heights[stk.top()]; stk.pop();
                int l = stk.empty() ? i:  i-stk.top()-1;  //i从头开始，不算这个点
                res = max(res, l*h);
            }
            stk.push(i);
        }
        return res;
    }
};


//不改变height
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int res = 0;
        stack<int>stk;
        for(int i = 0; i<=heights.size();i++){
            while(!stk.empty() && (i ==heights.size() || heights[stk.top()]>heights[i])){ //当i== height.size(), heights[i]报error, 所以加上条件i == heights.size()
                int h = heights[stk.top()]; stk.pop();
                int l = stk.empty() ? i:  i-stk.top()-1;
                res = max(res, l*h);
            }
            stk.push(i);
        }
        return res;
    }
};



/*
Divide Conquer: 
The idea is simple: for a given range of bars, 
the maximum area can either from left or right half of the bars, or from the area containing the middle two bars. 

*/
class Solution {
    int maxCombineArea(const vector<int> &height, int s, int m, int e) {
        // Expand from the middle to find the max area containing height[m] and height[m+1]
        int i = m, j = m+1;
        int area = 0, h = min(height[i], height[j]);
        cout<<" start "<<s<<" end "<<e<<" h "<<h<<endl;
        while(i >= s && j <= e) {
            h = min(h, min(height[i], height[j]));
            area = max(area, (j-i+1) * h);
            cout<<" while start "<<i<<" j "<<j<<" h "<<h<<" "<<"  (j-i+1) * h "<< (j-i+1) * h<<" area "<<area<<endl;
            if (i == s) {
                ++j;
            }
            else if (j == e) {
                --i;
            }
            else {
                // if both sides have not reached the boundary,
                // compare the outer bars and expand towards the bigger side
                if (height[i-1] > height[j+1]) {
                    --i;  //先弄大的，否则可能小的已经比h小了
                }
                else {
                    ++j;
                }
            }
        }
        return area;
    }
    int maxArea(const vector<int> &height, int s, int e) {
        // if the range only contains one bar, return its height as area
        if (s == e) {
            return height[s];
        }
        // otherwise, divide & conquer, the max area must be among the following 3 values
        int m = s + (e-s)/2;
        // 1 - max area from left half
        int area = maxArea(height, s, m);
        // 2 - max area from right half
        area = max(area, maxArea(height, m+1, e));
        // 3 - max area across the middle
        area = max(area, maxCombineArea(height, s, m, e));
        return area;
    }
public:
    int largestRectangleArea(vector<int> &height) {
        if (height.empty()) {
            return 0;
        }
        return maxArea(height, 0, height.size()-1);
    }
};