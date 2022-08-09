class Solution {
public:
    int longestIdealString(string s, int k) {
        vector<int>cnt(26,0); 
        int maxlen = 0;
        for(int i = 0; i<s.size(); ++i) {
            int cur = s[i] - 'a';
            int curmax = 0;
            for(int j = max(cur - k, 0); j <= min(cur+k,25); ++j){
                curmax = max(curmax, cnt[j]+1);
            }
            cnt[cur] = curmax;
        }
        return *max_element(cnt.begin(), cnt.end());
    }
};


class Solution {
public:
    int longestIdealString(string s, int k) {
        int dp[150] = {}, res = 0;
        for (auto& i : s) {
            for (int j = i - k; j <= i + k; ++j)
                dp[i] = max(dp[i], dp[j]);
            res = max(res, ++dp[i]);
        }
        return res;
    }
};


class Solution {
public:
    
    
    int longestIdealString(string s, int k) {
        int dp[26] = {};
        return k == 26 ? s.size() : accumulate(begin(s), end(s), 0, [&](int s, char ch){
            return max(s, dp[ch - 'a'] = 1 + *max_element(
                begin(dp) + max(0, ch - 'a' - k), begin(dp) + min(26, ch - 'a' + k + 1)));
        });
    } 
};


class Solution {
public:
    int topDown(const string& s, int k, int index, int prev, vector<vector<int>>&dp){
        //cout<<" index "<<index<<" prev "<<prev<<endl;
        if (index == s.size())
            return 0;
        if (dp[index][prev] != -1)
            return dp[index][prev];
        
        int cur = s[index] - 'a';
        if (abs(cur - prev) <= k  || prev == '{' - 'a')
            dp[index][prev] = max(dp[index][prev],  1 + topDown(s, k, index + 1, cur, dp)); //take
        dp[index][prev] =  max(dp[index][prev], topDown(s, k, index+1, prev, dp));  //not take

        
        //cout<<" index "<<index<<"cur "<<cur<<" "<< ((char)('a' + prev))<<" dp "<<dp[index][prev]<<endl;
        return dp[index][prev];
    }
    
    
    int longestIdealString(string s, int k) {
        if (s.empty()) return 0;
        vector<vector<int>>dp(s.size(), vector<int>(30 ,-1));
        return topDown(s, k, 0, '{' - 'a', dp);
    } 
};