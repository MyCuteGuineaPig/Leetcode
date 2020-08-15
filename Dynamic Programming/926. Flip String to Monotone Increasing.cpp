/*
dp[i][0]: 第i位，若为0需要的step
dp[i][1]: 第i位, 若为1需要的step

*/

class Solution {
public:
    int minFlipsMonoIncr(string S) {
        int n = S.size();
        vector<vector<int>>dp(n+1, vector<int>(2));
        for(int i = 1; i<=n;++i){
            if(S[i-1] == '0'){
                dp[i][0] = dp[i-1][0];   //i-1是0，i是0，step不变
                dp[i][1] = dp[i-1][1] + 1;; //i-1是1，i是0，所以step + 1
            }
            else{
                dp[i][0] = dp[i-1][0] + 1; // i-1 是0, i 是1，step + 1
                dp[i][1] = min(dp[i-1][0], dp[i-1][1]); //i 是 0， 若i-1 是1, step 不变;  若i-1是0，step + 1
            }
            
        }
        return min(dp[n][0], dp[n][1]);
    }
};


/*
Method 2:

1. Skip 0's until we encounter the first 1.
2. Keep track of number of 1's in onesCount (Prefix).
3. Any 0 that comes after we encounter 1 can be a potential candidate for flip. Keep track of it in flipCount.
4. If flipCount exceeds oneCount - (Prefix 1's flipped to 0's)
    a. Then we are trying to flip more 0's (suffix) than number of 1's (prefix) we have.
    b. Its better to flip the 1's instead.
 */


class Solution {
public:
    int minFlipsMonoIncr(string S) {
        int n = S.size();
        
        int oneCount = 0, flipCount = 0;
        for(int i = 0; i<n;++i){
            if(S[i] == '0'){
               if(oneCount == 0) continue;
               else flipCount++;
             }
              else{
                    oneCount++;
              }
              if(flipCount > oneCount){
                  flipCount = oneCount;
              }
        }
        return flipCount;
    }
};


class Solution {
public:
    int minFlipsMonoIncr(const std::string& S, int counter_one  = 0, int counter_flip = 0) {
        for (auto ch : S) counter_flip = std::min(counter_one += ch - '0', counter_flip + '1' - ch);
        return counter_flip;
    }
};



/*
Method 3:

Count of '0' -> '1' flips going left to right, and store it in f0.
Count of '1' -> '0' flips going right to left, and store it in f1.
Find a the smallest f0[i] + f1[i].

f0[i]: S[:i-1] 有几个1需要flip 成0
f1[i]: S[i:]  有几个0需要flip 成1   
 */
class Solution {
public:
    int minFlipsMonoIncr(string S, int res = INT_MAX) {
        vector<int> f0(S.size() + 1), f1(S.size() + 1);
        for (int i = 1, j = S.size() - 1; j >= 0; ++i, --j) {
            f0[i] += f0[i - 1] + (S[i - 1] == '0' ? 0 : 1);
            f1[j] += f1[j + 1] + (S[j] == '1' ? 0 : 1);
        }
        for (int i = 0; i <= S.size(); ++i) res = min(res, f0[i] + f1[i]);
        return res;
    }
};


class Solution {
public:
    int minFlipsMonoIncr(string S, int f0 = 0, int f1 = 0) {
        for (auto c : S) {
            f0 += c - '0';
            f1 = min(f0, f1 + 1 - (c - '0'));
        }
        return f1;
    }
};