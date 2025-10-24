class Solution {
public:
    int numberOfSubstrings(string s) {
        int res = 0; 
        int cnt = 0;
        int l = 0;
        int n = s.size();
        unordered_map<char,int>mp;
        for(int i = 0; i < s.size(); ++i){
            if (mp[s[i]] ++ == 0) cnt++;
            while (cnt == 3) {
                res += n - i;
                if (--mp[s[l++]] == 0) --cnt;
            }
        }
        return res;
    }
};


/*
lastpos 记录上次出现index的位置

a b c a b c 
        ^ 
        | 
       i = 4 
   ^
   | 
  最小的index, 可以组成是 b c a b 和 a b c a b

  每个点看以那个位置结束，可以组成多少个substring
 */
class Solution {
public:
    int numberOfSubstrings(string s) {
        unordered_map<char, int>lastpos;
        int res = 0;
        lastpos['a'] = lastpos['b'] = lastpos['c'] = -1;
        for(int i = 0; i < s.size(); ++i){
            lastpos[s[i]] = i;
            res += 1 + min({lastpos['a'], lastpos['b'], lastpos['c']});
        }
        return res;
    }
};