//2020 Bottom-up
class Solution {
public:
    int knightDialer(int N) {
        vector<vector<int>>move = {{4,6},{6,8},{7,9},{4,8},{0,3,9},{},{0,1,7},{2,6},{1,3},{2,4}};
        int M = pow(10,9)+7;
        vector<int>dp(10,1);
        for(int i = 1 ; i<N; ++i){
            vector<int>tmp(10);
            for(int j = 0; j<=9; ++j)
                for(auto nxt: move[j])
                    tmp[nxt] = (tmp[nxt] + dp[j])%M;
            dp =tmp;
        }
        
        long res = 0;
        for(auto i: dp)
            res = (res+i)%M;
        return res;
    }
};


/*
2020  Log(n)
 */

class Solution {
public:
    int Mod = pow(10,9)+7;
    
    int knightDialer(int N) {
        if ( N == 1) return 10;
        vector<vector<long>>move(10, vector<long>(10)); 
        move[0][4] = 1;  move[0][6] = 1;
        move[1][6] = 1; move[1][8] = 1;
        move[2][7] = 1; move[2][9] = 1;
        move[3][4] = 1; move[3][8] = 1;
        move[4][0] = 1; move[4][3] = 1; move[4][9] = 1;
        move[6][0] = 1; move[6][1] = 1; move[6][7] = 1;
        move[7][2] = 1; move[7][6] = 1; 
        move[8][1] = 1; move[8][3] = 1;
        move[9][2] = 1; move[9][4] = 1;
        
        vector<vector<long>>state = power(N-1, move);
        
        
        long res = 0;
        for(int i = 0; i<10; ++i){
             for(auto j: state[i]){
                res = (res+j)%Mod;
        return res;
    }
    
    vector<vector<long>>power(int n, vector<vector<long>>x){
        if(n == 1)
            return x;
        auto res = power(n/2, x);
        res = multiply(res, res);
            res = multiply(res, x);
        }
        return res;
    }
    
    vector<vector<long>>multiply(vector<vector<long>>&a, vector<vector<long>>&b){
        int n = a.size(), m = b[0].size();
        vector<vector<long>>res(n, vector<long>(m));

        for(int i = 0; i<n; ++i)
            for(int j = 0; j<m; ++j)
                for(int k = 0; k<b.size(); ++k)
                    res[i][j] = (res[i][j] + a[i][k]* b[k][j])%Mod;
        return res;
    }
    
};


//2020 TopDown
class Solution {
public:
    int Mod = pow(10,9)+7;
    
    int knightDialer(int N) {
        if ( N == 1) return 10;
        vector<vector<long>>move(10, vector<long>(10)); 
        move[0][4] = 1;  move[0][6] = 1;
        move[1][6] = 1; move[1][8] = 1;
        move[2][7] = 1; move[2][9] = 1;
        move[3][4] = 1; move[3][8] = 1;
        move[4][0] = 1; move[4][3] = 1; move[4][9] = 1;
        move[6][0] = 1; move[6][1] = 1; move[6][7] = 1;
        move[7][2] = 1; move[7][6] = 1; 
        move[8][1] = 1; move[8][3] = 1;
        move[9][2] = 1; move[9][4] = 1;

        vector<vector<long>>dp(N, vector<long>(10));    
        
        long res = 0;
        for(int i = 0; i<10; ++i){
            res = (res+topDown(N-1, i, move, dp))%Mod;
        }
        return res;
    }
    
    long topDown(int n, int i, vector<vector<long>>&move, vector<vector<long>>&dp){
        if(n == 0)
            return 1;
        if(dp[n][i])
            return dp[n][i];
        for(int j = 0; j<10; ++j)
            if(move[i][j])
                dp[n][i] = (dp[n][i] + topDown(n-1, j, move, dp))%Mod;
        return dp[n][i];
    }
   
    
};



class Solution {
public:
    vector<vector<int>> ms = { {4, 6}, {6, 8}, {7, 9}, {4, 8}, {3, 9, 0}, {}, {1, 7, 0}, {2, 6}, {1, 3}, {4, 2}};
    int knightDialer(int N) {
        vector<int> d1(10, 1), d2(10);
        for (; --N > 0; swap(d1, d2))
            for (auto i = 0; i < d1.size(); ++i) 
                d2[i] = accumulate(begin(ms[i]), end(ms[i]), 0, [&](int s, int i) {return (s + d1[i]) % 1000000007;});
        
            return accumulate(begin(d1), end(d1), 0, [](int s, int n) {return (s + n) % 1000000007;});
    }

};