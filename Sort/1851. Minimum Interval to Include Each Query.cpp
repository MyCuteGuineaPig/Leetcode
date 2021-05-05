class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        unordered_map<int,int>mp;
        vector<int>Q = queries, res;
        priority_queue<vector<int>>pq;
        
        sort(Q.begin(),Q.end());
        sort(intervals.begin(),intervals.end());
        int i = 0;
        for(auto q: Q){
            while(i < intervals.size() && intervals[i][0] <= q){
                pq.push({intervals[i][0] - intervals[i][1] - 1, intervals[i][1]});
                ++i;
            }
            while(!pq.empty() && pq.top()[1] < q){
                pq.pop();
            }
            mp[q] = pq.size() ? -pq.top()[0] : -1;   
        }
        for(int i = 0; i<queries.size(); ++i)
            res.push_back(mp[queries[i]]);
        return res;
    }
};

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& ints, vector<int>& qs) {
        sort(begin(ints), end(ints));
        set<pair<int, int>> s;
        vector<int> ids(qs.size()), res(qs.size(), -1);
        iota(begin(ids), end(ids), 0);
        sort(begin(ids), end(ids), [&](const auto a, const auto b){ return qs[a] < qs[b]; });
        int j = 0;
        for (auto i : ids) {
            for (; j < ints.size() && ints[j][0] <= qs[i]; ++j)
                s.insert({ints[j][1] - ints[j][0] + 1, ints[j][1]});
            while (!s.empty() && begin(s)->second < qs[i])
                s.erase(begin(s));
            if (!s.empty())
                res[i] = begin(s)->first;
        }
        return res;
    }
};


/*
Sort Intervals by the size. 
then binary search query and current windows size is the result 

跟Python的 Union Find 逻辑是一样的

*/
class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<int> res(queries.size(), -1);
        sort(intervals.begin(), intervals.end(), [](const auto &a, const auto &b) { return a[1] - a[0] < b[1] - b[0]; });
        set<pair<int, int>> s;
        for (int i = 0; i < queries.size(); ++i)
            s.insert({queries[i], i});
        for (auto &i : intervals) {
            auto it = s.lower_bound({i[0], 0});
            while (it != end(s) && it->first <= i[1]) {
                res[it->second] = i[1] - i[0] + 1;
                s.erase(it++); //因为it 已经被set，所以就remove
            }
        }
        return res;
    }
};



class Solution {
    typedef pair<int, int> T;
public:
    vector<int> minInterval(vector<vector<int>>& A, vector<int>& Q) {
        vector<pair<int, int>> QQ; // each element is a pair of query and the corresponding index
        for (int i = 0; i < Q.size(); ++i) QQ.emplace_back(Q[i], i); 
        sort(begin(QQ), end(QQ)); // sort in ascending order of query
        sort(begin(A), end(A)); // sort intervals in ascending order
        int i = 0, N = A.size(); // `i` is a read pointer scanning `A`.
        vector<int> ans(Q.size(), -1);
        map<int, int> m; // map `m` stores the mapping from a interval length to its corresponding count.
        priority_queue<T, vector<T>, greater<>> pq; // min-heap. Each element is a pair of right edge and interval length
        for (auto &[q, index] : QQ) {
            for (; i < N && A[i][0] <= q; ++i) { // extend the window's right edge -- cover all the intervals whose left edge <= q
                int len = A[i][1] - A[i][0] + 1;
                m[len]++;
                pq.emplace(A[i][1], len);
            }
            while (pq.size() && pq.top().first < q) { // shrink the window's left edge -- pop all the intervals whose right edge < q
                auto [right, len] = pq.top();
                if (--m[len] == 0) m.erase(len);
                pq.pop();
            }
            if (m.size()) ans[index] = m.begin()->first; // the map `m` stores the length of all the valid intervals and their corresponding count. We use the smallest length.
        }
        return ans;
    }
};