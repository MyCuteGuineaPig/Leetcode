/*
54. Spiral Matrix

Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

Example 1:

Input:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
Output: [1,2,3,6,9,8,7,4,5]
Example 2:

Input:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

*/


//定义 up, down, left, right 四个边界，每次loop 在最外围的一圈
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return{};
        vector<int>res;
        for(int l = 0, r = matrix[0].size()-1, top = 0, bottom = matrix.size()-1; top<=bottom && l<=r; top++, bottom--, l++, r--){
            for(int i = l; i<=r; i++)
                res.push_back(matrix[top][i]);
            for(int i = top+1; i<bottom; i++)
                res.push_back(matrix[i][r]);
            for(int i = r; top<bottom && i>=l; i--)
                res.push_back(matrix[bottom][i]);
            for(int i = bottom - 1; l<r && i>top; i--)
                res.push_back(matrix[i][l]);
        }
        return res;
    }
};

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = m ? matrix[0].size() : 0, u = 0, d = m - 1, l = 0, r = n - 1, p = 0;
        vector<int> order(m * n);
        while (u <= d && l <= r) {
            for (int col = l; col <= r; col++) {
                order[p++] = matrix[u][col];
            }
            if (++u > d) {
                break;
            }
            for (int row = u; row <= d; row++) {
                order[p++] = matrix[row][r];
            }
            if (--r < l) {
                break;
            }
            for (int col = r; col >= l; col--) {
                order[p++] = matrix[d][col];
            }
            if (--d < u) {
                break;
            }
            for (int row = d; row >= u; row--) {
                order[p++] = matrix[row][l];
            }
            if (l++ > r) {
                break;
            }
        }
        return order;
    }
};


// Time:  O(m * n)
// Space: O(1)
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return{};
        vector<int>res;
        enum Action{RIGHT, DOWN, LEFT, UP};
        Action action = RIGHT;
        for(int l = 0, r = matrix[0].size()-1, top = 0, bottom = matrix.size()-1, i = 0, j = 0; top<=bottom && l<=r;){
            res.push_back(matrix[i][j]);
            //cout<<i<<" j "<<j<<" top "<<top<<" down "<<bottom<<" l "<<l<<" r "<<r <<" action "<<action<<endl;
            switch(action){
                case RIGHT:
                    if(j < r) j++;
                    else action = DOWN, ++top, ++i;
                    break;
                case DOWN:
                    if(i < bottom ) ++i;
                    else action = LEFT, --r, --j;
                    break;
                case LEFT:
                    if(j>l) --j;
                    else action = UP, --bottom, --i;
                    break;
                case UP:
                    if (i>top) --i;
                    else action = RIGHT, ++l , j++;
                    break;
            }
        }
        return res;
    }
};


/*
When traversing the matrix in the spiral order, 
at any time we follow one out of the following four directions: 
RIGHT DOWN LEFT UP. Suppose we are working on a 5 x 3 matrix as such:

0 1 2 3 4 5
  6 7 8 9 10
  11 12 13 14 15

Imagine a cursor starts off at (0, -1), i.e. the position at '0', 
then we can achieve the spiral order by doing the following:

Go right 5 times
Go down 2 times
Go left 4 times
Go up 1 times.
Go right 3 times
Go down 0 times -> quit

Notice that the directions we choose always follow the order 'right->down->left->up', 
and for horizontal movements, the number of shifts follows:{5, 4, 3}, and vertical movements follows {2, 1, 0}.

Thus, we can make use of a direction matrix that records the offset for all directions, 
then an array of two elements that stores the number of shifts for horizontal and vertical movements, respectively. 
This way, we really just need one for loop instead of four.

Another good thing about this implementation is that: If later we decided to do spiral traversal on a different direction
(e.g. Counterclockwise), then we only need to change the Direction matrix; the main loop does not need to be touched.
*/
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<vector<int> > dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<int> res;
    int nr = matrix.size();     if (nr == 0) return res;
    int nc = matrix[0].size();  if (nc == 0) return res;
    
    vector<int> nSteps{nc, nr-1};
    
    int iDir = 0;   // index of direction.
    int ir = 0, ic = -1;    // initial position
    while (nSteps[iDir%2]) {
        for (int i = 0; i < nSteps[iDir%2]; ++i) {
            ir += dirs[iDir][0]; ic += dirs[iDir][1];
            res.push_back(matrix[ir][ic]);
        }
        nSteps[iDir%2]--;
        iDir = (iDir + 1) % 4;
    }
    return res;
}