
/*
A[i]>A[i-1] && B[i] > B[i-1】 
- i 和 i-1， 都不变
- i 和 i-1， 都变

A[i]>B[i-1] && B[i] > A[i-1]
- i-1变， i不变
- i-1不变, i变


             1,   3,      3,  8,    7,  11
             1,   2,      4,  6,    9,  13
  non_swap:  0   (0,1)    1  (1,2)  2   (2,3)   
  swap:      1   (2,1)    1  (2,2)  2   (3,3)
*/


class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int swap = 1, no_swap = 0, temp_swap = 0, temp_non_swap = 0;
        for(int i = 1; i<A.size();i++){
            temp_swap = temp_non_swap = INT_MAX;
            if(A[i]>A[i-1] && B[i] > B[i-1]){
                temp_non_swap = no_swap; //保持现状, 上一个没变，现状不变
                temp_swap = swap+1; //上一个swap了，这个继续swap， 上一个变，现状变
            }
            if(A[i]>B[i-1] && B[i] > A[i-1]){
                temp_non_swap = min(temp_non_swap,swap); //保持上一个swap， 上一个变，现在不变
                temp_swap = min(temp_swap,no_swap+1); //上一个没swap，现在swap， 上一个不变，现状变
            }
            swap = temp_swap;
            no_swap = temp_non_swap;
        }
        return min(swap, no_swap);
    }
};



/*
2020 
dp[i][0] 表示A[i] 和 B[i] 不交换, 需要最小swap 
dp[i][1] 表示i位的 A[i] 和 B[i]交换  需要最小swap 

dp[i][0] = min(
              dp[i-1][0],  i-1 no swap, i no swap,  A[i]>A[i-1], B[i] > B[i-1]
              dp[i-1][1]   i-1 swap,  i no swap,  A[i] > B[i-1], B[i] > A[i-1], 因为 i-1 位的 A,B 交换了
              )


dp[i][1] = min(
              dp[i-1][0] +1,  i-1 no swap, i swap,  A[i]>B[i-1], B[i] > A[i-1]
              dp[i-1][1] + 1,   i-1 swap,  i swap,  A[i] > A[i-1], B[i] > B[i-1], 因为 i-1 位的 A,B 都交换了
           
              )
 */

class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<vector<int>>dp(n,vector<int>(n, n+1));
        //[0] 表示 no swap, [1] 表示swap
        dp[0][0] = 0; dp[0][1] = 1;
        
        for(int i = 1; i<n; ++i){
            if(A[i] > A[i-1] && B[i] > B[i-1]) //i & i -1 both no swap
                dp[i][0] = dp[i-1][0]; 
            if(A[i] > B[i-1] && B[i] > A[i-1]) //i-1 swap, i no swap
                dp[i][0] = min(dp[i][0], dp[i-1][1]);
            
            if(A[i] > B[i-1] && B[i] > A[i-1]) //i-1 no swap, i swap
                dp[i][1] = dp[i-1][0]+1;
            
            if(A[i] > A[i-1] && B[i] > B[i-1]) //i-1 swap, i swap
                dp[i][1] = min(dp[i][1], dp[i-1][1]+1);
            
        }
        return min(dp[n-1][0], dp[n-1][1]);
    }
};



class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<vector<int>>dp(n,vector<int>(2));
        dp[0][0] = 0; dp[0][1] = 1;
        
        for (int i = 1; i < dp.size(); i++) {
            if ( (A[i] > A[i-1] && B[i] > B[i-1]) && !( A[i] > B[i-1] && B[i] > A[i-1]) ) {
                // A[i], B[i] cannot swap at A[i]
                dp[i][0] = dp[i-1][0];
                dp[i][1] = dp[i-1][1] + 1;
            } else if (!(A[i] > A[i-1] && B[i] > B[i-1]) && (A[i] > B[i-1] && B[i] > A[i-1]) ) {
                //A[i], B[i] must swap
                dp[i][0] = dp[i-1][1];
                dp[i][1] = dp[i-1][0] + 1;
            } else {//swap, not swap both are fine
                dp[i][0] = min(dp[i-1][0], dp[i-1][1]);
                dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + 1;
            }
        }
        return min(dp[n - 1][0], dp[n - 1][1]);
    }
};



// 2020 Top-Down
class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<vector<int>>dp(n,vector<int>(2));
        return min(topDown(A, B, dp, n-1, 1),topDown(A, B, dp, n-1, 0));
    }
    
    int topDown(const vector<int>& A, const vector<int>& B, vector<vector<int>>&dp, int i, int swap){
        if(i == 0) // 0 is no swap, 1 is swap
            return swap;
        if(dp[i][swap])
            return dp[i][swap];
        int res = i+1;
        if(A[i] > A[i-1] && B[i] > B[i-1])
            if(swap) res = min(res, topDown(A, B, dp, i-1, swap)+1); //both swap
            else res = min(res, topDown(A,B,dp, i-1, swap)); //i, i-1 no swap
        if(A[i] > B[i-1] && B[i] > A[i-1])
            if(swap) res = min(res, topDown(A, B, dp, i-1, 0)+1); // i-1 no swap, i swap
            else res = min(res, topDown(A,B,dp, i-1, 1)); // i-1 swap, i no swap
        return dp[i][swap] = res;
    }
};



class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<vector<int>>dp(n,vector<int>(2,-1));
        return topDown(A, B, dp, n-1, 0, 2001, 2001);
    }
    
    int topDown(const vector<int>& A, const vector<int>& B, vector<vector<int>>&dp, int i, int swap, int preA, int preB){
        if(i == -1) // 0 is no swap, 1 is swap
            return 0;
        if(dp[i][swap]>=0)
            return dp[i][swap];
        int res = i+1;
        if(A[i] < preA && B[i] < preB )
            res = topDown(A,B, dp, i-1, 0, A[i], B[i]);
        if(A[i] < preB && B[i] < preA)
            res = min(res, topDown(A, B, dp, i-1, 1, B[i], A[i])+1);
        return dp[i][swap] = res;
    }
};

/*
If A[i] > B[i], we say, we have a upward node, elsewise we have a downward note.

If a node max(A[i],B[i]) < min(A[i+1],B[i+1]), we name it a free node.
Because it can changed freely.
Otherwise, a non-free node should have same direction with next node.

So, we find a chain, left of first node is a free node, end with a free node. 
All other node in chain should be non-free nodes.

We known: all nodes in chain should have same direction.
Fixup a chain need min(upward nodes, downward nodes) steps.

So we got the solution: just scan all chains!



[0,4,4,5,9]
[0,1,6,8,10]
 
 i = 0 free node,     A[i] = 0,  A[i+1] = 4,   更新swap = 1
                       B[i] = 0,  B[i+1] = 4

 i = 3 free node,     A[i] = 5,  A[i+1] = 9,   更新swap = 1
                       B[i] = 8,  B[i+1] = 10

 要保证swap 后 A[1：3] 是递增的,  B[1:3] 也是递增的,  


 */
class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int swaps = 0;
        int up = 0, down = 0;
        for (int i = 0; i < A.size(); ++i) {
            if (A[i] > B[i])
                up += 1;
            else
                down += 1;

            if (i == A.size() - 1 || std::max(A[i], B[i]) < std::min(A[i + 1], B[i + 1])) {
                // free node
                swaps += std::min(up, down);
                up = down = 0;
            }
        }
        return swaps;
    }
};