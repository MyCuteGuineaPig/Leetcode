/*
438. Find All Anagrams in a String


Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".
*/

/*
保持windows 的长度不变为p， l是算p中还剩几个点没有被count过

减去当前点
    map[s[i]-'a']-->0 代表遇到s[i]之前，map这点大于0，代表这个字母在p出现过（只有p中的字母才会++）,

加上初始点
    ++map[s[i-m+1]-'a'] > 0 代表这个点在p出现过，因为只有p中出现的才会加后大于0
    初始点之前都做过l自减，现在因为要刨除这点，自加l

*/
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int>map(26,0);
        for(auto i: p)
            map[i-'a']++;
        int m = p.size(), l = p.size();
        vector<int>res;
        for(int i = 0; i<s.size();i++){
            if(map[s[i]-'a']-->0) l--;
            if(l == 0) res.push_back(i-m+1);
            if(i>=m-1){
                if(++map[s[i-m+1]-'a'] > 0) l++;
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char,int>dict;
        for(auto& c: p)
            dict[c]++;
        int cnt = 0;
        vector<int>res;
        for(int i = 0; i<s.size(); ++i){
            if (--dict[s[i]]>=0) ++cnt;
            if (cnt == p.size()) 
                res.push_back(i-p.size()+1);
            if (i >= p.size()-1 && ++dict[s[i-p.size()+1]]>0)
                    --cnt;
        
        }
        return res;
    }
};



/*
算right 和left的，

如果当前的数 map[s[i]-'a']<0, ++start(left), 如果 i (right ) - start(left) + 1 == windows size(), 当前每个数都==0，找到结果

*/

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int>map(26,0);
        for(auto i: p)
            map[i-'a']++;
        int m = p.size(), start = 0;
        vector<int>res;
        for(int i = 0; i<s.size();i++){
            map[s[i]-'a']--;
            while(map[s[i]-'a'] < 0) map[s[start++]-'a']++; 
            //start <= i, 比如“abceabc", p = "abc", 当i=e, 要把start前进到a（e的后一位）
            if(i-start+1 == m){
                res.push_back(start);
            }
        }
        return res;
    }
};




//算vector 相等的
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int s_size = s.size();
        int p_size = p.size();
        vector<int> s_vec(26, 0);
        vector<int> p_vec(26,0);
        vector<int> vec;
        if(s_size < p_size) return vec;
        
        for(int i = 0; i < p_size; ++i) {
            ++s_vec[s[i] - 'a'];
            ++p_vec[p[i] - 'a'];
        }
        
        if(s_vec == p_vec) vec.push_back(0);
        
        for(int i = 1; i < s_size - p_size + 1; ++i) {
            --s_vec[s[i-1] - 'a'];
            ++s_vec[s[i + p_size - 1] - 'a'];
            if(s_vec == p_vec) vec.push_back(i);
        }
        
        return vec;
    }
};