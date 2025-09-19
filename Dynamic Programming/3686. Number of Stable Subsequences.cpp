class Solution {
public:
    int countStableSubsequences(vector<int>& nums) {
        long long e1 = 0, e2 = 0, o1 = 0, o2=0;
        long long mod = 1e9 + 7;
        for(auto & num: nums){
            if (num & 1) {
                long long no1 = (o1 + (e1 + e2 + 1)) % mod;
                //o1 -> no1, not append new number just carry
                long long no2 = (o1 + o2) % mod;
                //o1 -> no2, add num to the end
                //o2 -> no2, not add num, just carry
                o1 = no1, o2 = no2;
            } else {
                long long ne1 = (e1 + (o1 + o2 + 1)) % mod;
                long long ne2 = (e1 + e2) % mod;
                e1 = ne1, e2 = ne2;
            }
            //cout << num <<" e1 "<<e1 << " e2 "<<e2 <<" o1 "<<o1 << " o2 "<<o2<<endl;
        }
        return (int)((e1 + e2 + o1 + o2) % mod);
    }
};

class Solution {
public:
    int countStableSubsequences(vector<int>& nums) {
        long long one[2] = {}, two[2] = {}, mod = 1000000007;
        for (int n : nums) {
            auto p = n % 2;
            two[p] = (two[p] + one[p]) % mod;
            one[p] = (one[p] + 1 + one[!p] + two[!p]) % mod;
        }
        return (one[0] + one[1] + two[0] + two[1]) % mod;
    }
};