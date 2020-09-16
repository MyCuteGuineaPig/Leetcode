
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



/*
ZigZag Search
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }
        int row = 0;
        int col = matrix[0].size() - 1;
        while (row < matrix.size() && col >= 0) {
            if (matrix[row][col] == target) {
                return true;
            } else if (matrix[row][col] < target) {
                row++;
            } else {
                col--;
            }
        }
        return false;
    }
};