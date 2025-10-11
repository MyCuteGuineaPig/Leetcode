//2020
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<long>dp(n+1);
        dp[0] = 1;
        int mod = pow(10,9)+7;
        for(int i = 0; i<s.size();++i){
            if(s[i] == '*'){
                dp[i+1] = dp[i]*9 % mod;
            }
            else if(s[i] != '0')
                dp[i+1] = dp[i];
            if(i>0){
                if(s[i-1] == '1'){
                    if(s[i] == '*')
                        dp[i+1] += dp[i-1]*9 % mod;
                    else
                        dp[i+1] += dp[i-1] % mod;
                }else if(s[i-1] == '2'){
                    if(s[i] == '*')
                         dp[i+1] += dp[i-1]*6 % mod;
                    else if(s[i] - '0' <= 6)
                         dp[i+1] += dp[i-1] % mod;
                }else if(s[i-1] == '*'){
                    if(s[i] == '*')
                        dp[i+1] += dp[i-1]*15 % mod; //注意是15, 因为star 只能是 1 - 9
                    else if(s[i] - '0' <= 6)
                        dp[i+1] += dp[i-1]*2 % mod; //*6, 可以是16, 17
                    else
                        dp[i+1] += dp[i-1] % mod; //*7 只能是17
                }
            }
        }
        return dp[n] % mod;
    }
};


class Solution {
public:
    int numDecodings(string s) {
        if(s.size()==0) return 0;
        vector<long long>dp(s.size()+1);
        dp[0] = 1;
        dp[1] = s[0] == '*' ? 9 : (s[0] == '0' ? 0: 1);
        static const long long M = 1000000007;
        for(int i = 1; i<s.size();i++){
            dp[i+1] = s[i] == '*' ? (dp[i]*9)%M: (s[i] != '0' ? dp[i]: 0);
            if(s[i] == '*'){
                if(s[i-1] == '*') dp[i+1] += dp[i-1]*15;
                
                else if(s[i-1] == '1') dp[i+1] += dp[i-1]*9;
                    
                else if(s[i-1]=='2') dp[i+1] += dp[i-1]*6;
            }
            else{
                if(s[i-1]=='*'){
                    if(s[i]>='0' && s[i]<='6' ) dp[i+1] += dp[i-1]*2;
                    else dp[i+1] += dp[i-1];
                }
                else{
                    string two = s.substr(i-1,2);
                    if(two>="10" && two<="26") dp[i+1] += dp[i-1];
                }
            }
            dp[i+1] = dp[i+1]%M;
        }
        return dp[s.size()];
    }
};


class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<unsigned long long>dp(n+1);
        dp[0] = 1; 
        unsigned long long mod = 1e9 + 7;
        for(int i = 0; i < n; ++i){
            if(s[i] == '0') {
                dp[i+1] = 0;
                if (i > 0 && (s[i-1] == '1' || s[i-1] == '2')) dp[i+1] = dp[i-1];
                else if (i >0 && s[i-1] == '*') dp[i+1] = 2*dp[i-1] % mod;
                //可以是 10， 或者20 
            } else if (s[i] >= '1' && s[i] <= '9'){
                dp[i+1] = dp[i];
                if (i > 0 && (s[i-1] == '1' || s[i-1] == '2' && s[i] <= '6' || s[i-1] == '*' && s[i] >= '7' ))
                    dp[i+1] = ( dp[i+1] + dp[i-1]) % mod;
                else if (i> 0 && s[i-1] == '*' && s[i] <= '6') {
                    dp[i+1] = (dp[i+1] + 2*dp[i-1]) % mod;
                }
            } else {
                dp[i+1] = 9*dp[i] % mod;
                if (i > 0 && s[i-1] == '1') dp[i+1] = (dp[i+1] + 9*dp[i-1]) % mod;
                else if(i > 0 && s[i-1] == '2' ) dp[i+1] = (dp[i+1] + 6*dp[i-1]) % mod;
                else if (i > 0 && s[i-1] == '*') dp[i+1] = (dp[i+1] + 15*dp[i-1]) % mod;
            }
            //cout<<i<<" dp "<<dp[i+1] << endl;
        }
        return dp.back();
    }
};


/**
endingAny = current number of ways we could decode, ending on any number;
ending1 = current number of ways we could decode, ending on an open 1;
ending2 = current number of ways we could decode, ending on an open 2;
 */
class Solution {
public:
    int numDecodings(string s) {
        long mod = 1000000007;
        long endingAny = 1, ending1 = 0, ending2 = 0;
        for (char c: s) {
            long curEndingAny = 0;
            if (c == '*') {
                curEndingAny = 9 * endingAny + 9 * ending1 + 6 * ending2;
                ending1 = endingAny;
                ending2 = endingAny;
            } else {
                curEndingAny = (c == '0'? 0:endingAny) + ending1 + (c <= '6'? ending2:0);
                ending1 = (c == '1'? endingAny:0);
                ending2 = (c == '2'? endingAny:0);
            }
            endingAny = curEndingAny % mod;
            cout<<" curEndingAny "<<curEndingAny<<" ending1 "<<ending1<<"  ending2 "<<ending2<<endl;
        }
        return endingAny;
    }
};


class Solution {
public:
    static const long M = 1e9 + 7;
    int numDecodings(string s) {
        long endingAny = 1, ending1 = 0, ending2 = 0;
        for(char c: s){
            long curEndingAny;
            if(c=='*'){
                curEndingAny = 9*endingAny + 9*ending1 + 6*ending2; 
                ending1 = endingAny;
                ending2 = endingAny;
            }
            else{
                curEndingAny = (c!='0')*endingAny + ending1 + (c<='6')*ending2;
                ending1 = (c=='1')*endingAny;
                ending2 = (c=='2')*endingAny;
            }
            endingAny = curEndingAny%M;
        }
        return endingAny;
    }
};


class Solution 
{
public:
    int numDecodings(string s) 
    {
        long e0 = 1, e1 = 0, e2 = 0, f0, f1, f2, M = 1e9 + 7;
        for (char c : s)
        {
            if (c == '*')
            {
                f0 = 9 * e0 + 9 * e1 + 6 * e2;
                f1 = e0;
                f2 = e0;
            }
            else
            {
                f0 = (c > '0') * e0 + e1 + (c <= '6') * e2;
                f1 = (c == '1') * e0;
                f2 = (c == '2') * e0;
            }
            e0 = f0 % M;
            e1 = f1;
            e2 = f2;
        }
        return e0;
    }
};