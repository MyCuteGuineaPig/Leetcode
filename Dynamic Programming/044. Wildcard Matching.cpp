/*
dp[i][j] 保存的是 s[0:i) 与 p[0:j) match 不match得结果

else if(p[j] == '*')
    dp[i+1][j+1] = dp[i][j];  *match 一个元素 s[i] = p[j]
    dp[i+1][j+1] = dp[i][j+1] *match 多个元素
    dp[i+1][j+1] =  dp[i+1][j]; *match 不匹配任何元素，s[0:i) 与 p[0:j-1) 匹配，given p[j] == '*';



*/
class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<bool>>dp(n+1,vector<bool>(m+1,false));
        dp[0][0] = true;
        
        /*
        // 比如 s= "adceb", p = "*a*b", 当 s index0a , 
        p index 1 为a, 是match的，dp[1][2] = dp[0][1] = true, 但是如果不提前设好 dp[0][1] = true, dp[1][2]是不行的
        dp[0][1] 为true 是因为 *可以为空, 所以 s = "", p = "*" 是匹配的
        
        */
        for(int j = 0; j<m; j++){
            if(dp[0][j] && p[j]=='*') //初始化，比如s = ""  p="**" 结果返回true
                dp[0][j+1] = true; 
            else 
                break;
        }
        
        
        for(int j = 0; j<m; j++){
            for(int i = 0; i<n; i++){
                if(s[i]==p[j] || p[j] == '?')
                     dp[i+1][j+1] = dp[i][j];
                else if(p[j] == '*')
                     dp[i+1][j+1] = dp[i][j] || dp[i][j+1] || dp[i+1][j];
            }
        }
        return dp[n][m];
        
    }
};





//2020
class Solution {
public:
    bool isMatch(string s, string p) {
        int n1 = s.size(), n2 = p.size();
        vector<vector<int>>dp(n1+1, vector<int>(n2+1,-1));
        return topDown(dp, s,p,0,0);
    }
    
    int topDown(vector<vector<int>>&dp, const string&s, const string&p, int i, int j){
        if(i == s.size() || j==p.size()){
            while(j<p.size() && p[j] == '*')
                    ++j;
            return i == s.size() && j==p.size() ? 1 : 0;
        }
        if(dp[i][j] == 0)
            return 0;
        if(s[i] == p[j] || p[j] == '?' || p[j] == '*')
             if(topDown(dp,s, p, i+1, j+1))
                return 1;
        
        if(p[j] == '*')
            return dp[i][j] = topDown(dp,s,p, i+1, j) ||  topDown(dp,s,p, i, j+1);
        
        return dp[i][j] = 0 ;
    }
};



class Solution {
public:
    bool isMatch(string s, string p) { 
        int m = s.length(), n = p.length();
        if (n > 30000) return false; // the trick
        vector<bool> cur(m + 1, false); 
        cur[0] = true;
        for (int j = 1; j <= n; j++) {
            bool pre = cur[0]; // use the value before update
            cur[0] = cur[0] && p[j - 1] == '*'; 
            for (int i = 1; i <= m; i++) {
                bool temp = cur[i]; // record the value before update
                if (p[j - 1] != '*')
                    cur[i] = pre && (s[i - 1] == p[j - 1] || p[j - 1] == '?');
                else cur[i] = cur[i - 1] || cur[i]; // cur[i - 1]表示跳过, cur[i]表示一次或者多次
                pre = temp;
            }
        }
        return cur[m]; 
    }
};

/*
Using Greedy Algorithm

I agree with dtcxzch. The complexity of the algorithm is O(p*s), 
where p and s are the lengths of the pattern and input strings. An example of such a worst-case input is:

input: bbbbbbbbbbbb
pattern: *bbbb

比如现在有两个*不用担心 上一个 *不能match的情况, 因为*可以match 任何值
比如 s = "adceb"
    p =  "*a*b", 只要保证当 j 到第二个*后，后面的可以match,前面*可以match任何，而第一个* 和第二个*之前已经match 不用管

     s = "adcefeafafeab"
    p =  "*a*b",  return true


比如   s =  "adbcdbce"
      p =  "*ad*bce"
   
   当p的bce 不match bcd时，i跳到 3('c'), j跳回4('*')
    
*/
class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size(), i = 0, j = 0, stari = -1, starj = -1;
        while(i<n){
            if( j < m && p[j] == '*'){
                stari = i;
                starj = j++;
            }else if(j < m && (s[i] == p[j] || p[j] == '?' )){
                i++; j++;
            }else if(stari >= 0){
                i = ++stari;  //移动到下一位，*match 增加一位, /之前星号代表的，不match了,所以回到星号之前match的下一个
                j = starj + 1;
            }
            else return false;
        }
         while(j<m && p[j] == '*') j++;
        return j == m ;
    }
};


class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        int stari = -1, starj = -1;
        int i = 0, j = 0;
        while( i < n) {
            if (j <m && (s[i] == p[j] || p[j] == '?')){
                ++i;
                ++j;
            } else if (j<m && p[j]=='*')  {
                stari = i;
                starj = ++j;
            } else if(stari>=0) {
                i = ++stari;
                j = starj;
            } else {
                return false;
            }
        }
        while(j<m && p[j] == '*') ++j;
        return j == m;
    }
};


//recurion, 可skip 不是很ideal的
class Solution {
    // return value:
    // 0: reach the end of s but unmatched
    // 1: unmatched without reaching the end of s
    // 2: matched
    int dfs(string& s, string& p, int si, int pi) {
        if (si == s.size() and pi == p.size()) return 2;
        if (si == s.size() and p[pi] != '*') return 0;
        if (pi == p.size()) return 1;
        if (p[pi] == '*') {
            if (pi+1 < p.size() and p[pi+1] == '*') 
                return dfs(s, p, si, pi+1); // skip duplicate '*'
            for(int i = 0; i <= s.size()-si; ++i) {
                int ret = dfs(s, p, si+i, pi+1);
                if (ret == 0 or ret == 2) return ret; 
            }
        }
        if (p[pi] == '?' or s[si] == p[pi])
            return dfs(s, p, si+1, pi+1);
        return 1;
    }    
    
public:
    bool isMatch(string s, string p) {
        return dfs(s, p, 0, 0) > 1;
    }
};


class Solution {
private:
    bool helper(const string &s, const string &p, int si, int pi, int &recLevel)
    {
        int sSize = s.size(), pSize = p.size(), i, curLevel = recLevel;
        bool first=true;
        while(si<sSize && (p[pi]==s[si] || p[pi]=='?')) {++pi; ++si;} //match as many as possible
        if(pi == pSize) return si == sSize; // if p reaches the end, return
        if(p[pi]=='*')
        { // if a star is met
            while(p[++pi]=='*'); //skip all the following stars
            if(pi>=pSize) return true; // if the rest of p are all star, return true
            for(i=si; i<sSize; ++i)
            {   // then do recursion
                if(p[pi]!= '?' && p[pi]!=s[i]) continue;
                if(first) {++recLevel; first = false;}
                if(helper(s, p, i, pi, recLevel)) return true;
                if(recLevel>curLevel+1) return false; // if the currently processed star is not the last one, return
            }
        }
        return false;
    }
public:
    bool isMatch(string s, string p) {
        int recLevel = 0;
        return helper(s, p, 0, 0, recLevel);
    }
};