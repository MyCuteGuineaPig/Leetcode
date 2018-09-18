/*
435. Non-overlapping Intervals
https://leetcode.com/problems/non-overlapping-intervals/description/

Given a collection of intervals, find the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Note:
You may assume the interval's end point is always bigger than its start point.
Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap each other.
Example 1:
Input: [ [1,2], [2,3], [3,4], [1,3] ]

Output: 1

Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.
Example 2:
Input: [ [1,2], [1,2], [1,2] ]

Output: 2

Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.
Example 3:
Input: [ [1,2], [2,3] ]

Output: 0

Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

*/



/*

题目问最少删除几个构成non-overlapping 的interval，实际上问最多有几个interval可以构成non-overlapping interval

根据end 来sort，不用关心起点，
比如 [1,4],[2,4],[3,4] or[3,4], [1,4],[2,4] : end 都是4，起点都小于4，所以删除都会删除2个

用end 来sort，因为：
1. 小的start 可能end 很远，可能与很多interval 覆盖，比如[ [1,5], [2,3], [3,4], [4，5]] 需要一边走一边调整end
   而根据end 排序，遇到i.start >= end, 我们知道下一个最小的end 一定是i.start
2. 不怕碰到跨度大的interval, 比如[1,2],[3,20], [4,21]，碰到[3,20]时候，即使它跨度大，
   20一定是最近上一个end的end点，如果有更接近的肯定会先出现, 比如[1,2],[3,10],[3,20]，

当i.start < end 肯定是要删除的，因为两个interval覆盖了

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
    int eraseOverlapIntervals(vector<Interval>& intervals) {
        if(intervals.size()==0) return 0;
        sort(intervals.begin(),intervals.end(),[](const Interval& a,const Interval& b){ return a.end < b.end;  }); 
        int end = intervals[0].end;
        int count = 1;
        for(int i = 1; i<intervals.size();i++){
            if(intervals[i].start >= end){ 
                count++;
                end = intervals[i].end;
            }
        }
        return intervals.size()-count;
    }
};


class Solution {
public:
    int eraseOverlapIntervals(vector<Interval>& intervals) {
        if(intervals.size()==0) return 0;
        sort(intervals.begin(),intervals.end(),[](const Interval& a,const Interval& b){ return a.end < b.end;  }); 
        int end = numeric_limits<int>::min();
        int erase = 0;
        for(auto i: intervals){
            if(i.start >= end)
                end = i.end;
            else erase ++;
        }
        return erase;
    }
};

/*
也可以sort by start
注意当有intervla 重合时，把end 变成最小的end = min(end, i.end)
因为   |----------------------------------------| 当前的interval，然后可能其中包含了小的interval
        |-----|  |--------| | ------- |, 如果不变小end，可能变成删除了更多小的interval，实际上删除一个大的interval即可

*/

class Solution {
public:
    int eraseOverlapIntervals(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), [](Interval& i1, Interval& i2){ return i1.start < i2.start; });
        int res = 0, e = INT_MIN;
        for (auto& itv : intervals) {
            if (itv.start < e) {
                res++; //res + 1, 删除可能是现在这个，也可能是上个大的跨度的interval，谁的end小，删除谁的
                if (itv.end < e) e = itv.end; 
                /*
                当前最小的end，因为大的end，可能会错过几个interval，
                比如[[1,100],[11,22],[1,11],[2,12]], end = 100, 删除3个，实际上当 end = 100, i = [1,11]时候,把end = 11，接下来再删除[2,12]即可

                */
            } else e = itv.end;
        }
        return res;
    }
};


/*

      
#1) sort by end:  after sorting we know: s1<e1<e2   and s2<e2
#(in order to make it be easier, we do not consider about "="). 
#Then s2 has three possible positions. I am giving those three possibilities by "@". :     @s1@e1@e2 
#Then we have 3 cases.
       #case 1: s2<s1<e1  @<e2 (replace the first "@"by s2 and remove the rest "@")   
                         #s1****e1
         #s2*****************************e2


        #case 2:s1<s2<e1 <e2 
         #s1*****************e1
                      #s2*******************e2
        

       #case 3:s1<e1< s2 <e2 
        #s1************e1
                                     #s2**************e2
       
#2) sort by start(similar as sort by end):   s1@s2@e2@
        #case1:    s1 <e1 <s2< e2
         #s1******e1
                                     #s2************e2


        #case2:    s1<s2<e1<e2
         #s1***************e1
                     #s2**********************e2


        #case3:s1<s2<e2<e1
          #s1************************************e1
                          #s2********e2


*/
