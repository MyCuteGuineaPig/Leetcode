
/*
https://leetcode.com/problems/arithmetic-slices-ii-subsequence/discuss/92822/Detailed-explanation-for-Java-O(n2)-solution

3的时候加1， 4的时候result + 2， 5个pair 时候result + 3， 6个pair 时候result + 4， 每次加就是把排序往后拽一位, 然后加一位新的

   3        4        5               6
3 [2,4,6]

4 [2,4,6] [4,6,8]
          [2,4,6,8]

5 [2,4,6] [4,6,8]    [6,8,10]
          [2,4,6,8]  [4,6,8,10]
                      [2,4,6,8,10]


6 [2,4,6] [4,6,8]    [6,8,10]       [8,10,12]
          [2,4,6,8]  [4,6,8,10]     [6,8,10,12]
                      [2,4,6,8,10]  [4,6,8,10,12]
                                    [2,4,6,8,10,12]

dp[i][diff] 表示到i为止，长度大于等于2个(注：不是3个) 差为diff 的 Arithmetic subsequence 数量, 
    这样，下一个数可以直接append i的后面，组成新的Arithmetic subsequence , res += dp[i][diff]

比如 [1,2,3,4],  
    dp[2][1]( 3的位置) = 2 表示 (1,2,3), (2,3), 后面的4 直接接上这两个就可以组成新的Arithmetic subsequence, (1,2,3,4), (2,3,4)
    dp[3][1] = 3 表示 (1,2,3,4), (2,3,4), (3,4)


*/

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int result = 0;
        vector<unordered_map<long long, int>> dp(A.size());
        for (int i = 1; i < A.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                const auto diff = static_cast<long long>(A[i]) - A[j];
                ++dp[i][diff]; //important, [2,4,6,8], 比如 在6，[4,6]又可以作为起点
                if (dp[j].count(diff)) {
                    dp[i][diff] += dp[j][diff];
                    result += dp[j][diff];
                }
            }
        }
        return result;
    }
};




class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        vector<unordered_map<long long,int>>dp(A.size());
        int res = 0;
        for(int i = 0; i<A.size(); ++i){
            for(int j = 0; j<i; ++j){
                long long diff = static_cast<long long>(A[i]) - A[j];
                res +=  dp[j][diff];
                dp[i][diff] += dp[j][diff]+1;
            }
        }
        return res;
    }
};