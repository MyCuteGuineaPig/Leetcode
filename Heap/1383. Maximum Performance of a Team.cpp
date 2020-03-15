//2020
class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        multiset<vector<int>>pq;
        for(int i = 0; i<n; ++i)
            pq.insert({-efficiency[i], speed[i]});
        long long cur = 0, res = 0, mod = pow(10,9)+7;
        multiset<int>topSpeed;
        for(auto it: pq){
            cur += it[1]; 
            topSpeed.insert(it[1]);
            if(topSpeed.size() > k){
                cur -= *topSpeed.begin();
                topSpeed.erase(topSpeed.begin());
            }
            res = max(cur*(-it[0]), res);
        }
        return res % (mod);
    }
};




//2020
class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        priority_queue<vector<int>>pq;
        for(int i = 0; i<n; ++i)
            pq.push({efficiency[i], speed[i]});
			
        long long cur = 0, res = 0, mod = pow(10,9)+7;
        priority_queue<int>topSpeed;
        for(int i = 0; i<n; ++i){
            auto top = pq.top();
            cur += top[1]; pq.pop();
            topSpeed.push(-top[1]);
			
            if(topSpeed.size() > k){
                cur += topSpeed.top();
                topSpeed.pop();
            }
            res = max(cur*top[0], res);
        }
        return res % (mod);
    }
};


class Solution{
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        vector<pair<int, int>> ess;
        for (int i = 0; i < n; ++i)
            ess.push_back({efficiency[i], speed[i]});
        sort(begin(ess), end(ess));

        long sumS = 0, res = 0;
        priority_queue <int, vector<int>, greater<int> > pq;
        for (int i = n - 1; i >= 0; --i) {
            pq.push(ess[i].second);
            sumS += ess[i].second;
            if (pq.size() > k) {
                sumS -= pq.top();
                pq.pop();
            }
            res = max(res, sumS * ess[i].first);
        }
        return res % (int)(1e9+7);
    }
};