
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        priority_queue<vector<int>>pq;
        for(int i = 0; i<startTime.size(); ++i){
            pq.push({-endTime[i], -startTime[i], profit[i]}); //sort by endTime
        }
        map<int,int>mp;
        int res = 0;
        while(!pq.empty()){
            auto top = pq.top();
            int end = -top[0], start=-top[1], p=top[2];
            pq.pop();
            auto it = mp.upper_bound(start);
            if(it!=mp.begin()){
                --it;
                if(it->second + p > mp.rbegin()->second){  
                    // if new end is not bigger lastest end profit, not update
                    mp[end] = it->second + p;
                    res = max(res, mp[end]);
                }
            }
            else if(mp.empty() || p > mp.rbegin()->second){
                mp[end] = p; // p > mp.rbegin()->second: the profit of current is bigger than last end time profit
                res = max(res, mp[end]);
            }

            //cannot write res = max(res, mp[end]); here
            //because not all start, end will update map, if write here, map is updated everytime
        }
        return res;
    }
};


class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<vector<int>> jobs;
        for (int i = 0; i < n; ++i) {
            jobs.push_back({endTime[i], startTime[i], profit[i]});
        }
        sort(jobs.begin(), jobs.end());
        map<int, int> dp = {{0, 0}};
        for (auto& job : jobs) {
            int cur = prev(dp.upper_bound(job[1]))->second + job[2];
            if (cur > dp.rbegin()->second)
                dp[job[0]] = cur;
        }
        return dp.rbegin()->second;
    }
};


/*
不可以是sort by startTime, 然后正向排序, 

比如: 
[4,2,4,8,2]
[5,5,5,10,8]
[1,2,8,10,4]

Answer: 18

update mp[5] = 8
update mp[8] = 4

      mp[10]  = mp[8] + 10 = 4 + 8 是错误的answer

*/



/*
lgorithm
1. Use a map to store job start times and the maximum profit (zero, initially).
2. Use an unordered map to store start time and job information.
    - We will use this unordered map to look-up jobs by their start time.
3. Since times in the map are sorted, process each time point right to left:
    - Lookup job information in the unordered map by the start time.
    - Set the maximum profit as the greater of:
            - Running maximum profit.
            - Job profit plus maximum profit at the end of the job.
    - Update the running maximum profit.
3. Return the running maximum profit.

*/

class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        vector<vector<int>>time;
        for(int i = 0; i<startTime.size(); ++i){
            time.push_back({-startTime[i], -endTime[i], profit[i]});
        }
        sort(time.begin(), time.end());
        
        map<int,int>mp;
        for(int i = 0; i < time.size(); ++i){
            int start = -time[i][0], end = -time[i][1], p = time[i][2];
            auto it = mp.lower_bound(end);
            if(!mp.empty())
                mp[start] = max(mp.begin()->second, mp[start]);

            /*
                不可以写成 mp[start] = max( mp[start], mp.begin()->second,);
                if start < mp.begin(), mp.begin 就是start 的位置为0，而不是上一个Process的数
            */
            mp[start] = max(mp[start], it == mp.end() ? p : it->second + p);
        }
        return mp.begin()->second;
    }
};

class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        map<int, int> times;
        unordered_map<int, vector<pair<int, int>>> jobs;
        for (auto i = 0; i < startTime.size(); ++i) {
            times[startTime[i]] = 0;
            jobs[startTime[i]].push_back({ endTime[i], profit[i] });
        }    
        int max_profit = 0;
        for (auto it = rbegin(times); it != rend(times); ++it) {
            for (auto job : jobs[it->first]) {
                auto ik = times.lower_bound(job.first); //job.first is endTime 
                max_profit = max(max_profit, (ik == end(times) ? 0 : ik->second) + job.second);
            }
            it->second = max_profit; //update times[it->first] = max_profit
        }
        return max_profit;
    }  
};

/*
Instead of copying the job information, we can use an index array to look-up data 
in the original arrays in the requried order.

*/

class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        vector<int> idx(startTime.size());
        iota(begin(idx), end(idx), 0);
        sort(begin(idx), end(idx), [&](int i, int j) { return startTime[i] > startTime[j]; });
        map<int, int> memo;
        int max_profit = 0;
        for (auto i = 0; i < idx.size(); ++i) {
            auto it = memo.lower_bound(endTime[idx[i]]);
            max_profit = max(max_profit, (it == end(memo) ? 0 : it->second) + profit[idx[i]]);
            memo[startTime[idx[i]]] = max_profit;
        }
        return max_profit;
    }
};




/*
Top Down
*/
class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        vector<vector<int>>time;
        for(int i = 0; i<startTime.size(); ++i){
            time.push_back({startTime[i], endTime[i], profit[i]});
        }
        sort(time.begin(), time.end());
        unordered_map<int,int>dp;
        return topDown(time, dp, 0);
    }
    
    int topDown(vector<vector<int>>&time, unordered_map<int,int>&dp, int index){
        if(index == time.size())
            return 0;
        if(dp.count(index))
            return dp[index];
        
        vector<int>search = {time[index][1],0,0};
        int next = lower_bound(time.begin()+index, time.end(),search) - time.begin();
        
        int inclusive = time[index][2] +  topDown(time, dp, next);
        int skip = topDown(time, dp, index + 1);
        return dp[index] = max(inclusive, skip);
    }
};