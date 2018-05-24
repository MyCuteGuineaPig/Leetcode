"""
56. Merge Intervals
Given a collection of intervals, merge all overlapping intervals.

Example 1:

Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
Example 2:

Input: [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considerred overlapping.


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
    vector<Interval> merge(vector<Interval>& intervals) {
        if(intervals.empty()) return {};
        sort(intervals.begin(),intervals.end(),[](const Interval & a, const Interval &b){
            if (a.start == b.start) return a.end<b.end; else return a.start<b.start;
        });
        vector<Interval>res; 
        int s=intervals[0].start, e = intervals[0].end;
        for(int i = 1; i<intervals.size();i++){
            if (e>=intervals[i].start)
                e = max(e, intervals[i].end);
            else {
                res.push_back(Interval(s,e));
                s = intervals[i].start; 
                e = intervals[i].end;
            }
        }
        res.push_back(Interval(s,e));
        return res;
    }
};


vector<Interval> merge(vector<Interval>& ins) {
    if (ins.empty()) return vector<Interval>{};
    vector<Interval> res;
    sort(ins.begin(), ins.end(), [](Interval a, Interval b){return a.start < b.start;});
    res.push_back(ins[0]);
    for (int i = 1; i < ins.size(); i++) {
        if (res.back().end < ins[i].start) res.push_back(ins[i]);
        else
            res.back().end = max(res.back().end, ins[i].end);
    }
    return res;
}


class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        if(intervals.empty()) return {};
        sort(intervals.begin(),intervals.end(),[](const Interval & a, const Interval &b){
             return a.start<b.start;
        });
        vector<Interval>res; 
        res.push_back(intervals[0]);
        for(int i = 1; i<intervals.size();i++){
            if (res.back().end>=intervals[i].start)
                res.back().end = max(res.back().end, intervals[i].end);
            else {
                res.push_back(intervals[i]);
            }
        }
        return res;
    }
};