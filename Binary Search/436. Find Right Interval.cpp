/*
436. Find Right Interval

Given a set of intervals, for each of the interval i, check if there exists an interval j whose start point is bigger than or equal to the end point of the interval i, 
which can be called that j is on the "right" of i.

For any interval i, you need to store the minimum interval j's index, 
which means that the interval j has the minimum start point to build the "right" relationship for interval i. 
If the interval j doesn't exist, store -1 for the interval i. Finally, you need output the stored value of each interval as an array.

Note:
You may assume the interval's end point is always bigger than its start point.
You may assume none of these intervals have the same start point.
Example 1:
Input: [ [1,2] ]

Output: [-1]

Explanation: There is only one interval in the collection, so it outputs -1.
Example 2:
Input: [ [3,4], [2,3], [1,2] ]

Output: [-1, 0, 1]

Explanation: There is no satisfied "right" interval for [3,4].
For [2,3], the interval [3,4] has minimum-"right" start point;
For [1,2], the interval [2,3] has minimum-"right" start point.
Example 3:
Input: [ [1,4], [2,3], [3,4] ]

Output: [-1, 2, -1]

Explanation: There is no satisfied "right" interval for [1,4] and [3,4].
For [2,3], the interval [3,4] has minimum-"right" start point.

*/



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