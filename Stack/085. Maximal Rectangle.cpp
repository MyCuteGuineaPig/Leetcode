"""
85. Maximal Rectangle

"""

/*
Ascending stack 的解
与 084. Largest Rectangle in Histogram 解相似

比如这个matrix有n行，就把这个问题转换成n个Histogram的问题。
每个问题就是一个以这一行为底的Histogram问题，上面连续的1的个数就是Height。
*/
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int n = matrix.size(), m = matrix[0].size();
        int h = 0, l = 0, maxarea = 0;
        vector<int>height(m);
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m; j++){
                height[j] = matrix[i][j] == '1' ? height[j]+1 : 0;
            }

            stack<int>stk;
            for(int j = 0; j<=m; j++){
                while(!stk.empty() && (j==m || height[stk.top()]>=height[j])){
                    h = height[stk.top()];
                    stk.pop();
                    l = stk.empty() ? j: j - stk.top()-1;
                    if(l*h > maxarea)
                        maxarea = l*h;
                }
                stk.push(j);
            }

        }
        return maxarea;
    }
};


class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) 
            return 0;
        int n = matrix.size(), m = matrix[0].size();
        vector<int>heights(m);
        int maxarea = 0;
        for(int i = 0; i<n; ++i){
            stack<int>stk;
            for(int j = 0; j<=m; ++j){
                int curh = 0;
                if(j<m)
                    heights[j] = matrix[i][j]=='1' ?  heights[j] + 1 : 0 ;
                while(!stk.empty() && (j == m || heights[j] <= heights[stk.top()] ) ){
                    int h = heights[stk.top()];  stk.pop();
                    int x = stk.empty() ? j : j-stk.top() - 1;
                    maxarea = max(maxarea, h*x);
                }
                stk.push(j);
            }
        }
        return maxarea;
    }
};






/*
dp的解：

height代表从上到下，有几个1，
left 代表在现在这个height，left的左侧边界位置
right:代表在现在这个height，这个长方形的右侧边界（右侧边界不包括在长方形内，是长方形右外侧第一个点）

cur_left 是现在左面起，到现在这个点(这个点必须是1)连续都是1的 第一个是1的左起点，比如 0 1 0 1 1 0, 到最后一个1时，cur_left = 3 
cur_right 是从右面起，到现在这个点(这个点必须是1)连续都是1的 第一个是1的右起点
             

第i行的left 继承第i-1行的left,
如果matrix[i][j] = 1, matrix[i-1][j] = 1, matrix[i][j-1] = 1, matrix[i][j-1] = 0, 
0 1
1 1  
那么在第i-1行 left[j-1] = 0, left [j] = j
第i行，  left[j-1] = cur_left = j-1,   left[j] = max(left[j], cur_left) = j

right 跟left的道理一样的


height means from top to this position, there are how many '1'
left means at current position, what is the index of left bound of the rectangle with height[j]. 0 means at this position, no rectangle. (现在这个矩形的左边的下标)
right means the right bound index of this rectangle. 'n' means no rectangle.

matrix
0 0 0 1 0 0 0
0 0 1 1 1 0 0
0 1 1 1 1 1 0

height
0 0 0 1 0 0 0
0 0 1 2 1 0 0
0 1 2 3 2 1 0

left
0 0 0 3 0 0 0
0 0 2 3 2 0 0
0 1 2 3 2 1 0

right
7 7 7 4 7 7 7
7 7 5 4 5 7 7
7 6 5 4 5 6 7

result
0 0 0 1 0 0 0
0 0 3 2 3 0 0
0 5 6 3 6 5 0

*/

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int n = matrix.size(), m = matrix[0].size();
        vector<int>height(m,0);
        vector<int>left(m, 0);
        vector<int>right(m,m); 
        int maxarea = 0;
        for(int i = 0; i<n; i++){
            int cur_left = 0, cur_right = m;
            for(int j = 0, k = m-1; j<m; j++, k--){
                if(matrix[i][k] == '1')
                    right[k] = min(right[k], cur_right);
                else{
                    cur_right = k;
                    right[k] = m;
                }
                    
                
                if(matrix[i][j] == '1'){
                    height[j] += 1;
                    left[j] = max(left[j], cur_left);
                }   
                else{
                    height[j] = 0;
                    cur_left = j+1;
                    left[j] = 0;
                }
            }
            for(int j = 0; j<m; j++){
                if((right[j] - left[j])*height[j] >maxarea)
                    maxarea = (right[j] - left[j])*height[j];
            }
        }
        return maxarea;
    }
};


//self
/*

matrix
0 0 0 1 0 0 0
0 0 1 1 1 0 0
0 1 1 1 1 1 0

height
0 0 0 1 0 0 0
0 0 1 2 1 0 0
0 1 2 3 2 1 0

left
-1 -1 -1 3 -1 -1 -1
-1 -1  2 3 2  -1  -1
-1  1  2 3 2  -1  -1

right
8 8 8 4 8 8 8
8 8 5 4 5 8 8
8 6 5 4 5 6 8

result
0 0 0 1 0 0 0
0 0 3 2 3 0 0
0 5 6 3 6 5 0

*/

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) 
            return 0;
        int n = matrix.size(), m = matrix[0].size();
        vector<int>heights(m);
        vector<int>left(m,-1), right(m,m+1);
        int maxarea = 0;
        for(int i = 0; i<n; ++i){
            int curleft= 0, curright = m;
            for(int j = 0; j<m; ++j){
                heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
                left[j] =   matrix[i][j] == '1' ? max(curleft, left[j]): -1;
                curleft =  matrix[i][j] == '1' ? curleft: j+1;
                
                int r = m-j-1;
                right[r] =  matrix[i][r] == '1' ? min(curright, right[r]): m+1;
                curright =  matrix[i][r] == '1' ? curright: r;
            }

            for(int j = m -1; j>=0; --j)
               maxarea = max(maxarea, heights[j]*(right[j] - left[j]));
        }
        return maxarea;
    }
};



class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int n = matrix.size(), m = matrix[0].size(); 
        vector<int>heights(m);
        vector<int>left(m);
        vector<int>right(m, m-1);
        int area = 0;
        for(int i = 0; i<n; i++){
            int cur_left  = 0, cur_right = m-1;
            for(int j = 0, k = m-1; j<m; j++, k--){
                if(matrix[i][k] == '1'){
                    right[k] = min(cur_right, right[k]);
                }else{
                    right[k] = m-1;
                    cur_right = k - 1;
                }
                
                if(matrix[i][j] == '1'){
                    left[j] = max(cur_left, left[j]);
                    heights[j] += 1;
                }else{
                    left[j] = 0;
                    heights[j] = 0;
                    cur_left = j + 1;
                }
            }
            
            
            for(int j = 0; j<m; j++){
                area = max(area, heights[j]*(right[j] - left[j]+1));
            }
        }
        return area;
    }
};



