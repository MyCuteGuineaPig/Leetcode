/*

375. Guess Number Higher or Lower II


We are playing the Guess Game. The game is as follows:

I pick a number from 1 to n. You have to guess which number I picked.

Every time you guess wrong, I'll tell you whether the number I picked is higher or lower.

However, when you guess a particular number x, and you guess wrong, you pay $x. You win the game when you guess the number I picked.

Example:

n = 10, I pick 8.

First round:  You guess 5, I tell you that it's higher. You pay $5.
Second round: You guess 7, I tell you that it's higher. You pay $7.
Third round:  You guess 9, I tell you that it's lower. You pay $9.

Game over. 8 is the number I picked.

You end up paying $5 + $7 + $9 = $21.
Given a particular n ≥ 1, find out how much money you need to have to guarantee a win.
*/


/*
It is actually confusing that the example shown in the problem description is not the best stragety to guess the final target number, 
and the problem itself is asking for the lowest cost achieved by best guessing strategy.
The example description should be updated.

---POSSIBLY, it can also add some example about the BEST Strategy---
The example description should be:

first introducebest strategyto guess:

for one number, like 1, best strategy is 0$
for two number, like 3,4, best strategy is 3$, which can be understood in this way: you have two way to guess: a) start by guess 4 is the target, 
(the worst case is) if wrong, you get charged $4, then immediately you know 3 is the target number, get get charged $0 by guessing that, 
and finally you get charged $4. b) similarly, if you start by 3, (the worst case is) if wrong, you get charged $3, 
then you immediately know that 4 is the target number, and get charged $0 for guessing this, and finally you get charged $3. In summary:
range ---------> best strategy cost
3, 4 ---------> $3
5, 6 ---------> $5
…
for three number, the best strategy is guess the middle number first, and (worst case is) if wrong, you get charged that middle number money, 
and then you immediately know what target number is by using “lower” or “higher” response, so in summary:
range ---------> best strategy cost
3, 4, 5 ---------> $4
7, 8, 9 ---------> $8

for four numbers, the best strategy is the first number + the third number
for five numbers, the best strategy is the second number + the fourth number

…
for more numbers, it can simply be reduced them into smaller ranges, and here is why DP solution make more sense in solving this.
suppose the range is [start, end]
the strategy here is to iterate through all number possible and select it as the starting point, say for any k between start and end, 
the worst cost for this is: k+DP( start, k-1 ) + DP(k+1, end ), and the goal is minimize the cost, 
so you need the minimum one among all those k between start and end


*/


/*

如果binary search的话，先猜中间的，因为会告诉是大还是小，所以猜了中间的，只要cost是多的哪个半个就行, k+dp(k+1,end), k是binary search猜的数
*/

class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>>dp(n+1,vector<int>(n+1,0));
        for(int j = 2; j<=n; j++){
            for(int i = j-1; i>=0; i--){
                int localmax = 0, globalmin = numeric_limits<int>::max();
                for(int k = i+1; k<j; k++){
                    localmax = k + max(dp[i][k-1],dp[k+1][j]);
                    globalmin = min(globalmin,localmax);
                }
                dp[i][j] = (j == i+1 ? i: globalmin);
            }
        }
        return dp[1][n];
    }
};