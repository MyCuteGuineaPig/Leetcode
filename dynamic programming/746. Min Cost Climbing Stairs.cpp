/*
746. Min Cost Climbing Stairs

On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

Once you pay the cost, you can either climb one or two steps. 
You need to find minimum cost to reach the top of the floor, 
and you can either start from the step with index 0, or the step with index 1.

Example 1:
Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.
Example 2:
Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].
Note:
cost will have a length in the range [2, 1000].
Every cost[i] will be an integer in the range [0, 999].

*/




class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int take = cost[0], skip = 0;
        for(int i = 1; i<cost.size(); i++){
            int temp = take;
            take = min(take,skip)+cost[i];
            skip = temp;
        }
        return min(take, skip);
    }
};


/*

            2   4   8   15   7   1   2
    take    2   4   10  19  17   18  21
    skip    0   2   4   10  19   19  18

   take 是经过这个台阶
   skip 是跳过这个台阶


            2   4    8    15   7   1   2
    cost    2   4    10   19   17  18  19
    

   cost是到达此点的cost, 返回倒数第一和倒数第二点的最小值
   class Solution {
    public:
        int minCostClimbingStairs(vector<int>& cost) {
            int n=(int)cost.size();
            vector<int> dp(n);
            dp[0]=cost[0];
            dp[1]=cost[1];
            for (int i=2; i<n; ++i)
                dp[i]=cost[i]+min(dp[i-2],dp[i-1]);
            return min(dp[n-2],dp[n-1]);
        }
    };


*/



string x = [](){
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    return "";
}();
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int take = 0, skip = 0;
        for(auto p: cost){
            int temp = take;
            take = min(take,skip)+p;
            skip = temp;
        }
        return min(take, skip);
    }
};


class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        return go(cost, cost.size());
    }
private:
    unordered_map<int,int> memo;
    int go(vector<int>& c, int n){
        if (memo.count(n)) return memo[n];
        if (n<=1) return memo[n]=c[n];
        return memo[n]=(n==c.size() ? 0 : c[n])+min(go(c,n-2),go(c,n-1));
    }
};