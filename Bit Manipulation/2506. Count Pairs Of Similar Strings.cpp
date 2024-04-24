class Solution {
public:
    int similarPairs(vector<string>& words) {
        unordered_map<int,int>m;
        int res = 0; 
        for(auto & w: words){
            int bits = 0;
            for(auto& ch: w){
                bits |= (1<< (ch - 'a'));
            }
            res += m[bits]++;
        }
        return res;
    }
};