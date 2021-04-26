/*

step 1: cur point = min (cur point, next point + distance )

step 2: cur point = min (cur point, prev point + distance )

step 3: calculate the max height in the middle between cur point and prev point 

actual_dis = the distance between two point when two point at the same height

e.g.  r[i-1][0] = 5, r[i-1][1] = 10
      r[i][0]   = 11, r[i][1] =  9

    distance = 6
    actual_dist = 6 - 1 = 5;  
    10 / 2 = 2, 表示 从5 到 11 最高可以上升两个 高度 
*/

class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& r) {
        r.push_back({1,0}); r.push_back({n,n-1});
        sort(r.begin(), r.end());
        
        int res = 0;
        for(int i = r.size()-2; i>=0; --i){
            r[i][1] = min(r[i][1], r[i+1][0] - r[i][0] + r[i+1][1]);
        }
        
        for(int i = 1; i<r.size(); ++i){
            r[i][1] = min(r[i][1], r[i][0] - r[i-1][0] + r[i-1][1]);
             
            int distance = r[i][0] - r[i-1][0];
            int actual_dist = distance - abs(r[i][1] - r[i-1][1]);
            res = max(res , max(r[i][1],r[i-1][1]) + actual_dist/2);
        }
        return res;
    }
};


class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& arr) {
        arr.push_back({1, 0});
        arr.push_back({n, n - 1});
        sort(arr.begin(), arr.end());
        int m = arr.size();
        
        for (int i = 1; i < m; ++i)
            arr[i][1] = min(arr[i][1], arr[i-1][1] + arr[i][0] - arr[i-1][0]);
        for (int i = m - 2; i >= 0; --i)
            arr[i][1] = min(arr[i][1], arr[i+1][1] + arr[i+1][0] - arr[i][0]);
        
        int ans = 0, l, h1, r, h2;
        for (int i = 1; i < m; ++i) {
            l = arr[i-1][0], r = arr[i][0], h1 = arr[i-1][1], h2 = arr[i][1];
            ans = max(ans, max(h1, h2) + (r - l - abs(h1 - h2)) / 2);
        }
        return ans;
    }
};