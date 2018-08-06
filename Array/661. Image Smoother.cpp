/*
661. Image Smoother

Given a 2D integer matrix M representing the gray scale of an image, 
you need to design a smoother to make the gray scale of each cell becomes the average gray scale 
(rounding down) of all the 8 surrounding cells and itself. If a cell has less than 8 surrounding cells, then use as many as you can.

Example 1:
Input:
[[1,1,1],
 [1,0,1],
 [1,1,1]]
Output:
[[0, 0, 0],
 [0, 0, 0],
 [0, 0, 0]]
Explanation:
For the point (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
For the point (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
For the point (1,1): floor(8/9) = floor(0.88888889) = 0
Note:
The value in the given matrix is in the range of [0, 255].
The length and width of the given matrix are in the range of [1, 150].


*/


class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
        int n = M.size(), m = M[0].size();
        for(int i = 0; i<n; i++){
            for(int j = 0; j<m; j++){
                int cnt = 0, sum = 0;
                for(int I = max(0, i-1); I<=min(n-1, i+1); I++) 
                    for(int J = max(0, j-1); J<=min(m-1, j+1); J++){
                        cnt++;
                        if(M[I][J]&255) { sum += (M[I][J] & 255);}
                    }
                
                M[i][j] |= (sum/cnt)<<8;
                    
                        
            }
        }
        
        for(int i = 0; i<n; i++)
            for(int j = 0; j<m; j++)
                M[i][j] >>= 8;
        
        return M;
    }
};


class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
        const auto& m = M.size(), &n = M[0].size();
        vector<vector<int>> result(M);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result[i][j] = getGray(M, i, j);
            }
        }
        return result;
    }

private:
    int getGray(const vector<vector<int>>& M, int i, int j) {
        const auto& m = M.size(), &n = M[0].size();
        double total = 0.0;
        int count = 0;
        for (int r = -1; r < 2; ++r) {
            for (int c = -1; c < 2; ++c) {
                const auto& ii = i + r;
                const auto& jj = j + c;
                if (0 <= ii && ii < m && 0 <= jj && jj < n) {
                    total += M[ii][jj];
                    ++count;
                }
            }
        }
        return static_cast<int>(total / count);
    }
};