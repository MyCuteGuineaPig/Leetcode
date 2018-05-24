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
            return a.start<t.start;
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