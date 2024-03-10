class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        unordered_map<int, int>mp;
        for(auto t: time){
            mp[t%60]++;
        }
        long cnt = 0;
        for(auto &it: mp){
            if (it.first > 30){
                continue;
            }
            if (it.first == 0 || it.first == 30){
                cnt += (long)it.second * (it.second - 1) / 2;
            }
            else if (mp.count(60 - it.first)){
                cnt += (long)it.second * mp[60 - it.first];
            }
        }
        return cnt;
    }
};

class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        vector<int> c(60);
        int res = 0;
        for (int t : time) {
            res += c[(540 - t) % 60]; //or c[(600 - t) % 60]
            c[t % 60] += 1;
        }
        return res;
    }
};