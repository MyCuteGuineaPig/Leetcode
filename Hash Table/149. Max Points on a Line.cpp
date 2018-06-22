/*
149. Max Points on a Line

Example 1:

Input: [[1,1],[2,2],[3,3]]
Output: 3
Explanation:
^
|
|        o
|     o
|  o  
+------------->
0  1  2  3  4
Example 2:

Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
Explanation:
^
|
|  o
|     o        o
|        o
|  o        o
+------------------->
0  1  2  3  4  5  6
*/



/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */

//精确度要用long double 否则会报错 比如[[0,0],[94911151,94911150],[94911152,94911151]]
class Solution {
public:
    int maxPoints(vector<Point>& points) {
        int res = 0;
        for(int i = 0; i<points.size();i++){
            unordered_map<long double	,int>map;
            int same = 1;
            for(int j = i+1; j<points.size();j++){
                if(points[i].y == points[j].y && points[i].x ==  points[j].x) same++;
                else if(points[i].x ==  points[j].x) map[numeric_limits<double>::max()]++;
                else{
                    long double	 slope =  static_cast<long double>(points[i].y - points[j].y) * 1.0 /(points[i].x - points[j].x);
                    map[slope]++;
                }
            }
            int localmax = same;
            for(auto it: map)
                localmax = max(localmax, it.second+same);      
            res = max(localmax, res);
        }
        return res;
    }
};



class Solution {
public:
    int maxPoints(vector<Point>& points) {
        int N = points.size();
        if (N < 3) return N;
        // Double max is slope for vertical line.
        const double DOUBLE_MAX = std::numeric_limits<double>::max();
        // Scalar is to avoid float point error.
        const double SCALAR = 1e9;
        int ret = 0;
        // For each seed point, loop through other points.
        for (int i = 0; i < N; ++i) {
            unordered_map<double, int> num_per_slope;
            // Max points in a line for current seed point, duplicated points are count seperately.
            int cur_max = 1, dup = 0;
            for (int j = i + 1; j < N; ++j) {
                double dx = static_cast<double>(points[j].x - points[i].x);
                double dy = static_cast<double>(points[j].y - points[i].y) * SCALAR;
                if (dx == 0.0 && dy == 0.0) {
                    ++dup;
                    continue;
                }
                double slope = (dx == 0.0) ? DOUBLE_MAX : (dy / dx);
                auto pair = num_per_slope.insert({slope, 2});
                if (!pair.second) ++pair.first->second;
                cur_max = max(cur_max, pair.first->second);
            }
            ret = max(ret, cur_max + dup);
        }
        return ret;
    }
};