/*
76. Minimum Window Substring

Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

Example:

Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"
Note:

If there is no such window in S that covers all characters in T, return the empty string "".
If there is such window, you are guaranteed that there will always be only one unique minimum window in S.


*/


/*
每次先减去当下的，然后看原来dictionary(T)里是否含有这个char，如果含有的话，dict[s[i]]会大于0，减去count
然后如果count == 0，前进start到满足开始的起点(最小的起点)
比如S = 'BEEEEBANC', T='ABC', start 在0的B的位置，前进B越过E,到最近的B，
-- 机制是，因为T里有一个B，S里有2个B，如果第一个B，call 字典的话，是负数

用vector 比unordered_map 快3倍
vector: 9ms
unordered_map: 22ms
*/
class Solution {
public:
    string minWindow(string s, string t) {
        if(s.size()<1 || t.size()<1 || t.size()>s.size()) return "";
        unordered_map<char,int>dict;
        for(auto i: t) dict[i]++;
        int minlen = numeric_limits<int>::max(), minstart = 0, count = t.size();
        for(int i = 0, start = 0; i<s.size();i++){
            dict[s[i]]--;
            if(dict[s[i]]>=0) count--;
            if(!count){
                while(dict[s[start]]<0) { 
                    dict[s[start]]++;
                    start++;
                }
                if(i-start+1<minlen) {
                    minlen = i-start+1;
                    minstart = start;
                }
                dict[s[start]]++;
                count ++;
                start++;
            }
        }
        return minlen == numeric_limits<int>::max() ? "" : s.substr(minstart,minlen);
    }
};


class Solution {
public:
    string minWindow(string s, string t) {
        if(s.size()<1 || t.size()<1 || t.size()>s.size()) return "";
        unordered_map<char,int>dict;
        for(auto i: t) dict[i]++;
        int minlen = numeric_limits<int>::max(), minstart = 0, count = 0;
        for(int i = 0, start = 0; i<s.size();i++){
            dict[s[i]]--;
            if(dict[s[i]]>=0) count++;
            while(dict[s[start]]<0) { 
                dict[s[start]]++;
                start++;
            }
            if(count == t.size() && i-start+1<minlen) {
                minlen = i-start+1;
                minstart = start;
            }
        }
        return minlen == numeric_limits<int>::max() ? "" : s.substr(minstart,minlen);
    }
};

class Solution {
public:
string minWindow(string s, string t) {
        vector<int> map(128,0);
        for(auto c: t) map[c]++;
        int counter=t.size(), begin=0, end=0, d=INT_MAX, head=0;
        while(end<s.size()){
            if(map[s[end++]]-->0) counter--; //in t
            while(counter==0){ //valid
                if(end-begin<d)  d=end-(head=begin);
                if(map[s[begin++]]++==0) counter++;  //make it invalid
            }  
        }
        return d==INT_MAX? "":s.substr(head, d);
    }
};

class Solution {
public:
    string minWindow(string s, string t) {
        int n=s.size();
        int m=t.size();
        if(n<1 || m<1 || n<m)
            return string("");
        int map[255]={0};
        for(char c: t)
            map[c]--;
        
        int counter=-m, begin=0, end=0;
        int d=n+1, head=0;
        while(end<n)
        {
            if(map[s[end]]<0)
            { 
                counter++;
            }
            map[s[end]]++;
            end++;
            
            while(counter==0)
            {
                if(d>end-begin)
                {
                    d=end-begin;
                    head=begin;
                }
                if(map[s[begin]]==0) counter--;
                map[s[begin]]--;                    
                begin++;
            }
        }
        if(d==n+1)
            return string("");
        return string(s, head, d);
    }
};


class Solution {
public:
    string minWindow(string S, string T) {
    if(S.length()==0 || T.length()==0) return "";
        unordered_map<char, int> m;

        for(auto k: T)
            m[k]++;
        
        int minLen =  INT_MAX, minId = 0, i = -1, j = 0, size = S.length();
        // i 必须是﹣1， 必须initialize size,因为S.length() 返回时size_t 默认为正，
        // -1和size_t 没法比
        int require = T.size();
        while(i<size && j<size){
            if(require){
                i++;
                m[S[i]]--;
                if(m[S[i]]>=0) {
                    require--;
                }
            }
            else{
                if(minLen>i-j+1){
                    minLen = i-j+1;
                    minId = j;
                }
                if(m[S[j]]>=0){
                    require++;
                }
                m[S[j]]++;
                j++;
            }
        }
        return minLen == INT_MAX ? "": S.substr(minId,minLen);
    }
};