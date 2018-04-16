/*
357. Count Numbers with Unique Digits

Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10n.

Example:
Given n = 2, return 91. (The answer should be the total numbers in the range of 0 ≤ x < 100, excluding [11,22,33,44,55,66,77,88,99])

*/

/*
DP
*/

class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if(n == 0) return 1;
        vector<int>dp(n,1);
        dp[0] = 10;
        for(int i = 1; i<n; i++){
            int num = 9, j = i;
            while(j>=0){
                dp[i] *= num;
                if(j<i) num--;
                j--;
            }
            dp[i] += dp[i-1];
            //cout<<dp[i]<<endl;
        }
        return dp[n-1];
    }
};

/*Static Dynamic Programming */

class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if(n == 0) return 1;
        static vector<int> dp= {10};
        if(dp.size()<=n){
            for(int i = dp.size(); i<n; i++){
                int num = 9, j = i;
                dp.push_back(1);
                while(j>=0){
                    dp[i] *= num;
                    if(j<i) num--;
                    j--;
                }
                dp[i] += dp[i-1];
                //cout<<dp[i]<<endl;
            }
        }
        return dp[n-1];
    }
};



/*
better version
*/


class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if(n == 0) return 1;
        if(n>10) n = 10;
        vector<int>dp(n,0);
        dp[0] = 10;
        int num = 9, accum = 9;
        for(int i = 1; i<n; i++){
            accum *= num--;
            dp[i] += accum + dp[i-1];
        }
        return dp[n-1];
    }
};

/*Static Dynamic Programming */
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if(n == 0) return 1;
        if(n>10) n = 10;
        static vector<int> dp= {10};
        if(dp.size()<=n){
            int num = 9, accum = 9;
            int j = 1;
            while(j++<=dp.size()){
                accum *= num--;
            }
            for(int i = dp.size(); i<n; i++){
                dp.push_back(accum);
                dp[i] += dp[i-1];
                accum *= num--;
                //cout<<dp[i]<<endl;
            }
        }
        return dp[n-1];
    }
};


/*
backtracking
*/
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        vector<int>used(10,0);
        return backtrack(used, n > 10 ? 10: n, 0);
    }
    
    int backtrack(vector<int>&used, const int& n, int cur){
        if(cur>=pow(10,n))
            return 0;
        int tot = 1;
        for(int i = cur == 0 ? 1: 0; i<=9; i++){
            if(!used[i])
            {
                used[i] = 1;
                tot += backtrack(used, n, cur*10+i);
                used[i] = 0;
            }
        }
        return tot;
        
    }
};

