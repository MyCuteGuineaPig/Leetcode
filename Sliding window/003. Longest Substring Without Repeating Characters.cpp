/*
3. Longest Substring Without Repeating Characters


Given a string, find the length of the longest substring without repeating characters.

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.



*/


/*
sliding window, m[s[i]]是上次s[i]出现的位置，cur是以当前字母结尾的长度，

如果当前字母上次出现的位置 在前cur长度里，cur要缩小成上次字母出现后的长度

比如  "abcbe"
     a    b   c   b  e
cur  1    2   3   2  3 
*/
class Solution {  //记录当前substring的长度
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int>m;  //m[i] 表示字母i 上次出现的位置（位置是index + 1）
        int cur = 0, res = 0;
        for(int i = 0; i<s.size();i++){
            if(i+1-m[s[i]]<cur+1) cur = i+1-m[s[i]];
            else cur++;
            res = max(cur, res);
            m[s[i]] = i+1;
        }
        return res;
    }
};



/*
sliding window, 

每次记录substring 开始的位置，
如果当前字母 上次出现位置在现有start 后，把start 设置为上次当前字母出现的位置

从上次字母出现位置到现在距离就是 i-start
*/


class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<int, int>mp;
        int res = 0, l = -1;
        for(int i = 0; i<s.size(); ++i){
            if(mp.count(s[i])) {
                l = max(l, mp[s[i]]);
            } 
            mp[s[i]] = i;
            res = max(res, i - l);
        }
        return res;
    }
};


class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<int>st;
        int res = 0, l = 0;
        for(int i = 0; i<s.size(); ++i){
            while(st.count(s[i])){
                st.erase(s[l++]);
            }
            st.insert(s[i]);
            res = max(res, i - l + 1);
        }
        return res;
    }
};
/*
用hash set记录当前string，

用两个pointer, 一个快的，一个慢的，
    --  没遇到重复的字母，前进的快的，往hashset推当前的字母
    --  遇到重复的字母，前进慢的，直到把重复的字母删去
 比如  "abcbc“
*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char>set;
        int res = 0;
        for(int i = 0, j = 0; i<s.size();){
            if(!set.count(s[i])){
                set.insert(s[i++]);
                res = max(res, (int)set.size());
            }else{
                set.erase(s[j++]);
            }
        }
        return res;
    }
};