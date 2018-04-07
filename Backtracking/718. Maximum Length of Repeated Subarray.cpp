/*
718. Maximum Length of Repeated Subarray

Given two integer arrays A and B, return the maximum length of an subarray that appears in both arrays.

Example 1:
Input:
A: [1,2,3,2,1]
B: [3,2,1,4,7]
Output: 3
Explanation: 
The repeated subarray with maximum length is [3, 2, 1].
Note:
1 <= len(A), len(B) <= 1000
0 <= A[i], B[i] < 100
*/



/*
DP 
Since a common subarray of A and B must start at some A[i] and B[j], 
let dp[i][j] be the longest common prefix of A[i:] and B[j:]. 
Whenever A[i] == B[j], we know dp[i][j] = dp[i+1][j+1] + 1. Also, the answer is max(dp[i][j]) over all i, j.

We can perform bottom-up dynamic programming to find the answer based on this recurrence. 
Our loop invariant is that the answer is already calculated correctly and stored in dp for any larger i, j.


*/

class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        vector<vector<int>>dp(A.size()+1, vector<int>(B.size()+1,0));
        int res = 0;
        for(int i = A.size()-1; i>=0; i--)
            for(int j = B.size() - 1; j>=0; j--)
                if(A[i] == B[j]){
                    dp[i][j] = dp[i+1][j+1]+1;
                    res = max(res,dp[i][j]);
                }
        return res;
    }
};


class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        vector<vector<int>>dp(A.size()+1, vector<int>(B.size()+1,0));
        int res = 0;
        for(int i = 0; i<A.size(); i++)
            for(int j = 0; j<B.size(); j++)
                if(A[i] == B[j]){
                    dp[i+1][j+1] = dp[i][j]+1; //dp[i+1][j+1] 代表i,j 的数
                    res = max(res,dp[i+1][j+1]);
                }
        return res;
    }
};



/*
DP space is only O(N) 不是O(M*N)
*/

class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        vector<int>dp(B.size()+1,0); //loop through B 每一个Loop through A的，现在A跟上一个A比较
        int res = 0;
        for(int i = 0; i<A.size(); i++)
            for(int j = B.size()-1; j>=0; j--) // 从后往前的原因是，避免从0到B。size() 假如用到dp[5] = dp[4] + 1, 而上一个循环因为不match，把dp[4] 设置成0了
                res = max(res, dp[j+1] = A[i] == B[j] ? dp[j]+1: 0);
                
        return res;
    }
};
