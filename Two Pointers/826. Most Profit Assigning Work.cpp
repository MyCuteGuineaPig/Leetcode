/*
826. Most Profit Assigning Work

We have jobs: difficulty[i] is the difficulty of the ith job, and profit[i] is the profit of the ith job. 

Now we have some workers. worker[i] is the ability of the ith worker, 
which means that this worker can only complete a job with difficulty at most worker[i]. 

Every worker can be assigned at most one job, but one job can be completed multiple times.

For example, if 3 people attempt the same job that pays $1, then the total profit will be $3.  
If a worker cannot complete any job, his profit is $0.

What is the most profit we can make?

Example 1:

Input: difficulty = [2,4,6,8,10], profit = [10,20,30,40,50], worker = [4,5,6,7]
Output: 100 
Explanation: Workers are assigned jobs of difficulty [4,4,6,6] and they get profit of [20,20,30,30] seperately.
Notes:

1 <= difficulty.length = profit.length <= 10000
1 <= worker.length <= 10000
difficulty[i], profit[i], worker[i]  are in range [1, 10^5]


*/


class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        vector<pair<int,int>>jobs;
        for(int i = 0; i<profit.size();i++)
            jobs.push_back({difficulty[i],profit[i]});
        sort(jobs.begin(), jobs.end());
        sort(worker.begin(),worker.end());
        int res = 0;
        for(int i = 0, j=0, profit_till_i = 0; i<worker.size();i++){ //profit就是到i-1时最高的收益
            while(j<jobs.size() && jobs[j].first<=worker[i]) profit_till_i = max(profit_till_i, jobs[j++].second);
            res += profit_till_i;
        }
        return res;
    }
};


/*
This solution sorts levels and assigns the maximum profit among all jobs with equal or lower level:

1. Load levels and profits into a sorted map.
2. Update the map so that each level has the maximum possible profit. Practically, 
   if the previous level has higher profit, we assign that profit to the current level.
3. For each worker, search the map to get the maximum profit for the worker's level.
The complexity is O((n + m) log n), where n and m is the number of jobs and workers respectfully.
*/
class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        map<int,int>m;
        for(int i = 0; i<profit.size();i++) m[difficulty[i]] = max(m[difficulty[i]],profit[i]);
        for(auto it = next(m.begin()); it!=m.end(); it++) it->second = max(it->second, prev(it)->second);
        return accumulate(worker.begin(),worker.end(), 0, [&](int s, int p){return s+ prev(m.upper_bound(p))->second;});
    }
};
/*  As a bonus, below is the solution that uses bucket sort. It requires, 
however, additional memory but the runtime complexity is O(N + m), 
where N is the number of levels (100,000 in our case). 
The second solution is only slightly faster in OJ (100 vs. 110 ms), 
probably because n is signifficantly smaller than N in the test cases.
*/

class Solution {
public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        int m[10001] = {0};
        for(int i = 0; i<profit.size();i++) m[difficulty[i]] = max(m[difficulty[i]],profit[i]);
        for(int it = 1; it<10001; it++) m[it] = max(m[it],m[it-1]);
        return accumulate(worker.begin(),worker.end(), 0, [&](int s, int p){return s+ m[p];});
    }
};
/*
I also checked the sort and two-pointer solution by @lee215. 
That solution requires two sorts, that's why my preference was to sort once and fix profits in the linear time.
 Anyway, I adopted the two-pointer solution to use the bucket sort.
  Note that I store the number of workers with a given level in the second array.

*/
int maxProfitAssignment(vector<int>& lv, vector<int>& profit, vector<int>& worker) {
  int m[100001] = {}, w[100001] = {}, p = 0, max_p = 0;
  for (auto i = 0; i < lv.size(); ++w[worker[i++]]) m[lv[i]] = max(m[lv[i]], profit[i]);
  return accumulate(begin(w), end(w), 0, [&](int s, int w) { max_p = max(max_p, m[p++]); return s + max_p * w; });
}