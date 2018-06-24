/*
290. Word Pattern

Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Example 1:

Input: pattern = "abba", str = "dog cat cat dog"
Output: true
Example 2:

Input:pattern = "abba", str = "dog cat cat fish"
Output: false
Example 3:

Input: pattern = "aaaa", str = "dog cat cat dog"
Output: false
Example 4:

Input: pattern = "abba", str = "dog dog dog dog"
Output: false


*/

//记录相同位置字母上次出现的顺序
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<string,int>strmap;
        unordered_map<char, int>patmap;
        stringstream ss(str);
        string t;
        for(int i = 0; i<pattern.size(); i++){
            getline(ss,t,' ');
            char c = pattern[i];
            if(strmap.find(t) == strmap.end() && patmap.find(c) == patmap.end()){
                strmap[t] = i;
                patmap[c] = i;
            }else if(!strmap.count(t) || !patmap.count(c) || strmap[t]!=patmap[c])
                return false;
        }
        if(getline(ss,t,' ')) return false; //str 可能没有loop 完，因为长度不一样
        return true;
    }
};


//把pattern, 和str关联在一起， 比如 ABBA，A和第一个应该一样，可以str是aa bb bb cc, map[A] == aa != cc 也可以返回错
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<string,char>strmap;
        unordered_map<char, string>patmap;
        stringstream ss(str);
        string t;
        for(int i = 0; i<pattern.size(); i++){
            getline(ss,t,' ');
            char c = pattern[i];
            if(strmap.find(t) == strmap.end() && patmap.find(c) == patmap.end()){
                strmap[t] = c;
                patmap[c] = t;
            }else if(!strmap.count(t) || !patmap.count(c) || strmap[t]!=c)
                return false;
        }
        if(getline(ss,t,' ')) return false;
        return true;
    }
};


class Solution {
public:
    bool wordPattern(string pattern, string str) {
        unordered_map<char, int> p2i;
        unordered_map<string, int> w2i;
        istringstream in(str);
        
        int i = 0, n = pattern.size();
        for (string word; in >> word; ++i) {
            char c = pattern[i];
            if (p2i[c] != w2i[word]) return false;
            p2i[c] = i + 1;
            w2i[word] = i + 1;
        }
        
        return i == n;
    }
};