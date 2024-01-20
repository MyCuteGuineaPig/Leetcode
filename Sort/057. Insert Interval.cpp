"""
057. Insert Interval


Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
Example 2:

Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
"""

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
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        auto it = lower_bound(intervals.begin(),intervals.end(), newInterval,[](const Interval& a, const Interval& t){
            return a.start<t.start;//返回的是第一个不满足条件的位置
        });
        vector<Interval>res;
        if(it!=intervals.begin()){
            if((*(it-1)).end >= newInterval.start) {
                it--;
                newInterval.start = (*it).start;
            }
            copy(intervals.begin(),it, back_inserter(res));
        }
        for(;it!=intervals.end() && newInterval.end >= (*it).start; it++){
            newInterval.end = max(newInterval.end, (*it).end);
        }
        res.push_back(newInterval);
        if(it!=intervals.end())
            copy(it, intervals.end(),back_inserter(res));
        return res;
    }
};


class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        auto it = lower_bound(intervals.begin(), intervals.end(), newInterval, [](const vector<int>& a, const vector<int>&b){
            return a[1] < b[0]; 
        });
        vector<vector<int>>res;
        if (it != intervals.begin()){
            copy(intervals.begin(), it, back_inserter(res));
        }
        while (it != intervals.end() && (*it)[0] <= newInterval[1]){
            newInterval[0] = min(newInterval[0], (*it)[0]);
            newInterval[1] = max(newInterval[1], (*it)[1]);
            ++it;
        }
        res.push_back(newInterval);
        if (it!=intervals.end()){
            copy(it, intervals.end(), back_inserter(res));
        }
        return res;
    }
};


class Solution {
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        int i = 0, n = intervals.size();
        vector<Interval>res;
        while(i<n && intervals[i].end < newInterval.start) res.push_back(intervals[i++]);
        if(i<n) newInterval.start = min(newInterval.start, intervals[i].start);
        while(i<n && intervals[i].start <= newInterval.end) newInterval.end = max(newInterval.end, intervals[i++].end);
        res.push_back(newInterval);
        while(i<n) res.push_back(intervals[i++]);
        return res;
    }
};