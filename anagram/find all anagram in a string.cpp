/*
483:  Find All Anagrams in a String
https://leetcode.com/problems/find-all-anagrams-in-a-string/description/

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

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char,int>m, n;
        
        vector<int>res;
        int k = p.size();
        for(auto i: p)
            n[i]++;

        for(int i = 0; i<s.length();i++){
            m[s[i]]++;
            if(i>=k){
                m[s[i-k]]--;//remove k position before
                if(m[s[i-k]]==0) m.erase(s[i-k]);
            }
            if(i>=k-1 && m==n){ // to see if having anagram
                res.push_back(i-k+1);
            }
        }
        return res;
    }
};



/**********************************************************************************************/
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> pv(26,0), sv(26,0), res;
        if(s.size() < p.size())
           return res;
        // fill pv, vector of counters for pattern string and sv, vector of counters for the sliding window
        for(int i = 0; i < p.size(); ++i)
        {
            ++pv[p[i]-'a'];
            ++sv[s[i]-'a'];
        }
        if(pv == sv)
           res.push_back(0);

        //here window is moving from left to right across the string. 
        //window size is p.size(), so s.size()-p.size() moves are made 
        for(int i = p.size(); i < s.size(); ++i) 
        {
             // window extends one step to the right. counter for s[i] is incremented 
            ++sv[s[i]-'a'];
            
            // since we added one element to the right, 
            // one element to the left should be forgotten. 
            //counter for s[i-p.size()] is decremented
            --sv[s[i-p.size()]-'a']; 

            // if after move to the right the anagram can be composed, 
            // add new position of window's left point to the result 
            if(pv == sv)  
               res.push_back(i-p.size()+1);
        }
        return res;
    }
};