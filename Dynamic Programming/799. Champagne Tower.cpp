
/*
比如六杯水，每杯要是大于1，就减去1，然后pass一半给底下的水

6      0     0    0   
2.5   2.5    0    0  
0.75  1.5   0.75  0   
0     0.25  0.25  0  

*/

/*
complexity: O(N^2)  space: O(N^2)
*/

class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<vector<double>>dp(query_row+1, vector<double>(query_row+1));
        dp[0][0] = poured;
        for(int i = 0; i<query_row; i++){
            for(int j = 0; j<=i; j++){
                dp[i+1][j] += max((dp[i][j]-1)*0.5,0.0);
                dp[i+1][j+1] += max((dp[i][j]-1)*0.5,0.0);
            }
        }
        return min(dp[query_row][query_glass], 1.0);
    }
};


//2020
class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<vector<double>>dp(101, vector<double>(101));
        dp[0][0] = poured;
        bool next = true;
        for(int i = 0; i<query_row && next; ++i){
            next = false;
            for(int j =0; j<=i; ++j){
                if(dp[i][j] > 1)
                {
                    next = true;
                    dp[i+1][j] += (dp[i][j] - 1)/2;
                    dp[i+1][j+1] += (dp[i][j] - 1)/2;
                }
            }
        }
        return min(dp[query_row][query_glass],1.0);
    }
};

/*

Top Down TLE

class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<vector<double>>dp(101, vector<double>(101, -1));
        dp[0][0] = poured;
        return min(topDown(dp, query_row, query_glass), 1.0);
    }
    
    double topDown(vector<vector<double>>&dp, int i, int j){
        if(i<0 || j < 0)
            return 0;
        if(dp[i][j] > 0) return dp[i][j];
        return dp[i][j] = max((topDown(dp, i-1, j-1)-1.0)/2, 0.0) + max((topDown(dp, i-1,j)-1)/2,0.0);
    }
    
};

 */



/*
complexity: O(N^2)  space: O(N)
*/
class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<double>dp(query_row+1);
        dp[0] = poured;
        for(int i = 0; i<query_row; i++){
            for(int j = i; j>=0; j--){
                dp[j+1] += max((dp[j]-1)*0.5,0.0);
                dp[j] = max((dp[j]-1)*0.5,0.0);
            }
        }
        return min(dp[query_glass], 1.0);
    }
};



class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        vector<double> res(102);
        res[0] = poured;
        for (int row = 1; row <= query_row; row++)
            for (int i = row; i >= 0; i--)
                res[i + 1] += res[i] = max(0.0, (res[i] - 1) / 2);
        return min(res[query_glass], 1.0);
    }
};