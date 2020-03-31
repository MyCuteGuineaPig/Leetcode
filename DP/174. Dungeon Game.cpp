/*
174. Dungeon Game

The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. 
The dungeon consists of M x N rooms laid out in a 2D grid. 
Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. 
If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; 
other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

 

Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

 

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path 
RIGHT-> RIGHT -> DOWN -> DOWN.



*/


/**
 * 
 * dp[i,j] 代表进入这个点前需要的豆子 min(dp[i+1,j],dp[i,j+1])- point[i,j] 用减法原因是因为点是负的，需要消耗的点，减减负负得正，就加回去
 * 
 * */


class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        if(dungeon.size()==0) return 0;
        int n = dungeon.size(), m = dungeon[0].size();
        vector<int>dp(m+1, INT_MAX);
        dp[m] = dp[m-1] = 1;
        for(int i = n-1; i>=0; dp[m] = INT_MAX, i--)
            for(int j = m-1; j>=0; j--)
                dp[j] = max(min(dp[j], dp[j+1]) -dungeon[i][j], 1);         
        return dp[0];
    }
};



static int x = []() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}();
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        if(dungeon.size()==0) return 0;
        int n = dungeon.size(), m = dungeon[0].size();
        vector<int>dp(m+1, INT_MAX);
        dp[m] = dp[m-1] = 1;
        for(int i = n-1; i>=0; dp[m] = INT_MAX, i--)
            for(int j = m-1; j>=0; j--)
                dp[j] = max(min(dp[j], dp[j+1]) -dungeon[i][j], 1);
                
        return dp[0];
    }
};