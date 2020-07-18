/*
Table like this:  
11111
11111
11111
11111
11011

After We use DP to rule each row 
1 2 3 2 1
1 2 3 2 1
1 2 3 2 1
1 2 3 2 1
1 1 0 1 1

After We use DP to rule each column 
1 1 1 1 1
1 2 2 2 1
1 2 2 2 1
1 2 1 2 1
1 1 0 1 1
最大只能是2
*/


class Solution {
public:
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        unordered_map<int,unordered_set<int>>Banned;
        for_each(mines.begin(),mines.end(),[&](auto mine){Banned[mine[0]].insert(mine[1]);});
        
        vector<vector<int>>dp(N, vector<int>(N));
        for(int i = 0; i<N; i++){
            int count = 0;
            for(int j = 0; j<N; j++){//从左到右
                if(Banned.count(i) == 0 || Banned[i].count(j) == 0)count++; 
                else count = 0;
                dp[i][j] = count;
            } 
            
            count = 0;
            for(int j = N-1; j>=0; j--){ //从右到左
                if(Banned.count(i) == 0 || Banned[i].count(j) == 0)count++;
                else count = 0;
                if (count<dp[i][j]) 
                  dp[i][j]  = count;
            }   
        }
        int res = 0;
        for(int j = 0; j<N; j++){
            int count = 0;
            for(int i = 0; i<N; i++){ //从上到下
                if(Banned.count(i) == 0 || Banned[i].count(j) == 0)count++;
                else count = 0;
                if (count<dp[i][j]) 
                  dp[i][j]  = count;
            } 
            
            count = 0;
            for(int i = N-1; i>=0; i--){ //从下到上
                if(Banned.count(i) == 0 || Banned[i].count(j) == 0)count++;
                else count = 0;
                if (count<dp[i][j]) 
                  dp[i][j]  = count;
                res = max(res,dp[i][j]);
            }   
        }
        return res;
        
    }
};


class Solution {
public:
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        if(N == 0) return 0;
        vector<vector<int>>grid(N+1,vector<int>(N+1,N));
        
        for(vector<int>& m : mines)
        {
            grid[m[0]][m[1]] = 0;
        }
        for(int i = 0; i < N; i++)
        {
            int l = 0, r = 0, u = 0, d = 0;
            for(int j = 0, k = N - 1; j < N ; j++, k--)
            {
                //左到右
                grid[i][j] = min(grid[i][j], l = (grid[i][j] == 0 ? 0 : l + 1));
                //右到左
                grid[i][k] = min(grid[i][k], r = (grid[i][k] == 0 ? 0 : r + 1));
                //上到下
                grid[j][i] = min(grid[j][i], u = (grid[j][i] == 0 ? 0 : u + 1));
                //下到上
                grid[k][i] = min(grid[k][i], d = (grid[k][i] == 0 ? 0 : d + 1));
            }
        }
        int ans = 0;
        for(int i = 0; i < N ; i++)
        {
            for(int j = 0; j < N; j++)
            {
                ans = max(ans,grid[i][j]);
            }
        }
        return ans;
    }
};


class Solution {
public:
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        vector<vector<int>>dp(N, vector<int>(N, N+1));
        for_each(mines.begin(),mines.end(),[&](auto mine){dp[mine[0]][mine[1]] = 0;});
        
        for(int i = 0; i<N; i++){
            int l = 0, r = 0, u = 0, d = 0;
            for(int j = 0, k = N-1; j<N;j++, k--){
                dp[i][j] = min(dp[i][j], l = (dp[i][j]==0 ? 0: l+1));
                dp[j][i] = min(dp[j][i], u = (dp[j][i]==0 ? 0: u+1));
                
                dp[i][k] = min(dp[i][k], r = (dp[i][k]==0 ? 0: r+1));
                dp[k][i] = min(dp[k][i], d = (dp[k][i]==0 ? 0: d+1));
            }
        }
        int res = 0;
        for(int i = 0; i<N; i++) for(int j = 0; j<N;j++)
            res = max(res, dp[i][j]);

        
        return res;
        
    }
};

/*

Method 2:

- Iterate over mines of each row:  -1, N 也加进去
- For each mines, 只考虑open spaces between mine and those that lead to a larger plus sign, 
    比如已经有res =  2 and mine 在 positition 1 和 8， 只考虑position 4 和 5
- for each position condersiding as a center, already know how far the plus sign can extend in that row, 
   只要再找 how far it can extend in the column binary search the list of mines in that column
    to find the closest one above and below.


The fact that we only consider open positions that could lead to larger plus signs allows us to 
    skip a large amount of computation in most practical cases.
     
The fact that the number of mines is very small compared to the grid size makes a solution 
where we "iterate over mines" and "binary search over lists of mines" very efficient.



 */

class Solution {
public:
    int orderOfLargestPlusSign(int N, vector<vector<int>>& mines) {
        vector<vector<int>>rows(N);
        vector<vector<int>>cols(N);
        for(int i = 0; i<N; ++i){
            rows[i] = {-1,N};
            cols[i] = {-1,N};
        }
        for(auto mine: mines){
            rows[mine[0]].push_back(mine[1]);
            cols[mine[1]].push_back(mine[0]);
        }
        for(int i = 0; i<N; ++i){
            sort(rows[i].begin(), rows[i].end());
            sort(cols[i].begin(), cols[i].end());
        }
        
        int res = 0;
        for(int i = 0; i<N; ++i){
            for(int j = 0; j<rows[i].size()-1; ++j){
                int left = rows[i][j];
                int right = rows[i][j+1];
                for(int k = left + res + 1; k<right-res; ++k){
                    auto idx = upper_bound(cols[k].begin(), cols[k].end(), i);
                    int bottom = *idx; //大于i行的
                    int up = *(idx-1);
                    res = max(res, min(min(min(k-left, right-k), bottom -i), i -up) );
                }
                
            }
            
            
        }
        
        return res;
    }
};