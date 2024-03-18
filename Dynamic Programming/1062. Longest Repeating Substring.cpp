class Solution {
public:
    bool valid(const string& s, int window_size){
        unordered_set<string>st; 
        for(int i = 0; i<=s.size() - window_size; ++i){
            string cur = s.substr(i, window_size);
            if (st.count(cur)) return true;
            st.insert(cur);
        }
        return false;
    }

    int longestRepeatingSubstring(string s) {
        int l = 0, r = s.size() - 1;
        while (l<=r){
            int mid = (l + r )/2; 
            //cout<<l<<" r " << r <<" mid "<<mid<<endl;
            if (!valid(s, mid))
            {
                r = mid-1;
            } else {
                l = mid + 1 ;
            }
        }
        return r; //or return l-1
    }
};


class Solution {
public:
    int longestRepeatingSubstring(string s) {
        int n = s.size();
        vector<vector<int>>dp(n+1,vector<int>(n+1));
        int res = 0;
        for(int i = 0 ; i < n; ++i){
            for(int j = 0; j < i; ++j){
                if(s[i] == s[j]){
                    res = max(res, dp[i+1][j+1] = 1 + dp[i][j]);
                }
            }
        }
        return res;
    }
};


//debug
class Solution {
public:
    int longestRepeatingSubstring(string S, int m_val = 0) {
        vector<vector<short>> dp(S.size() + 1, vector<short>(S.size() + 1));
        for (int i = 0; i < S.size(); ++i)
            for (int j = 0; j < i; ++j) {
                if (S[i] == S[j]) {
                    auto val = dp[i + 1][j + 1] = 1 + dp[i][j];
                    if (val > m_val) m_val = val;
                }
            }
        int n  =S.size();
        cout<<" , "<<" , ";
        for(auto s: S)
            cout<<s<<", ";
        cout<<endl;
        for(int i = 0; i<=n; ++i){
            if (i > 0)
                cout<<S[i]<<", ";
            else 
                cout<<" , ";
            for(int j = 0; j<=n; ++j)
                cout<<dp[i][j]<<", ";
            cout<<endl;
        }
        return m_val;
    }
};