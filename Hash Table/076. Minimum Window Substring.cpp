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


//sliding windows
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char,int>m;
        for(auto i: t) m[i]++;
        
        int  count = t.size(), curlen = s.size();
        int head = -1;
        
        for(int i = 0, j = 0; i<s.size();i++){
            if(m[s[i]]-->0) count--;
            while(j<=i && count == 0){
                if( i - j + 1 <= curlen){
                    head = j; 
                    curlen = i-j+1;
                }
                if(++m[s[j++]]>0) count++;
            }
        }
        //cout<<"head "<<head<<"curlen "<<curlen<<endl;
        return  head == -1 ? "" : s.substr(head, curlen);
    }
};

lass Solution {
public:
    string minWindow(string s, string t) {
        if(s.size() < t.size() || t.empty()) return "";
        int start = -1, end = s.size()+1;
        unordered_map<char,int>mp, lookup;
        for(auto i: t) lookup[i]++;
        for(int i = 0, l = 0, cnt = t.size(); i<s.size(); i++){
            ++mp[s[i]];
            if(lookup.count(s[i]) && mp[s[i]] <= lookup[s[i]])
                cnt--;
            if(cnt == 0){
                if(i-l < end - start){
                    end = i; 
                    start = l;
                }
                cnt++;
                --mp[s[l++]];
            }
            while(l<=i && (lookup.count(s[l]) == 0 || mp[s[l]] > lookup[s[l]])){
                --mp[s[l++]];
            }
        }
        return start == -1 ? "" : s.substr(start, end-start+1);
    }
};


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
        vector<char,int>dict;
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
string minWindow(string s, string t) 
{
	vector<int> vmap(128, 0);
	int count = t.size(), beg = 0, end = 0, d = INT_MAX, head = 0;
	for (int i = 0; i < t.size(); i++)
		vmap[t[i]]++;
	while (end < s.size())
	{
		if (vmap[s[end++]]-->0)	count--;//先判断vmap[s[end]]>0，字符是否在目标串中
		while (count == 0)  //完成匹配
		{
			if (end - beg < d)  //判断串是否最短
			{
				d = end - beg;
				head = beg;
			}
			if (vmap[s[beg++]]++ == 0) count++;  //让匹配的第一个起点字符失效，从而进行下一次匹配
		}
	}
	return d == INT_MAX ? "" : s.substr(head, d);
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
