//2020 
/*
dp[i] 表示 当以s[i] 为最后一个element 且 s[i]必须是最后一个element时候，最小的cut
 */
class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        int L = A[0].size(), n = A.size();
        vector<int>dp(L,101);
        dp[0] = 0;
        
        for(int r = 1; r<L; ++r){
            dp[r] = r;
            for(int l = r-1; l>=0; --l){
                int cur = -1;
                for(int i = 0; i <n; ++i){
                    if(A[i][r] >= A[i][l])
                        cur = max(cur, dp[l] + r-l-1); //如果保留第r位, 那么cut必须是对所有A[i][r] 都成立，就是取最大值
                    else{
                        cur = -1;
                        break;
                    } 
                }
                if(cur!=-1)
                     dp[r] = min(dp[r], cur);//不同位置时候，取最小的cut
            }
        }
        int res = 101;
        for(int i = 0; i<L; ++i)
            res = min(res, L - i - 1 + dp[i]);
        return res;
    }
};



/*
dp[i] means the longest subsequence ends with i-th element.
For all j < i, if A[][j] < A[][i], then dp[j] = max(dp[j], dp[i] + 1)

 */

class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        int m = A.size(), n = A[0].length(), res = n - 1, k;
        vector<int>dp(n, 1);
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < j; ++i) {
                for (k = 0; k < m; ++k) {
                    if (A[k][i] > A[k][j]) break;
                }
                if (k == m && dp[i] + 1 > dp[j]) //对于所有的A[][j] <= A[][i]
                    dp[j] = dp[i] + 1;
            }
            res = min(res, n - dp[j]);
        }
        return res;
    }
};


class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        int m = A.size();
        int n = A[0].size();
        vector<int> dp(A[0].size(), 1);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                if(cmp(A, i, j)) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return n - *max_element(dp.begin(), dp.end());
    }
    
    bool cmp(vector<string> &arr, int i, int j) {
        for(int k = 0; k < arr.size(); k++) {
            if(arr[k][j] > arr[k][i]) return 0;
        }
        return 1;
    }
};



class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        int l = A[0].length(), res = 101;
        vector<int>dp(l, 0);
        for(int i = l-1; i>=0; --i)
            res = min(res, l - topDown(A,dp,i));
            
        return res;
    }
    
    int topDown(vector<string>&A, vector<int>&dp, int index){
        if(index == 0)
            return 1;
        if(dp[index])
            return dp[index];
        dp[index] = 1;
        for(int i = index-1; i>=0; --i){
            int k = 0;
            for(; k<A.size(); ++k) if(A[k][i] > A[k][index]) break;
            if(k==A.size())
                dp[index] = max(dp[index], topDown(A,dp, i)+1);
        }
        return dp[index];
    }
};