
/***错误解**/
class Solution {
public:
    int findSubstringInWraproundString(string p) {
        if(p.size()==0) return 0;
        vector<int>letters(26,0);
        int len = 1, res = 1;
        letters[p[0] - 'a'] = 1;
        for(int i = 1; i<p.size();i++){
            int cur = p[i] - 'a';
            int prev = p[i-1] - 'a';
            if(prev == cur - 1 || (prev == 25 && cur == 0)){
                len++;
                if(letters[cur] < letters[prev]+len) // 错误
                {
                    res += len; // 这样会多算 比如 abcdefghijklmnopqrstuvwxyza,  到a的时候是27，应该加27，但是27个中第27个就是a，已经算过了一次，所以不行
                    letters[cur] = letters[prev]+len;
                }
            }else{
                len = 1;
                if(letters[cur] == 0){
                    res++;
                    letters[cur] =1;
                }
                    
            }
        }
        return res;
    }
};

/**
 注意几种情况:

 1. bcabc = 6,  b, c, bc, a, ab, abc
 2. abaab = 3,  a, b, ab

dp[i] 表示到字母i, 最长的距离，e.g. dp['d'] = 3 表示 bcd 都已经记录过了，
                                 dp['a'] = 3 表示 yza 都已经记录过了

  bcabc, 第一个b len = 1 记录 dp['b'] = 1, 
         第二个b len = 2 ('ab') 记录 res += 2 -1,  dp['b'] = 2. 增加记录的'a'

 */
class Solution {
public:
    int findSubstringInWraproundString(string p) {
        vector<int>letters(26,0);
        int len = 0, res = 0;
        for(int i = 0; i<p.size();i++){
            int cur = p[i] - 'a';
            if(i>0 && ((p[i-1] - 'a')+1)%26 != cur) len = 0;
            if (++len > letters[cur]) {
                res += len - letters[cur];
                letters[cur] = len;
            }
            
        }
        return res;
        
    }
};


class Solution {
public:
    int findSubstringInWraproundString(string p) {
        vector<int>dp(26,0);
        int res = 0, len = 0;
        for(int i = 0; i<p.size(); ++i){
            int cur = p[i] - 'a';
            if(i > 0 && (p[i-1] - 'a' + 1)%26 != cur)
                len = 0;
            if(++len > dp[cur])
            {
                dp[cur] = len; 
            }
        }
        return accumulate(dp.begin(), dp.end(),0);
    }
};

//Two pointer + dp
class Solution {
public:
    int findSubstringInWraproundString(string p) {
        vector<int> lens(26, 0);
        int i = 0;
        int j = 1;
        while (j <= p.length()) {
            while (j<p.length() && (p[j]=='a' && p[j-1]=='z' || p[j]==p[j-1]+1)) {
                j++;
            }
            while (i < j) {
                lens[p[i]-'a'] = max(lens[p[i]-'a'], j-i);
                i++;
            }
            j++;
        }
        return accumulate(lens.begin(), lens.end(), 0);
    }
};

class Solution {
public:
    int findSubstringInWraproundString(string p) {
        int len[26]={0}, i = 0, n = p.size();
        for(int j=0;j<n;j++)
            if(j>i && p[j-1]+1!=p[j] && p[j-1]-p[j]!=25) {
                for(int k=i;k<min(j,i+26);k++) len[p[k]-'a'] = max(len[p[k]-'a'],j-k);
                i=j;
            }
        for(int k=i;k<min(n,i+26);k++) len[p[k]-'a'] = max(len[p[k]-'a'],n-k);
        return accumulate(len,len+26,0);
    }
};