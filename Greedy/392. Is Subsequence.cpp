/*

392. Is Subsequence
https://leetcode.com/problems/is-subsequence/description/

Given a string s and a string t, check if s is subsequence of t.

You may assume that there is only lower case English letters in both s and t. 
t is potentially a very long (length ~= 500,000) string, and s is a short string (<=100).

A subsequence of a string is a new string which is formed from the original string 
by deleting some (can be none) of the characters 
without disturbing the relative positions of the remaining characters. 
(ie, "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
s = "abc", t = "ahbgdc"

Return true.

Example 2:
s = "axc", t = "ahbgdc"

Return false.

Follow up:
If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B,
 and you want to check one by one to see if T has its subsequence. 
 In this scenario, how would you change your code?

*/




class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i = 0, j = 0, n = s.size(), m = t.size();
        while(i<n && j < m){
            if(s[i] == t[j]){
                i++;j++;
            }  
            else j++;
        }
        return i == n;
    }
};


/*

Just go through t and "cross off" the matching characters in s. Then return whether there's nothing left in s.

Sometimes, C makes things easier... here it's helpful that C strings are null terminated and that
 I can easily pop off a string's first character in constant time just by incrementing the pointer.
*/


bool isSubsequence(char* s, char* t) {
    while (*t)
        s += *s == *t++;
    return !*s;
}



class Solution {
public:
    bool isSubsequence(string s, string t) {
    	auto i = s.begin();
        for(char c : t) i += (*i == c);
        return i == s.end();
    }
};

/*
For followup: 

using Binary Search,
running time: O(len(s) * log(len(t)))

Binary Search:
    记录每个char的index，把index push到unordered_map中char作为key的vector里，因为是按照t从左到右排序，index逐渐增加，
    所以每个key的vector里数也是有小到大有序排序
    search match的时候用prev记录上一个index的位置,下一个index必须大于它 (upper_bound)


*/


class Solution {
public:
    bool isSubsequence(string s, string t) {
        unordered_map<char, vector<int>>dict;
        for(int i = 0; i<t.size(); i++){
            dict[t[i]].push_back(i);
        }
        int prev = -1;
        for(char c: s){
            auto it = upper_bound(dict[c].begin(),dict[c].end(), prev);
            if(it == dict[c].end()) return false;
            prev = *it;
        }
        return true;
    }
};


/*
Follow-up Faster, O(len(t) + sum(len(s[i])))
*/
class Solution {
public:
    vector<bool> isSubsequence(vector<string> ss, string t) {
    	vector<string::const_iterator> iters(ss.size());
    	vector<vector<int> > waitingList(26);
    	for(int i = 0; i < ss.size(); i++) {
    		iters[i] = ss[i].begin();
    		waitingList[*iters[i] - 'a'].push_back(i);
    	}
        for(char c : t) {
        	vector<int> updateList = waitingList[c - 'a'];
        	waitingList[c - 'a'].clear();
        	for(int i : updateList) {
        		iters[i]++;
        		waitingList[*iters[i] - 'a'].push_back(i);
        	}
        }
        vector<bool> ans(ss.size());
        for(int i = 0; i < ss.size(); i++) {
        	ans[i] = iters[i] == ss[i].end();
        }
        return ans;
    }
};


class Solution {
public:
    vector<bool> isSubsequence(vector<string> ss, string t) {
    	vector<string::const_iterator> iters(ss.size());
    	for(int i = 0; i < ss.size(); i++) {
    		iters[i] = ss[i].begin();
    	}
        for(char c : t) {
        	for(int i = 0; i < ss.size(); i++) {
        		iters[i] += *iters[i] == c;
        	}
        }
        vector<bool> ans(ss.size());
        for(int i = 0; i < ss.size(); i++) {
        	ans[i] = iters[i] == ss[i].end();
        }
        return ans;
    }
};