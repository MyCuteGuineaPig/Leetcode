


/*
O(KLogK)  K number of employee
*/
class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& a) {
        vector<Interval> res;
        map<int, int> timeline;
        for (auto &v : a) {
            for (auto &i : v) {
                timeline[i.start]++;
                timeline[i.end]--;
            }
        }
        int overlap = 0;
        for (auto it1 = timeline.begin(); it1 != timeline.end(); it1++) {
            overlap += it1->second;
            auto it2 = next(it1, 1);
            if (it2 == timeline.end()) break;
            if (!overlap) res.emplace_back(it1->first, it2->first);
        }
        return res;
    }
};

/*
O(NLogK)  K number of employee, N number of schedule
*/
class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        priority_queue<vector<int>,vector<vector<int>>, greater<vector<int>>>pq;
        
        int anchor = numeric_limits<int>::max();
        for(int i = 0; i<schedule.size(); ++i){
            pq.push({schedule[i][0].start, schedule[i][0].end, i, 0});
            anchor = min(anchor, schedule[i][0].start);
        }
        
        vector<Interval>res;
        while(!pq.empty()){
            auto top = pq.top(); pq.pop();
            if(top[0] > anchor)
                res.emplace_back(anchor,top[0]);
            anchor = max(anchor, top[1]);
            if (top[3]+1 < schedule[top[2]].size()){
                 ++top[3];
                 pq.push({schedule[top[2]][top[3]].start,schedule[top[2]][top[3]].end, top[2], top[3] });
            }
        }
        
        return res;
    }
};



/*
O(KLogK)  K number of employee
*/

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& a) {
        vector<Interval> res;
        map<int, int> timeline;
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < a[i].size(); j++) {
                timeline[a[i][j].start]++;
                timeline[a[i][j].end]--;
            }
        }
        int workers = 0;
        for (pair<int, int> p : timeline) {
            workers += p.second;
            if (!workers) res.push_back(Interval(p.first, 0));
            if (workers && !res.empty() && res.back().end == 0) res.back().end = p.first;
        }
        if (!res.empty()) res.pop_back();
        return res;
    }
};

