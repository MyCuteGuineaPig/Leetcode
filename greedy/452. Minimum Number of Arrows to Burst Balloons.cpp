/*

There are a number of spherical balloons spread in two-dimensional space. 
For each balloon, provided input is the start and end coordinates of the horizontal diameter. 
Since it's horizontal, y-coordinates don't matter and hence the x-coordinates of start and end of the diameter suffice.
 Start is always smaller than end. There will be at most 104 balloons.

An arrow can be shot up exactly vertically from different points along the x-axis. 
A balloon with xstart and xend bursts by an arrow shot at x if xstart ≤ x ≤ xend. 
There is no limit to the number of arrows that can be shot. An arrow once shot keeps travelling up infinitely.
The problem is to find the minimum number of arrows that must be shot to burst all balloons.

Example:

Input:
[[10,16], [2,8], [1,6], [7,12]]

Output:
2

Explanation:
One way is to shoot one arrow for example at x = 6 (bursting the balloons [2,8] and [1,6]) and another arrow at x = 11
 (bursting the other two balloons).

*/



/*
Solution 1:
burst 点是保证 burst触发的点在interval 区间内 start<= burst point <= end
比如 [[10,16], [2,8], [1,6], [7,12]]
即使 [1,6], [2,8], [7,12] 可以构成连续的interval，但是因为[1,6], [7,12] 不重合，不能满足start<=burst point <= end

思路：先按照start, 排序，
    当burst 区间开始时(p.first > end)，start点就固定了, 因为所有点按照start 排序, 所有后面点的start都比start 大，
    但是后面点的end 顺序不定，我们要缩小它的范围， 
    然后开始缩小burst point end 范围，如果下面的点end < curend, 更新curend, 直到i.start > curend



*/
class Solution {
public:
    int findMinArrowShots(vector<pair<int, int>>& points) {
        if(points.empty()) return 0;
        sort(points.begin(), points.end(), [](const pair<int, int>& a,const pair<int, int>& b){return a.first<b.first;});
        long end = numeric_limits<long>::min(); int count = 0;
        for(auto p: points){
            if(p.first>end){
                count ++;
                end = p.second;
            } else if (p.second < end) end = p.second;
        }
        return count;
    }
};

/*
Solution2: 是solution 1 的reverse operation
burst 点是保证 burst触发的点在interval 区间内 start<= burst point <= end
按照end点的位置由大到小排序，

    当burst 区间开始时(p.second < start)，end点就固定了, 因为所有点按照end 排序, 所有后面点的end都比start 小，
    但是后面点的start 顺序不定，我们要缩小它的范围, 逐渐让start 靠近end， 就取当前start 和i.start最大值

*/
class Solution {
public:
    int findMinArrowShots(vector<pair<int, int>>& points) {
        if(points.empty()) return 0;
        sort(points.begin(), points.end(), [](const pair<int, int>& a,const pair<int, int>& b){return a.second>b.second;}); //顺序按照end的由大到小排序
        long start = numeric_limits<long>::max(); int count = 0;
        for(auto p: points){
            if(p.second<start){
                count ++;
                start = p.first;
            } else if (p.first > start) start = p.first;
        }
        return count;
    }
};

/*
Solution 3: 

burst 点是保证 burst触发的点在interval 区间内 start<= burst point <= end
按照end点的位置由大到小排序，

    当burst 区间开始时(p.first < end)，end点就固定了, 因为所有点按照end 排序, 所有后面点的ebd都比end大，
    但是后面点的start 顺序不定，我们可以忽略start 的顺序，

    比如 [1,4],  [2,8], [5,9]
    end  = 4， 可以爆 [1,4], [2,8], 之后end = 9, 爆后面的点
    但是有比如 [1,4],  [5,9], [2,12], 
    end = 4, 只爆了[1,4] 实际上可以爆[2,12]点，但是[2,12]跨度大, [5,9], end = 9, 根据sort 9 < 12, 点[2,12]也可以在[5,9]爆

*/

class Solution {
public:
    int findMinArrowShots(vector<pair<int, int>>& points) {
        if(points.empty()) return 0;
        sort(points.begin(), points.end(), [](const pair<int, int>& a,const pair<int, int>& b){return a.second<b.second;}); //顺序按照end的由大到小排序
        long end = numeric_limits<long>::min(); int count = 0;
        for(auto p: points){
            if(p.first>end){
                count ++;
                end = p.second;
            }
        }
        return count;
    }
};


class Solution {
public:
    int findMinArrowShots(vector<pair<int, int>>& points) {
        if(points.size()==0) return 0;
        sort(points.begin(),points.end(),[](const pair<int, int> &a, const pair<int,int> &b ){
            if(a.first != b.first) return a.first<b.first; return a.second < b.second;
        });
        int count = 1;
        int end = points[0].second;
        for(int i = 1; i<points.size();i++){
            if(points[i].first > end){
                count++;
                end = points[i].second;
            }else{
                end = min(end,points[i].second);
            }

        }
        return count;
    }
};


