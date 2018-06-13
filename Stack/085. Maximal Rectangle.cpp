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

/*
dp的解：

height代表从上到下，有几个1，
left 代表在现在这个height，left的左侧边界位置
right:代表在现在这个height，这个长方形的右侧边界（右侧边界不包括在长方形内，是长方形右外侧第一个点）

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
            for(int j = 0; j<m; j++)
                height[j] = matrix[i][j] == '1' ? height[j]+1 : 0;

            for(int j = 0; j<m; j++)
                if(matrix[i][j] == '1') left[j] = max(left[j], cur_left);
                else{  cur_left = j+1; left[j] = 0; }

            for(int j = m-1; j>=0; j--)
                if(matrix[i][j] == '1') right[j] = min(right[j], cur_right);
                else{ cur_right = j; right[j] = m; }
                    
            for(int j = 0; j<m; j++)
                if((right[j] - left[j])*height[j] >maxarea)
                    maxarea = (right[j] - left[j])*height[j];

        }
        return maxarea;
    }
};