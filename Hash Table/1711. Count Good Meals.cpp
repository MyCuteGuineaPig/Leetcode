class Solution {
public:
    int countPairs(vector<int>& deliciousness) {
        unordered_map<int, int>num;
        long res = 0;
        long mod = 1e9 + 7;
        for(auto i: deliciousness){
            for(int j = 0; j < 31; ++j){
                int tmp = (1<<j) - i;
                if(num.count(tmp)){
                    res = (res + num[tmp]) % mod;
                }
            }
            num[i]++;
        }
        return res;
    }
};