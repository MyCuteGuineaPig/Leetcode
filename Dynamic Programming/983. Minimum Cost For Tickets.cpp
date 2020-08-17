
/*
dp[i] 表示当以day i结束travel时，最小的cost
*/
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int n = days.back();
        vector<int>dp(n+31, numeric_limits<int>::max());
        dp[0] = 0;
        int res = numeric_limits<int>::max();
        for(int i = 1, j1 = 0, j7 = 0, j30 = 0; i<=n+30; ++i){
            dp[i] = dp[i-1];
            if(j1 < days.size() && i == days[j1]){
                dp[i] = dp[i-1] + costs[0];
                ++j1;
            }
            if(i - 7 >= 0)
                dp[i] = min(dp[i], dp[i-7] + costs[1]);
            if(i - 30 >= 0)
                dp[i] = min(dp[i], dp[i-30] + costs[2]);
            if(i >= n)
                res = min(res, dp[i]);
        }
        return res;
    }
};



/*

Method 1. Track calendar days

We track the minimum cost for all calendar days in dp. 

For non-travel days, the cost stays the same as for the previous day. 
For travel days, it's a minimum of yesterday's cost plus single-day ticket,
 or cost for 8 days ago plus 7-day pass, or cost 31 days ago plus 30-day pass.

 One Tricky Test:

[1,4,6,7,8,20]
[2,7,15]

days                 0        1       2   3       4    5
Calandar days  0  1   2   3   4   5   6   7   8   9   10
Cost           0  2   2   2   4   4   6   7   7   9    9
               ------------7 days----------
                           --------------- 7 days-------
 */
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
      unordered_set<int> travel(begin(days), end(days));
      int dp[366] = {};
      for (int i = 1; i < 366; ++i) {
        if (travel.find(i) == travel.end()) dp[i] = dp[i - 1];
        else dp[i] = min({ dp[i - 1] + costs[0], dp[max(0, i - 7)] + costs[1], dp[max(0, i - 30)] + costs[2]});
      }
      return dp[365];
    }
};





//Top-Down
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
      int n = days.back();
      vector<int>dp(n+1, -1);
        
      return topDown(days, costs, dp, days.size()-1, n);
    }
    
    int topDown(vector<int>&days, vector<int>&costs, vector<int>&dp, int i, int d){
        if(d == 0)
            return 0;
        if(dp[d] >= 0)
            return dp[d];
        if(i>=0 && d == days[i])
            dp[d] = min({topDown(days, costs,dp, i-1, d-1)+costs[0],
                         topDown(days, costs,dp, i-1, max(0,d-7))+costs[1],
                         topDown(days, costs,dp, i-1, max(0,d-30))+costs[2]
                         });
        else
            dp[d] = topDown(days, costs, dp, i, d-1);
        return dp[d];
    }
};

/*
Optimization 
 */
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
      unordered_set<int> travel(begin(days), end(days));
      int dp[30] = {};
      for (int i = days.front(); i <= days.back(); ++i) {
        if (travel.find(i) == travel.end()) dp[i % 30] = dp[(i - 1) % 30];
        else dp[i % 30] = min({ dp[(i - 1) % 30] + costs[0],
            dp[max(0, i - 7) % 30] + costs[1], dp[max(0, i - 30) % 30] + costs[2] });
      }
      return dp[days.back() % 30];
    }
};


/**
 Method 2: Track Travel Days

 We track the minimum cost for each travel day. 
 We process only travel days and store {day, cost} for 7-and 30-day passes in the last7 and last30 queues. 
 After a pass 'expires', we remove it from the queue. 
 This way, our queues only contains travel days for the last 7 and 30 days, 
 and the cheapest pass prices are in the front of the queues.


Example:

TraCK Travel days

Travel Days: 1  4  6  7  9   10
Cost:        2  4  6  7  9    9
Last7:       7  9  11 13 14   16
            ---7 days--
                 ---- 7 days ---

 */


class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs, int cost = 0) {
      queue<pair<int, int>> last7, last30;
      for (auto d : days) {
        while (!last7.empty() && last7.front().first + 7 <= d) last7.pop();
        while (!last30.empty() && last30.front().first + 30 <= d) last30.pop();
        last7.push({ d, cost + costs[1] });
        last30.push({ d, cost + costs[2] });
        cost = min({ cost + costs[0], last7.front().second, last30.front().second });
      }
      return cost;
    }
};

//Method 3. O(nlogn)
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        map<int, int> dp = {{-30,0}};
        auto cost = [&](int day){return prev(dp.upper_bound(day))->second;};
        for(int d:days) dp[d] = min({costs[0] + cost(d-1), costs[1] + cost(d-7), costs[2] + cost(d-30)});
		// if you want O(N) solution, simply add one line in loop:  if(dp.size() > 31) dp.erase(dp.begin());   
        return dp[days.back()];
    }
};


//TopDown
class Solution {
public:
    vector<int>memo;
    int mincostTickets(vector<int>& days, vector<int>& costs) {
      int n = days.back();
      memo.resize(n+1,0);
        
      return mincostTickets(0, days, costs);
    }
        
    int mincostTickets(int dayIndex, vector<int>& days, vector<int>& costs) {
        if (dayIndex == days.size()) {
            return 0;
        }
        
        if (memo[dayIndex] != 0) {
            return memo[dayIndex];
        }
        
        // Choose a pass, update dayIndex, and accumulate totalCost
        int totalCostDay = costs[0] + mincostTickets(getNextDayToBuy(dayIndex, days, 1), days, costs);   
        int totalCostWeek = costs[1] + mincostTickets(getNextDayToBuy(dayIndex, days, 7), days, costs);
        int totalCostMonth = costs[2] + mincostTickets(getNextDayToBuy(dayIndex, days, 30), days, costs);
        
        // Return the one with min totalCost
        memo[dayIndex] = min({totalCostMonth, totalCostDay, totalCostWeek});
        return memo[dayIndex];
    }
    
    int getNextDayToBuy(int dayIndex, vector<int>& days, int duration) {
        int endDay = days[dayIndex] + duration - 1;
        int newDayIndex = dayIndex;
		
        while (newDayIndex < days.size() && days[newDayIndex] <= endDay) {
            newDayIndex++;
        }
        
        return newDayIndex;
    }
};
