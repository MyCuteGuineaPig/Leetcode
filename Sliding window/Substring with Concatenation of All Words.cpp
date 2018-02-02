/*

30 Substring with Concatenation of All Words
https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/
You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).

*/






class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        unordered_map<string,int>counts;
        for(auto i : words)
            counts[i]++;
        int totalLen = words[0].size()*words.size();
        int len = words[0].size();
        for(int i = 0; i<s.length()-totalLen+1; i++){
            unordered_map<string,int>seen;
            for(int j = 0; j<words.size();j++){
                string temp = s.substr(i+j*len,len);
                seen[temp]++;
                if(counts.count(temp)==0 || seen[temp]>counts[temp])
                   break;
                if(j==words.size()-1)
                    res.push_back(i);
            }
            
        }
        return res;
    }
};





