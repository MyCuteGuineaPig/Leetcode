
/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
        set<pair<int,int>, comp>s;
        for(int i = 0; i<intervals.size(); i++)
            s.insert({intervals[i].start, i});
        vector<int>res(intervals.size(),-1);
        for(int i = 0; i<intervals.size(); i++){
            auto it = s.lower_bound({intervals[i].end,i});
            if(it!=s.end()) res[i] = (*it).second;
        }
        return res;
    }
    struct comp{
        bool operator()(const pair<int,int> & lhs, const pair<int,int>& rhs) const{return lhs.first<rhs.first;}
    };
};

class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
        set<pair<int,int>>s;
        for(int i = 0; i<intervals.size(); i++){
            s.insert({intervals[i].start, i});
        }
        vector<int>res(intervals.size(),-1);
        for(int i = 0; i<intervals.size(); i++){
            auto it = s.lower_bound({intervals[i].end,INT_MIN}); //得用INT_min, 因为假如intervals[i] 一样，会比较second element
            if(it!=s.end()) res[i] = (*it).second;
        }
        return res;
    }
    
};


/*
用map的 lowerbound
*/
class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
        map<int, int> hash;
        vector<int> res;
        int n = intervals.size();
        for (int i = 0; i < n; ++i)
            hash[intervals[i].start] = i;
        for (auto in : intervals) {
            auto itr = hash.lower_bound(in.end);
            if (itr == hash.end()) res.push_back(-1);
            else res.push_back(itr->second);
        }
        return res;
    }
};


/*
用vector
*/
class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
        int start = INT_MAX;
        int end = INT_MIN;
        vector<int> res;
        for (int i = 0; i < intervals.size(); i++) {
            if (intervals[i].start < start) {
                start = intervals[i].start;
            }
            if (intervals[i].start > end) {
                end = intervals[i].start;
            }
        }
        vector<int> map(end - start + 1, -1);
        for (int i = 0; i < intervals.size(); i++) {
            map[intervals[i].start - start] = i;
        }
        for (int i = 0; i < intervals.size(); i++) {
            int j = intervals[i].end - start;
            while (j < map.size() && map[j] == -1) {
                j++;
            }
            if (j < map.size()) {
                res.push_back(map[j]);
            } else {
                res.push_back(-1);
            }
        }
        return res;
    }    
};


class Solution {
public:
    vector<int> findRightInterval(vector<Interval>& intervals) {
        vector<pair<int, int>> v;
        int n = intervals.size();
        for(int i = 0; i < n; ++i){
            v.push_back({intervals[i].start, i});
        }
        
        sort(v.begin(), v.end());
        
        vector<int> ans;
        for(int i = 0; i < n; ++i){
            pair<int,int> t {intervals[i].end, 0};
            auto it = lower_bound(v.begin(), v.end(), t, [](const pair<int,int>& lhs, const pair<int,int>& rhs){
                return lhs.first < rhs.first; 
            });
            if(it != v.end()){
                ans.push_back(it->second);
            }else{
                ans.push_back(-1);
            }
        }
        
        return ans;
    }
};