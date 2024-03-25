class Solution {
public:
    int largestVariance(string s) {
        int res = 0;
        vector<int>counter(26);
        for(auto& i: s)
            counter[i-'a']++;
        
        for(int i = 0; i < 26; ++i){
            for(int j = 0; j < 26; ++j){
                if (i ==j || counter[i] == 0 || counter[j] == 0) continue;

                char a = 'a' + i;
                char b=  'a' + j;

                int major_cnt = 0 , minor_cnt = 0, rest_cnt = counter[j];
                for(char ch: s){
                    if (ch == a){
                        ++major_cnt;
                    } 
                    if (ch == b){
                        ++minor_cnt;
                        --rest_cnt;
                    }
                    //cout<<" a="<<a << " b="<<b<<" major_cnt" << major_cnt << " minor_cnt "<<minor_cnt  << endl;
                    if (minor_cnt > 0) {
                        res = max(res, major_cnt - minor_cnt);
                    }
                    if (major_cnt < minor_cnt){
                        if (rest_cnt > 0){
                            major_cnt = 0;
                            minor_cnt = 0;
                        } 
                        //if rest_cnt === 0, 不动，维持现状
                        //比如paa, 当经过第一个p, minor_cnt = 1, res_cnt = 0, majr_cnt = 0
                    }
                }
            }
        }
        return res;
    }
};



class Solution {
public:
    int largestVariance(string s) {
        int res = 0;
        unordered_set<char> unique(begin(s), end(s));
        for (char a : unique)
            for (char b : unique) {
                int var = 0, has_b = 0, first_b = 0;
                for (auto ch : s) {
                    var += ch == a;
                    if (ch == b) {
                        has_b = true;
                        if (first_b && var >= 0)
                            first_b = false;
                        else if (--var < 0) {
                            first_b = true;
                            var = -1;
                        }
                    }
                    res = max(res, has_b ? var : 0);
                }
            }
        return res;
    }
};