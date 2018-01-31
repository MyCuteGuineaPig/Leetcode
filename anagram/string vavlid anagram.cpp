/*
242. Valid Anagram
link:  https://leetcode.com/problems/valid-anagram/description/

For example,
s = "anagram", t = "nagaram", return true.
s = "rat", t = "car", return false.
You may assume the string contains only lowercase alphabets.
*/

class Solution {
public:
    bool isAnagram(string s, string t) {
        vector<int>map(128,0);
        for(int i = 0; i<s.length(); i++){
            map[s[i]]++;
        }
        for(int i = 0; i<t.length(); i++){
            if(--map[t[i]]<0) 
                return false;
        }
        for(int i = 97; i<123;i++){ //97 到123 是lowercase的
            if(map[i]>0) 
                return false;
        }
        return true;
        
    }
};


//much faster 
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        int n = s.length();
        int counts[26] = {0};
        for (int i = 0; i < n; i++) { 
            counts[s[i] - 'a']++;
            counts[t[i] - 'a']--;
        }
        for (int i = 0; i < 26; i++)
            if (counts[i]) return false;
        return true;
    }
};
