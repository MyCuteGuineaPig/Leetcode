class Solution {
public:
    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget) {
        int l = 0; 
        deque<int>q; 
        long  res = 0; 
        long cur = 0;
        long n = chargeTimes.size();
        for(int i = 0; i < n; ++i) {
            while(q.size() && chargeTimes[q.back()] <= chargeTimes[i]){
                q.pop_back();
            }
            q.push_back(i);
            cur += runningCosts[i];
            while(q.size() && (long)chargeTimes[q.front()] + (long)(i-l+1)*cur > budget) {
                cur -= runningCosts[l];
                if (l++ == q.front()) {
                    q.pop_front();
                }
            }
            res = max(res, (long)i - l + 1);
        }
        return res;
    }
};


class Solution {
public:
    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget) {
        int l = 0; 
        deque<int>q; 
        long  res = 0; 
        long cur = 0;
        long n = chargeTimes.size();
        for(int i = 0; i < n; ++i) {
            while(q.size() && chargeTimes[q.back()] <= chargeTimes[i]){
                q.pop_back();
            }
            q.push_back(i);
            cur += runningCosts[i];
            if((long)chargeTimes[q.front()] + (long)(i-l+1)*cur > budget) {
                cur -= runningCosts[l];
                if (l++ == q.front()) {
                    q.pop_front();
                }
            }
        }
        return n-l;
    }
};