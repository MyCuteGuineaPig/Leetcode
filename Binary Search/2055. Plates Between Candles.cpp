class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        vector<int>candles;
        for(int i = 0; i<s.size(); ++i){
            if(s[i] == '|') candles.push_back(i);
        }
        vector<int>res;
        for(auto& q: queries){
            int l = lower_bound(candles.begin(), candles.end(), q[0])- candles.begin();
            int r = upper_bound(candles.begin(), candles.end(), q[1])- candles.begin()-1;
            //cout<<" l "<<l<<" r "<<r<<endl;
            if (l >= r){
                res.push_back(0);
            } else {
                res.push_back((candles[r]-candles[l])-1 - (r-l-1));
            }
        }
        return res;
    }
};