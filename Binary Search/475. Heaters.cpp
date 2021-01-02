/*
set lowerbound
*/
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        set<int>s(heaters.begin(),heaters.end());
        int res = 0;
        for(auto h: houses){
            auto it = s.lower_bound(h);
            int cur = INT_MAX;
            if(it!=s.end()) cur = *it-h;
            if(it!=s.begin()) cur = min(cur, h - *(--it));
            res = max(res, cur);
        }
        return res;
    }
};


/*
vector lowerbound
*/

class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        sort(heaters.begin(),heaters.end());
        int res = 0;
        for(auto h: houses){
            auto it = lower_bound(heaters.begin(),heaters.end(),h);
            int cur = numeric_limits<int>::max();
            if(it!=heaters.end()) cur = *it-h;
            if(it!=heaters.begin()) cur = min(cur, h - *(--it));
            res = max(res, cur);
        }
        return res;
    }
};



class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        if(heaters.empty() || houses.empty())  return 0;
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        int index = 0;
        int r = 0;
        int n = heaters.size();
        for(int i = 0; i < houses.size(); i++) {
            int house = houses[i];
            if(index == (n - 1) || abs(heaters[index]-house) < abs(heaters[index+1]-house)) {                
                r = max(r, abs(heaters[index]-house));
            } else {                
                i--;
                index++;
            }
        }
        return r;
    }
};



class Solution {
public:
/*
Example:    h = house,  * = heater  M = INT_MAX

        h   h   h   h   h   h   h   h   h    houses
        1   2   3   4   5   6   7   8   9    index
        *           *       *                heaters
                
        0   2   1   0   1   0   -   -   -    (distance to nearest RHS heater)
        0   1   2   0   1   0   1   2   3    (distance to nearest LHS heater)

        0   1   1   0   1   0   1   2   3    (res = minimum of above two)

Result is maximum value in res, which is 3.
*/
    int findRadius(vector<int>& A, vector<int>& H) {
        sort(A.begin(), A.end());
        sort(H.begin(), H.end());
        vector<int> res(A.size(), INT_MAX); 
        
        // For each house, calculate distance to nearest RHS heater
        for (int i = 0, h = 0; i < A.size() && h < H.size(); ) {
            if (A[i] <= H[h]) { res[i] = H[h] - A[i]; i++; }
            else { h++; }
        }
        
        // For each house, calculate distance to nearest LHS heater
        for (int i = A.size()-1, h = H.size()-1; i >= 0 && h >= 0; ) {
            if (A[i] >= H[h]) { res[i] = min(res[i], A[i] - H[h]); i--; }
            else { h--; }
        }
       
        return *max_element(res.begin(), res.end());
    }
};