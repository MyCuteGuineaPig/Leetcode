/*
205. Isomorphic Strings


Given two strings s and t, determine if they are isomorphic.

Two strings are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. 
No two characters may map to the same character but a character may map to itself.

Example 1:

Input: s = "egg", t = "add"
Output: true
Example 2:

Input: s = "foo", t = "bar"
Output: false
Example 3:

Input: s = "paper", t = "title"
Output: true
Note:
You may assume both s and t have the same length.

*/



//建立一种map，比如‘egg' 'add', 把s的map [e] = 'a', 把tmap的【a] = 'e', 下次如果有任何一个map 包含
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if(s.size()!=t.size()) return false;
        unordered_map<int,int>smap;
        unordered_map<int,int>tmap;
        for(int i = 0; i<s.size();i++){
            if(smap[s[i]] == 0 && tmap[t[i]] == 0){
                smap[s[i]] = t[i];
                tmap[t[i]] = s[i];
            }
            else if(smap[s[i]]!=t[i])
                return false;
        }
        return true;
    }
};


//v1, v2分别记录两个alphabet 上一位出现这个字母的位置，如果相同位上上一个字母出现位置不一样，pattern就不一样
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        vector<int> v1(256, -1), v2(256, -1);
        for(int i=0; i<s.size(); ++i)
        {
            if(v1[s[i]] != v2[t[i]])
                return false;
            
            v1[s[i]] = v2[t[i]] = i;
        }
        
        return true;
    }
};