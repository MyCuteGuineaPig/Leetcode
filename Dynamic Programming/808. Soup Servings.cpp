/*
808. Soup Servings


There are two types of soup: type A and type B. Initially we have N ml of each type of soup. There are four kinds of operations:

Serve 100 ml of soup A and 0 ml of soup B
Serve 75 ml of soup A and 25 ml of soup B
Serve 50 ml of soup A and 50 ml of soup B
Serve 25 ml of soup A and 75 ml of soup B
When we serve some soup, we give it to someone and we no longer have it.  
Each turn, we will choose from the four operations with equal probability 0.25. 
If the remaining volume of soup is not enough to complete the operation, we will serve as much as we can.  
We stop once we no longer have some quantity of both types of soup.

Note that we do not have the operation where all 100 ml's of soup B are used first.  

Return the probability that soup A will be empty first, plus half the probability that A and B become empty at the same time.

 

Example:
Input: N = 50
Output: 0.625
Explanation: 
If we choose the first two operations, A will become empty first. 
For the third operation, A and B will become empty at the same time. 
For the fourth operation, B will become empty first. 
 So the total probability of A becoming empty first plus half the probability that A and B become empty at the same time, 
 is 0.25 * (1 + 1 + 0.5 + 0) = 0.625.

Notes:

0 <= N <= 10^9. 
Answers within 10^-6 of the true value will be accepted as correct.


*/


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