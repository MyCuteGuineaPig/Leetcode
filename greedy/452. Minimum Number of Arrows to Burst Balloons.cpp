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



class Solution {
public:
    int findMinArrowShots(vector<pair<int, int>>& points) {
        if(points.size()==0) return 0;
        sort(points.begin(),points.end(),[](const pair<int, int> &a, const pair<int,int> &b ){
            if(a.first != b.first) return a.first<b.first; return a.second < b.second;
        });
        int count = 1;
        int start = points[0].first, end = points[0].second;
        for(int i = 1; i<points.size();i++){
            if(points[i].first > end){
                count++;
                start = points[i].first;
                end = points[i].second;
            }else{
                start = max(start,points[i].first);
                end = min(end,points[i].second);
            }

        }
        return count;
    }
};

/*

First, we sort balloons by increasing points.end (if ends are the same, then by increasing of points.start). 
Every time arrow shot points.end, say, points[i].second. 
If next balloon.start <= points[i].second, it is also shot, thus we continue.

*/
    int findMinArrowShots(vector<pair<int, int>>& points) {
        int count = 0, arrow = INT_MIN;
        sort(points.begin(), points.end(), mysort);
        for(int i = 0; i<points.size(); i++){
            if(arrow!=INT_MIN && points[i].first<=arrow){continue;} //former arrow shot points[i] 
            arrow = points[i].second; // new arrow shot the end of points[i]
            count++;
        }
        return count;
    }
    static bool mysort(pair<int, int>& a, pair<int, int>& b){
        return a.second==b.second?a.first<b.first:a.second<b.second;
    }