/*

10. Regular Expression Matching

https://leetcode.com/problems/regular-expression-matching/description/

Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true

*/

/*
* could for example be expanded to `` (zero characters), . (one character), .. meaning two characters, or ... (three chars), .... (four chars) etc.. 
and the .. matches ab. .* just sort of means "insert anything". or nothing. nothing also technically matches.

1. * remove 前面的character
dp[i+1][j+1] = dp[i+1][j-1] Match zero time preceding. e.g. s = "ab" t = "abb*"

2. * repeat 前面character 0 次
   
   t =  a  b  *  c
s=  1   0  0  0  0
 a  0   1  0  1  0 
 b  0   0  1 _1_ =====>  i = 1, j = 2   dp[i+1][j+1] <= take dp[i][j+1],  
 c  0   0  0  0  1        take  dp[i][j+1] 原因是, dp[i][j+1] = dp[1][3] 只考虑了 s[i-1] ('a') 和 p[j-2] ('a')  match 不 match
                            s 和 t 再多考虑一位,  if s[i]  == p[j-1]  s= 'ab', t='ab'  dp[i+1][j+1] = dp[i][j+1] = true;

                          
                          
3. * repeat 前面多个 character 


   t =  a  b  *  c
s=  1   0  0  0  0 
 a  0   1  0  1  0 
 b  0   0  1  1 ===== > dp[i+1][j]: 表示 * 重复了0遍或者多变
 b  0   0  0 _1_ =====>  i = 2, j = 2   dp[i+1][j+1] <= take dp[i][j+1], 
 c  0   0  0  0  1        take  dp[i][j+1] 原因是, dp[i][j+1] = dp[2][3] 只考虑了 s[i-1] ('ab') 和 p[j-2] ('ab')  match 不 match, 
                         如果 s再多考虑一位, 因为是*, t是跟之前一样的pattern,  if s[i]  == p[j-1]  s= 'abb', t='ab'  dp[i+1][j+1] = dp[i][j+1] = true;
*/

class Solution {
public:
    bool isMatch(string s, string p) {
       int n1 = s.size(), n2 = p.size();
       vector<vector<int>>dp(n1+1, vector<int>(n2+1, 0));
       dp[0][0] = 1;
       for(int j = 1; j<n2 && p[j] == '*'; j+=2)
           dp[0][j+1] = dp[0][j-1];
        
       for(int i = 0; i<n1; ++i)
       {
           for(int j = 0; j<n2; ++j){
               if(s[i] == p[j] || p[j] == '.')
                   dp[i+1][j+1] = dp[i][j];
               else if(p[j] == '*')
                   dp[i+1][j+1] = dp[i+1][j-1] || ( s[i] == p[j-1] || p[j-1] == '.') && dp[i][j+1];
           }
       }
        return dp[n1][n2];
    }
};

/*
This Solution use 2D DP. beat 90% solutions, very simple.

Here are some conditions to figure out, then the logic can be very straightforward.

1, If p.charAt(j) == s.charAt(i) :  dp[i][j] = dp[i-1][j-1];
2, If p.charAt(j) == '.' : dp[i][j] = dp[i-1][j-1];
3, If p.charAt(j) == '*': 
   here are two sub conditions:
               1   if p.charAt(j-1) != s.charAt(i) : dp[i][j] = dp[i][j-2]  //in this case, a* only counts as empty
               2   if p.charAt(j-1) == s.charAt(i) or p.charAt(j-1) == '.':
                              dp[i][j] = dp[i-1][j]    //in this case, a* counts as multiple a 
                           or dp[i][j] = dp[i][j-1]   // in this case, a* counts as single a
                           or dp[i][j] = dp[i][j-2]   // in this case, a* counts as empty

*/


class Solution {
public:
    bool isMatch(string s, string p) {
        //if(s == "" && p == "") return false;
        vector<vector<bool>>dp(s.length()+1, vector<bool>(p.length()+1,false));
        dp[0][0] = true;
        for (int i = 0; i < p.length(); i++) {
            if (p[i] == '*' && dp[0][i-1]) {
                // cout<<" initialize i-1 "<<i<<" dp[0][i+1] true "<<endl;
                 dp[0][i+1] = true;
            }
        }
        
        for(int i = 0; i<s.length();i++){
            for(int j = 0; j<p.length();j++){
                //cout<<" i "<<i <<" j "<<j<<" s[i ]" <<s[i]<<" p[j]  "<<p[j]<<endl;
                if(s[i] == p[j] || p[j] == '.'){
                     //cout <<"s[i] = p[j]  || p[j] == '.' i-1 "<<i<<" j- 1 "<<j << " dp[i-1][j-1] =  "<<dp[i][j]<<endl;
                     dp[i+1][j+1] = dp[i][j];
                }
                else if(p[j] == '*'){
                    if(p[j-1]!=s[i] && p[j-1]!= '.'){
                        //cout <<"p[j-1]!=s[i] && p[j-1]!= '.' i "<<i<<" j- 2 "<<j-1 << "  dp[i-1][j-2] = "<<dp[i+1][j-1]<<endl;
                        dp[i+1][j+1] = dp[i+1][j-1];
                        
                    }
                        
                    else{
                        //cout <<"else ' i-1 "<<i<<" j "<<j+1 << " dp[i-1][j] = "<<dp[i][j+1]<<"  ' i "<<i+1<<" j- 1 "<<j-1 << "  dp[i][j-1] "<< dp[i+1][j]<<" ' i "<<i+1<<" j-2 "<<j-1 << "  dp[i][j-2] "<<dp[i+1][j-1]<<endl;
                        dp[i+1][j+1] = dp[i][j+1] || dp[i+1][j] || dp[i+1][j-1] ;
                        
                    }
                }
                //cout<<"finally "<<dp[i+1][j+1] <<endl;
            }
        }
        return dp[s.length()][p.length()];
    }
};



class Solution {
public:
    bool isMatch(string s, string p) {
        vector<vector<int>>dp(p.size()+1, vector<int>(s.size()+1,0)); //dp[i+1][j+1] 代表s[i] p[j]位置情况
        dp[0][0] = 1;
        for(int i = 1; i<=p.size();i++){
            for(int j = 0; j<=s.size(); j++){ // 
                if(j == 0 && p[i-1] == '*') dp[i][0] = dp[i-2][j];
                else if(j>0){
                    if(p[i-1]!='*') dp[i][j] =  p[i-1] == s[j-1] || p[i-1] == '.' ? dp[i-1][j-1] : 0;
                    else dp[i][j] = dp[i-2][j] || dp[i-1][j] || (j>1 && (p[i-2] == s[j-1] || p[i-2] == '.')  && dp[i][j-1] ); 
                        // dp[j] 
                        //dp[i-2][j] is zero preceding
                        //dp[i-1][j] is one preceding 
                        // dp[i][j-1] is two or more preceding
                }
            }
        }
        return dp[p.size()][s.size()];
    }
};


class Solution {
public:
    bool isMatch(string s, string p) {
        vector<vector<int>>dp(p.size()+1, vector<int>(s.size()+1,0)); //dp[i+1][j+1] 代表s[i] p[j]位置情况
        dp[0][0] = 1;
        for(int i = 1; i<=p.size();i++)
            for(int j = 0; j<=s.size(); j++) // 
                    if(p[i-1]!='*') dp[i][j] =  p[i-1] == s[j-1] || p[i-1] == '.' ? dp[i-1][j-1] : 0;
                    else dp[i][j] = dp[i-2][j] || dp[i-1][j] || (j>1 && (p[i-2] == s[j-1] || p[i-2] == '.')  && dp[i][j-1] ); 
                        // dp[j] 
                        //dp[i-2][j] is zero preceding
                        //dp[i-1][j] is one preceding 
                        // dp[i][j-1] is two or more preceding
        return dp[p.size()][s.size()];
    }
};


