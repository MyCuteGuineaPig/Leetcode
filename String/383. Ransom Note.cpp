/*
383. Ransom Note


Given an arbitrary ransom note string and another string containing letters from all the magazines, 
write a function that will return true if the ransom note can be constructed from the magazines ; otherwise, it will return false.

Each letter in the magazine string can only be used once in your ransom note.

Note:
You may assume that both strings contain only lowercase letters.

canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true

*/


class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int>m;
        for(auto i: magazine) m[i]++;
        for(auto i: ransomNote){
            if(m.count(i) == 0 || m[i] <= 0) return false;
            m[i]--;
        }
        return true;
    }
};


class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> counts(26);
        int letters = 0;
        for (const auto& c : ransomNote) {
            if (counts[c - 'a']++ == 0) {
                ++letters;
            }
        }
        for (const auto& c : magazine) {
            if (--counts[c - 'a'] == 0 && --letters == 0) {
                // Break as soon as possible if letters have been enough.
                break;
            }
        }
        return letters == 0;
    }
};


class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        
        int a[400];
        memset(a, 0, sizeof(a));
        
        for (int i = 0;i < ransomNote.size();i ++)
            a[(int)ransomNote[i]] ++;
        
        for (int i = 0;i < magazine.size();i ++)
            a[(int)magazine[i]] --;
        
        for (int i = 0;i < 400;i ++)
        {
            if(a[i] > 0)
                return false;
        }
        return true;
    }
};