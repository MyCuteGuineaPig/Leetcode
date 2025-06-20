class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        if (mat.empty() || mat[0].empty()){
            return {};
        }
        vector<int>res;
        int i = 0, j = 0;
        bool up = true;
        int n = mat.size(), m = mat[0].size();
        while (i != n - 1 || j != m -1 ){
            res.push_back(mat[i][j]);
            if (up){
                if (i == 0 && j != m-1){
                    j = j + 1;
                    up = false;
                } 
                else if (j == m - 1 ){
                    i = i +  1;
                    up = false;
                }
                else {
                    i = i - 1;
                    j = j + 1;
                }
                
            } else {
                if (j == 0 && i != n - 1){
                    i = i + 1;
                    up = true;
                } 
                else if (i == n - 1){
                    j = j +  1;
                    up = true;
                }
                else{
                    i = i + 1;
                    j = j - 1;
                }
            }
        }
        res.push_back(mat[n-1][m-1]);
        return res;
    }
};


class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        if (mat.empty() || mat[0].empty()){
            return {};
        }
        vector<int>res;
        int i = 0, j = 0;
        bool up = true;
        int n = mat.size(), m = mat[0].size();
        for(int d = 0; d < n + m - 1; ++d){
            int index_i = d < n ? d : n - 1; 
            int index_j = d < n ? 0 : d - n + 1; 
            vector<int>tmp;
            while ( index_i >= 0 && index_j < m) {
                tmp.push_back(mat[index_i--][index_j++]);
            }
            if(d % 2) {
                reverse(tmp.begin(), tmp.end());
            }
            res.insert(res.end(), tmp.begin(), tmp.end());
        }
        return res;
    }
};