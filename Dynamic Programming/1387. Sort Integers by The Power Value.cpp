class Solution {
public:
    int getKth(int lo, int hi, int k) {
        vector<pair<int,int>>mp;
        for(int i = lo; i<=hi; ++i)
            mp.push_back({power_value(i), i});
        nth_element(mp.begin(), mp.begin()+k-1, mp.end());
        return (mp.begin()+k-1)->second;
    }
    
    int power_value(int x){
        int y = x, cnt = 0;
        while(x != 1 && dp.find(x) == dp.end()){
            ++cnt;
            if (x & 1) 
                x = 3 * x + 1;
            else 
                x >>= 1;
        }
        return Solution::dp[y] = cnt + Solution::dp[x];
    }
    static unordered_map<int,int>dp;
};

unordered_map<int,int>Solution::dp;