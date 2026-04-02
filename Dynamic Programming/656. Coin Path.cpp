/*
不能是forward DP 只能是backdp,

因为比如这个解， 到69时候，选择了38， 因为38 和47 有一样的cost, 但38更小
但是lexicographically smaller的路径是47, 因为12 比38更小
[1, 12, 47, 69]

[1, 38, 69]

 */

class Solution {
public:
    vector<int> cheapestJump(vector<int>& coins, int maxJump) {
        int n = coins.size();
        // If the end is unreachable or start is blocked
        if (n == 0 || coins[n-1] == -1 || coins[0] == -1) return {};

        // dp[i] is the min cost to reach the end (n-1) starting from index i
        vector<long> dp(n, numeric_limits<long>::max());
        vector<int> next_node(n, -1);
        
        dp[n-1] = coins[n-1];

        // Iterate backwards from the second to last element
        for (int i = n - 2; i >= 0; --i) {
            if (coins[i] == -1) continue;
            
            for (int j = i + 1; j <= min(i + maxJump, n - 1); ++j) {
                if (dp[j] == numeric_limits<long>::max()) continue;
                
                long val = coins[i] + dp[j];
                
                // If we find a lower cost, update.
                // If costs are EQUAL, we don't update because 'j' is increasing.
                // Keeping the smaller 'j' (the one we found first in this loop)
                // ensures the lexicographically smallest path.
                if (val < dp[i]) {
                    dp[i] = val;
                    next_node[i] = j;
                }
            }
        }

        // If dp[0] is still infinity, index n-1 is unreachable
        if (dp[0] == numeric_limits<long>::max()) return {};

        // Reconstruct path starting from index 0
        vector<int> res;
        int cur = 0;
        while (cur != -1) {
            res.push_back(cur + 1);
            cur = next_node[cur];
        }
        
        return res;
    }
};

class Solution {
public:
    vector<int> cheapestJump(vector<int>& coins, int maxJump) {
        int n = coins.size(); 
        vector<long>costs(n, numeric_limits<int>::max());
        vector<vector<int>> paths(n);
        costs[0] = 0;
        paths[0].push_back(1);
        for(int i = 1; i < n; ++i) {
            if (coins[i] == - 1) continue;
            for(int prev = max(0, i - maxJump); prev < i; ++prev) {
                if (costs[i] > coins[i] + costs[prev]) {
                    costs[i] = coins[i] + costs[prev];
                    vector<int>cur = paths[prev];
                    cur.push_back(i+1);
                    paths[i] = cur;
                } else if (costs[i] == coins[i] + costs[prev]) {
                    if (paths[i] > paths[prev]) {
                        vector<int>cur = paths[prev];
                        cur.push_back(i+1);
                        paths[i] = cur;
                    }
                }
            }
        }
        return paths[n-1];
    }
};



class Solution {
public:
    vector<int> cheapestJump(vector<int>& coins, int maxJump) {
        int n = coins.size();
        if (n == 0 || coins[n - 1] == -1) return {};

        vector<long> dp(n, INT_MAX);
        vector<int> next_node(n, -1);
        
        // Start from the end
        dp[n - 1] = coins[n - 1];

        for (int i = n - 2; i >= 0; --i) {
            if (coins[i] == -1) continue;
            
            for (int j = i + 1; j <= min(i + maxJump, n - 1); ++j) {
                if (dp[j] == INT_MAX) continue;
                
                long current_cost = coins[i] + dp[j];
                
                // If we find a cheaper path, OR an equal cost path
                // Because we are moving backwards, picking the earliest j 
                // naturally results in the lexicographically smallest path.
                if (current_cost < dp[i]) {
                    dp[i] = current_cost;
                    next_node[i] = j;
                } else if (current_cost == dp[i]) {
                    // In a tie, the smaller index j is already handled by 
                    // the fact that we iterate j from i+1 upwards.
                    // (Actually, no specific check needed here if loop is forward)
                }
            }
        }

        if (dp[0] == INT_MAX) return {};

        // Reconstruct path
        vector<int> path;
        int curr = 0;
        while (curr != -1) {
            path.push_back(curr + 1);
            curr = next_node[curr];
        }
        return path;
    }
};