/*
813. Largest Sum of Averages


What is the largest score we can achieve?

Note that our partition must use every number in A, and that scores are not necessarily integers.

Example:
Input: 
A = [9,1,2,3,9]
K = 3
Output: 20
Explanation: 
The best choice is to partition A into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
We could have also partitioned A into [9, 1], [2], [3, 9], for example.
That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
 

Note:

1 <= A.length <= 100.
1 <= A[i] <= 10000.
1 <= K <= A.length.
Answers within 10^-6 of the correct answer will be accepted as correct.


*/


/*
dp[k][i] 表示在A[:i] 中最多分k次 所得的平均数最大和
dp[k][i] = max(dp[k][i], dp[k-1][j] + (sum[i]-sum[j])/(i-j)) 

(sum[i]-sum[j])/(i-j) 是从(j,i] 的平均数, 
dp[k-1][j] k-1次partition A[0:j] 平均数最大和
循环j比较sum of k-1 partition dp[k-1][j] and new added average 
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
            for(int i = k; i<n; i++){
                for(int j = k-1; j<i; j++){
                    dp[k][i] = max(dp[k][i], dp[k-1][j] + (sum[i]-sum[j])/(i-j));
                }   
            }
        }
        return dp[K-1][n-1];
    }
};


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
            for(int i = k,index = k%2; i<n; i++){
                for(int j = k-1; j<i; j++){
                    dp[index][i] = max(dp[index][i], dp[index^1][j] + (sum[i]-sum[j])/(i-j));
                }   
            }
        }
        return dp[K%2^1][n-1];
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