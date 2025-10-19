/*
dp[k][i] 表示在A[:i] 中最多分k次 所得的平均数最大和
dp[k][i] = max(dp[k][i], dp[k-1][j] + (sum[i]-sum[j])/(i-j)) 

(sum[i]-sum[j])/(i-j) 是从(j,i] 的平均数, 
dp[k-1][j] k-1次partition A[0:j] 平均数最大和
循环j比较sum of k-1 partition dp[k-1][j] and new added average 


比如  [9, 1, 2, 9, 2,3, 4] 可以分成4 分

k = 3 时
      [9, 1, 2, 9, 2,3] 时候
       (1) (2 ) (3    )

k = 4 时:  dp = dp[k][3] + (sum(6) - sum(3))/3
      [9, 1, 2, 9,  | 2 ,3， 4] 
       (1) (2 ) (3)  （4    ）
*/


class Solution {
public:
   
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        vector<vector<double>>dp(n,vector<double>(n,0.0));
        
        vector<double>sum(n); sum[0] =dp[0][0]  =  A[0];
        for(int i = 1;i<n; i++){
            sum[i] = sum[i-1] + A[i];
            dp[0][i] = sum[i]/(i+1);
        }
         
        for(int k = 1; k<K; k++){
            for(int i = k; i<n; i++){  // 长度是 len = k + 1, 所以必须至少需要 k + 1 个数, 起点是 k
                for(int j = k-1; j<i; j++){ // len = k + 1. sum[k-1] 表示 长度为前len -1 个数和,
                    dp[k][i] = max(dp[k][i], dp[k-1][j] + (sum[i]-sum[j])/(i-j));
                }   
            }
        }
        return dp[K-1][n-1];
    }
};


/* 
2025
dp[i][k]  表示在 A[0..i] 中分成 k 组 (包括i点) 所能得到的最大平均值和
*/
class Solution {
public:
    double largestSumOfAverages(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int>presum(n);
        vector<vector<double>>dp (n, vector<double>(k));
        for(int i = 0; i < n; ++i) {
            presum[i] = (i == 0? 0 : presum[i-1]) + nums[i];
            dp[i][0] = (double)presum[i] / (i+1);
        }

        for(int m = 1; m < k; ++m) {
            for(int i = 1; i < n; ++i) {
                for(int j = m-1; j <i; ++j) {
                    dp[i][m] = max(dp[i][m], dp[j][m-1] + (double)(presum[i]-presum[j])/(i-j) );
                }
            }
        }
        return dp[n-1][k-1];
    }
};

class Solution {
public:
   
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        vector<int>sum(n);
        
        for (int i = 0;i < n; i++) 
            sum[i] = A[i] + (i > 0 ? sum[i-1] : 0); 
        
        vector<vector<double>>dp(K+1, vector<double>(n));

        for (int groups = 1; groups <= K; groups++) {
            for (int s = 0; s + groups <= n; s++) {
                if (groups == 1) {
                    dp[groups][s] = ((double)(sum[n-1] - sum[s] + A[s]) / (n-s));
                    //sum[n-1] - sum[s] 没有算 A[s] 所以加上A[s]
                    continue;
                }
                for (int e = s; e + groups <= n; e++) {
                    dp[groups][s] = max(dp[groups][s], (dp[groups-1][e+1] + (double) (sum[e] - sum[s] + A[s]) / (e - s + 1)));
                }
            }
        }
        return dp[K][0];
    }
    
};

//O(n) space

class Solution {
public:
   
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        vector<int>sum(n);
        
        for (int i = 0;i < n; i++) 
            sum[i] = A[i] + (i > 0 ? sum[i-1] : 0); 
        
        vector<double>dp(n);

        for (int groups = 1; groups <= K; groups++) {
            for (int s = 0; s + groups <= n; s++) {
                if (groups == 1) {
                    dp[s] = ((double)(sum[n-1] - sum[s] + A[s]) / (n-s));
                    //sum[n-1] - sum[s] 没有算 A[s] 所以加上A[s]
                    continue;
                }
                for (int e = s; e + groups <= n; e++) {
                    dp[s] = max(dp[s], (dp[e+1] + (double) (sum[e] - sum[s] + A[s]) / (e - s + 1)));
                }
            }
        }
        return dp[0];
    }
    
};



/*
dp[k][i] 还是表示在A[:i] 中最多分k次 所得的平均数最大和

*/
class Solution {
public:
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        vector<vector<double>>dp(K,vector<double>(n,0.0));
        double cur = 0.0;
        for(int i = 0; i<n; i++)
        {
            cur += A[i];
            dp[0][i] = cur/(i+1);
        }
        return helper(dp,A,n,K-1);
    }
    
    double helper(vector<vector<double>>& dp, vector<int>& A, int n, int k){
        if(n<=0) return 0;
        if(dp[k][n-1]>0.0)
            return dp[k][n-1];
        double cur = 0.0;
        for(int i = n-1; i>k-1; i--){
            cur += A[i];
            dp[k][n-1] = max(dp[k][n-1], cur/(n-i) + helper(dp, A, i, k-1));
        }
        return dp[k][n-1];
    }
};



// 2020 Top-Down
class Solution {
public:
   
    double largestSumOfAverages(vector<int>& A, int K) {
        int n = A.size();
        vector<vector<double>>dp(n,vector<double>(n,-1));
        
        vector<double>sum(n); sum[0] =dp[0][0]  =  A[0];
        for(int i = 1;i<n; i++){
            sum[i] = sum[i-1] + A[i];
            dp[0][i] = sum[i]/(i+1);
        }
        return topDown(A, dp, sum, K-1, A.size()-1);
    }
         
        double topDown(vector<int>& A, vector<vector<double>>&dp,  vector<double>&sum, int k, int i){
            if(dp[k][i]>=0)
                return dp[k][i];
            for(int l = k-1; l<=i; ++l)
                dp[k][i] = max(dp[k][i], (sum[i]-sum[l])/(i-l) +topDown(A, dp, sum, k-1, l));
            return dp[k][i];
        }
    
};
