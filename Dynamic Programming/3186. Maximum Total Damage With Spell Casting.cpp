class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        map<int, long long> mp; 
        for(auto p: power)
            mp[p] += p;
        long long  prev = 0;
        long long res = 0;
        for(auto it = mp.begin(), it2 = mp.begin(); it != mp.end(); ++it){
            while(it2->first < it->first - 2 ) {
                prev = max(prev, mp[(it2++)->first]);
            }
            mp[it->first] += prev;
            res = max(res,  mp[it->first]);
        }
        return res;
    }
};


//TLE
class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        unordered_map<int, int> mp; 
        for(auto p: power)
            mp[p] += p;
        int min_v = *min_element(power.begin(), power.end());
        int max_v = *max_element(power.begin(), power.end());
        long long res = 0, res_1 = 0, res_2 = 0;
        for(int i = min_v; i <= max_v; ++i){
            long long tmp = 0;
            tmp = mp[i];
            
            if (i >= min_v + 1) tmp = max(tmp , res);
            if (i >= min_v + 2) tmp = max(tmp, res_1);
            if (i > min_v + 2) {
                tmp = max(res_2 + mp[i], tmp);
            }
            res_2 = res_1;
            res_1 = res;
            res = tmp;
            //cout<<i<<" res[i - min_v] "<<res[i - min_v]<<endl;
        }
        return res;
    }
};