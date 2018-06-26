/*
447. Number of Boomerangs


Given n points in the plane that are all pairwise distinct, a "boomerang" is a tuple of points (i, j, k) 
such that the distance between i and j equals the distance between i and k (the order of the tuple matters).

Find the number of boomerangs. You may assume that n will be at most 500 and coordinates of points are all in the range [-10000, 10000] (inclusive).

Example:
Input:
[[0,0],[1,0],[2,0]]

Output:
2

Explanation:
The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]]
*/


class Solution {
public:
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        int res = 0;
        for(int i = 0; i<points.size();i++){
            unordered_map<int,int>m;
            for(int j = 0; j<points.size();j++){
                if(j!=i) m[calcu(points[i], points[j])]++;
            }
            for(auto it: m)
                res += it.second*(it.second-1);
        }
        return res;
    }
    
    int calcu(pair<int,int>&a, pair<int,int>&b){
        return (a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second);
    }
};


class Solution {
public:
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        int booms = 0;
        for (auto &p : points) {
            unordered_map<double, int> ctr(points.size());
            for (auto &q : points)
                booms += 2 * ctr[hypot(p.first - q.first, p.second - q.second)]++; //2*prev 是，新的和原来每个组 都可以成为2个新的
        }
        return booms;
    }
};