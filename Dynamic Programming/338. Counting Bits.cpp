

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int>dp(num+1, 0);
        for(int i = 1; i<=num; i++){
            dp[i] = dp[i>>1] + (i&1);
        }
        return dp;
    }
};

/*
Obviously, this is overlap sub problem, and we can come up the DP solution. 
    For now, we need find the function to implement DP.

dp[0] = 0;

dp[1] = dp[0] + 1;

dp[2] = dp[0] + 1;

dp[3] = dp[1] +1;

dp[4] = dp[0] + 1;

dp[5] = dp[1] + 1;

dp[6] = dp[2] + 1;

dp[7] = dp[3] + 1;

dp[8] = dp[0] + 1;
...

This is the function we get, now we need find the other pattern for the function to get the general function.
    After we analyze the above function, we can get
dp[0] = 0;

dp[1] = dp[1-1] + 1;

dp[2] = dp[2-2] + 1;

dp[3] = dp[3-2] +1;

dp[4] = dp[4-4] + 1;

dp[5] = dp[5-4] + 1;

dp[6] = dp[6-4] + 1;

dp[7] = dp[7-4] + 1;

dp[8] = dp[8-8] + 1;
..

Obviously, we can find the pattern for above example, so now we get the general function

dp[index] = dp[index - offset] + 1;

*/

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int>dp(num+1, 0);
        int offset = 1;
        for(int i = 1; i<=num; i++){
            if(i == offset*2)
                offset *= 2;
            dp[i] = dp[i-offset]+1;
        }
        return dp;
    }
};

//与上面的原理一样
/*
i = (i + 1) % cnt:

2  i = 0,   (0+1) % 1 = 0
3  i = 0,   (0+1) % 2 = 1
4  i = 1,    (1+1)%2 = 0
5  i = 0,   (0 + 1) % 3 = 1
6  i = 1,   (1 + 1) % 3 = 2
 */
class Solution2 {
public:
    vector<int> countBits(int num) {
        vector<int> res{0};
        for (int i = 0, cnt = res.size();
             res.size() <= num;
             i = (i + 1) % cnt) { 
            if (i == 0) { // 
                cnt = res.size();
            }
            res.emplace_back(res[i] + 1);
        }
        return res;
    }
};

/*

i&(i-1) drops the lowest set bit. 
For example: i = 14, its binary representation is 1110, 
so i-1 is 1101, i&(i-1) = 1100, the number of "1" in its binary representation decrease one, 
so ret[i] = ret[i&(i-1)] + 1. 


 */

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> ret(num+1, 0);
        for (int i = 1; i <= num; ++i)
            ret[i] = ret[i&(i-1)] + 1;
        return ret;
    }
};

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> res(num+1, 0);
        for(int i = 1; i <= num; i++){
            if((i & 1) == 0){
                res[i] = res[i >> 1];
            }else{
                res[i] = res[i - 1] + 1;
            }
        }
        return ret;
    }
};