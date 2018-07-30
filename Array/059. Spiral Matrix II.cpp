/*
59. Spiral Matrix II

Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.

Example:

Input: 3
Output:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]


*/


class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>>res(n, vector<int>(n));
        for(int top = 0, bottom = n-1, l = 0, r = n - 1, cnt = 1; cnt <= n*n; top++, bottom--, l++, r--){
            //cout<<l<<" r "<<r<<" top "<<top<<" bottom "<<bottom<<endl;
            for(int i = l; i<=r; i++)  res[top][i] = cnt++;
            for(int i = top+1; i<bottom; i++) res[i][r] = cnt++;
            for(int i = r; top < bottom && i>=l; i--) res[bottom][i] = cnt++;
            for(int i = bottom-1; l < r && i>top; i--) res[i][l] = cnt++;
        }
        return res;
    }
};


class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>>res(n, vector<int>(n));
        enum Action{RIGHT, DOWN, LEFT, UP};
        Action action = RIGHT;
        for(int i = 0, j = 0, top = 0, bottom = n-1, l = 0, r = n - 1, cnt = 1; cnt <= n*n; cnt++){
            res[i][j] = cnt;
            switch(action){
                case RIGHT:
                    if(j<r) j++;
                    else { action = DOWN; top++; ++i;}
                    break;
                case DOWN:
                    if(i<bottom) ++i;
                    else {action = LEFT; r--; --j;}
                    break;
                case LEFT:
                    if(j>l) --j;
                    else {action = UP; bottom--; --i;}
                    break;    
                case UP:
                    if(i>top) --i;
                    else {action = RIGHT; l++; ++j;}
                    break;       
            }
        }
        return res;
    }
};


class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ret(n, vector<int>(n,0));
        int x = 1;
        for(int i = 0; i < (n+1)/2; i++){
            for(int j = i; j <= n - 1 - i; j++)    ret[i][j] = x++;
            for(int j = i+1; j <= n - 1 - i; j++)   ret[j][n-1-i] = x++;
            for(int j = n - i - 2; j>=i; j--)   ret[n-1-i][j] = x++;
            for(int j = n - i - 2; j>i; j--)    ret[j][i] = x++;
        }
        return ret;
    }
};


class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> spiral (n,vector<int>(n,0));
        int dr=0,dc=1,r=0,c=0;
        for (int k=1; k<=n*n; k++) {
            spiral[r][c]=k;
            if (spiral[(r+dr+n)%n][(c+dc+n)%n]) {
                int tempdc=dc;
                dc=-dr;
                dr=tempdc;
            }
            r+=dr;
            c+=dc;
        }
        return spiral;
    }
};