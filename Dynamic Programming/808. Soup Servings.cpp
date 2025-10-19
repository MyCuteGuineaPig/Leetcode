/*
Example:
Input: N = 50
Output: 0.625
Explanation: 
   A, B 一开始都是50 ml,
   1. serve A 100 ml, serve B 0  ml,  probability = 1 * 0.25
   2. serve A 75 ml,  serve B 25 ml,  probability = 1 * 0.25
   3. serve A 50 ml,  serve B 50 ml,  probability = 0.5 * 0.25 
   4. serve A 25 ml,  serve B 75 ml,  probability = 0 * 0.25 

 0.25 * (1 + 1 + 0.5 + 0) = 0.625.

*/


/*
It's obvious that A is easier to be empty than B. And when N gets bigger, we have less chance to run out of B first.
So as N increases, our result increases and it gets closer to 100 percent = 1.

Answers within 10^-5 of the true value will be accepted as correct.
Now it's obvious that when N is big enough, result is close enough to 1 and we just need to return 1.
When I incresed the value of N, I find that:
When N = 4800, the result = 0.999994994426
When N = 4801, the result = 0.999995382315
So if N>= 4800, just return 1 and it will be enough.

 */

class Solution {
public:
    double soupServings(int n) {
        if (n >= 4800) return 1.0;
        n = (n + 24) /25;
        vector<vector<double>>dp (n + 1, vector<double>(n+1));
        dp[0][0] = 0.5;
        for(int i = 1; i<=n; ++i)
            dp[0][i] = 1;
        for(int i = 1; i<=n; ++i){
            for(int j = 1; j <= n; ++j) {
                dp[i][j] = 0.25 * (dp[max(i-4, 0)][j] + dp[max(i-3, 0)][j-1] + + dp[max(i-2, 0)][max(j-2, 0)] + dp[i-1][max(j-3, 0)]);
            }
        }
        return dp[n][n];
    }
};

class Solution {
public:
    unordered_map<int,unordered_map<int,double>>dp;
    double soupServings(int N) {
        return N>4800 ? 1.0 : helper(N,N);
    }
    
    double helper(int A, int B){
        if(dp.count(A) && dp[A].count(B)) return dp[A][B];
        if (A<=0 && B <= 0) return 0.5;
        else if (A<=0) return 1.0;
        else if(B<=0) return 0.0;
        return dp[A][B] = 0.25*(helper(A-100, B)+ helper(A-75, B-25)+ helper(A-50, B - 50) +helper(A-25, B-75)) ;
    } 
};


/**
 we use only O(200 * 200) time & space.

 否则用 O(5000 * 5000) time & space if A != B, (which sounds like 250mb)

(N + 24) / 25 

如果不大于25 的话, 直接return 0.5 , 比如 N = 3, 3/25 = 0, 

实际是 0.25*(1 + 0.5 + 0.5 + 0.5) = 0.625

 */

class Solution {
public:
    double memo[200][200];
    double soupServings(int N) {
        return N > 4800 ?  1.0 : f((N + 24) / 25, (N + 24) / 25);
    }
    double f(int a, int b) {
        if (a <= 0 && b <= 0) return 0.5;
        if (a <= 0) return 1;
        if (b <= 0) return 0;
        if (memo[a][b] > 0) return memo[a][b];
        memo[a][b] = 0.25 * (f(a-4,b)+f(a-3,b-1)+f(a-2,b-2)+f(a-1,b-3));
        return memo[a][b];
    }
};


//Bottom-up
class Solution {
public:
    double soupServings(int N) {
        if(N >= 4800) {
            return 1.0; 
        }
        
        N = (N + 24) / 25; /* instead of viewing the soups by their ml content, we can view the soups in terms of 
		servings where each 25ml of soup is 1 serving. This simplifies the problem and allows us to fit the problem in
		a 2D dp array. */
		
        vector<vector<double>>dp(N+1, vector<double>(N+1));
        
        dp[0][0] = 0.5;  /* when soup A and soup B reach 0, we only want half the probability, so we divide 1 by 2 
		when they both reach 0ml */
        
        for(int i = 1; i <= N; i++) {
			/* when soup A is 0 and soup B isn't, we know that there is 100% chance that soup A reached 0 before
			soup B, so we set it at 1 */
            dp[0][i] = 1;
        }
        
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
				/* we look at the 4 cases. Each case contributes 25% to the whole probability, so we need to multiply
				each of them by .25. find(i-4, j), means we look at the 100ml to 0ml case. 
				We subtract 4 from i (100ml from soup A) and 0 from j (0ml from soup B) */
                dp[i][j] = 0.25 * (find(dp, i - 4, j) + find(dp, i - 3, j - 1) + find(dp, i - 2, j - 2) + find(dp, i - 1, j - 3));
            }
        }
        return dp[N][N];
    }
    
    double find(vector<vector<double>>& dp, int i, int j) {
        if(i < 0) {
            i = 0;
        }
        if(j < 0) {
            j = 0;
        }
        return dp[i][j];
    }
};