/**
 Reason: why cannot start from top-left to bottom-right

Explanation 1: 

This is because, in order to compute HP[i][j], you will need to make sure of two things:

1. your HP[i][j]+dungeon[i][j] should be >0
2. your HP[i][j]+dungeon[i][j] should be large enough, so that it will be sufficient to cover the minimum requirement on HP 
    for the next step, be it right or down (take whichever requires smaller HP).

So you see, because of the second requirement, your calculation of HP[i][j] will depend on later steps 
    that you could take. This is why you have to know these later steps ahead of time, 
    thus calculating from the bottom right.


Explanation 2:

If we start from left top, in addition to minimize initial HP required to get (i,j), 
    we also have to maximize HP left when we get (i,j) in order to decide whether we need more initial HP in the next step. 
    It doesn't directly depend on things at (i-1,j) and (i,j-1).


For example, at some point we have two paths, from left or from up.

1. Left: min HP required is 1, max HP left is 1
2. Up: min HP required is 5, max HP left is 100

How do we choose now? If we choose smaller min HP required, this requirement may increase to 5 later anyway and 95 HP is wasted.

I'd be happy to know if anyone can do this from left-top (not trying different initial HP values).

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


class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        if(dungeon.size()==0) return 0;
        int n = dungeon.size(), m = dungeon[0].size();
        vector<vector<int>>dp(n, vector<int>(m,0));
        dp[n-1][m-1] = max(1, 1 - dungeon[n-1][m-1]);
        
        for(int i = n - 2; i>=0; --i)
            dp[i][m-1] = max(1, dp[i+1][m-1]- dungeon[i][m-1]);
        for(int j = m - 2; j>=0; --j)
            dp[n-1][j] = max(1, dp[n-1][j+1] -dungeon[n-1][j] );
        
        for(int i = n - 2; i>=0; --i)
            for(int j = m-2; j>=0; --j)
                dp[i][j] = max(1, min(dp[i][j+1], dp[i+1][j])-dungeon[i][j]);
        return dp[0][0];
    }
};








//Binary Search
//Complexity: O(log(INT_MAX)MN)
class Solution {
public:
    int calculateMinimumHP(vector<vector<int> > &dungeon) {
        int N = dungeon.size();
        int M = dungeon[0].size();

        // just pick a simple path through the dungeon to obtain an upperbound
        int lowerbound = 0;
        int upperbound = 1;
        for (int i = 0; i < M; i++) {
            int val = dungeon[0][i];
            if (val < 0) upperbound += (-val);
        }
        for (int i = 0; i < N; i++) {
            int val = dungeon[i][M - 1];
            if (val < 0) upperbound += (-val);
        }

        // A number so small impossible to come back alive from
        static const int64_t dead = numeric_limits<int64_t>::min() / 3;

        // Binary search looking for the smallest starting health which we
        // survive from. Invariant we maintain is lowerbound dies and
        // upperbound survives
        while (lowerbound < upperbound - 1) {
            int mid = (upperbound - lowerbound) / 2 + lowerbound;

            // create a buffer N + 1 and M + 1 size so we have sentinal values
            // padding the first row and column.
            auto cur_health = vector<vector<int64_t> >(N + 1);
            for (int n = 0; n <= N; n++) {
                cur_health[n].resize(M + 1, dead);
            }

            // Seed in our starting health
            cur_health[0][1] = cur_health[1][0] = mid;
            for (int n = 1; n <= N; n++) {
                for (int m = 1; m <= M; m++) {
                    cur_health[n][m] = max(cur_health[n-1][m], cur_health[n][m-1]) + dungeon[n-1][m-1];
                    if (cur_health[n][m] < 1) {
                        // Once we are dead, ensure we stay dead
                        cur_health[n][m] = dead;
                    }
                }
            }

            // If we have positive health at the end we survived!
            if (cur_health[N][M] > 0) {
                upperbound = mid;
            } else {
                lowerbound = mid;
            }
        }
        return upperbound;
    }
};