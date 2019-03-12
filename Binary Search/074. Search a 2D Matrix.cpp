/*
74. Search a 2D Matrix

Write an efficient algorithm that searches for a value in an m x n matrix. 
This matrix has the following properties:

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
Example 1:

Input:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 3
Output: true
Example 2:

Input:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 13
Output: false
*/


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty() || matrix[0].empty()) return false;
        auto it = upper_bound(matrix.begin(),matrix.end(), target, [](const int b,const vector<int> & a){return b<a[0];});
        int i = --it-matrix.begin(); 
        if (i<0) return false;
        auto it2 = lower_bound(matrix[i].begin(),matrix[i].end(),target,[](const int v, const int b){return v<b;});
        int j = it2 - matrix[i].begin(); 
        return matrix[i][j]==target;
    }
};

/*
Don't treat it as a 2D matrix, just treat it as a sorted list
*/


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty() || matrix[0].empty()) return false;
        int n = matrix.size(), m = matrix[0].size();
        int l = 0, r = n*m-1;
        while(l<=r){
            int mid = l + (r-l)/2;
            if(matrix[mid/m][mid%m]>=target)
                r = mid-1;
            else l = mid+1;
        }  
        return l<=n*m-1 && matrix[l/m][l%m] == target;
    }
};


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty() || matrix[0].empty()) return false;
        int n = matrix.size(), m = matrix[0].size();
        int l = 0, r = n*m-1;
        while(l<r){
            int mid = l + (r-l)/2;
            if(matrix[mid/m][mid%m]>=target)
                r = mid;
            else l = mid+1;
        }  
        return matrix[l/m][l%m] == target;
    }
};


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty() || matrix[0].empty()) return false;
        int n = matrix.size(), m = matrix[0].size();
        int l = 0, r = n*m;
        while(l<r){
            int mid = (l+r)>>1;
            int num = matrix[mid/m][mid%m] ;
            if(num == target) return true;
            else if(num > target) 
                r = mid;
            else l = mid + 1;
        }       
        return false; 
    }

};
