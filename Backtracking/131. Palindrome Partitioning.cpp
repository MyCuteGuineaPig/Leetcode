/*
131. Palindrome Partitioning

Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

[
  ["aa","b"],
  ["a","a","b"]
]

*/

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>>res;
        vector<string>cur;
        backtracking(res,cur,s,0);
        return res;
    }
    
    void  backtracking(vector<vector<string>>& res, vector<string>& cur, const string & s, int begin){
        if(begin==s.size()){
            res.push_back(cur);
            return;
        }
        for(int i = begin; i<s.size();i++){
            if(isPalindrome(s,begin,i)){
                cur.push_back(s.substr(begin,i-begin+1));
                backtracking(res,cur,s,i+1);
                cur.pop_back();
            }
        }
        
    }
    
    bool isPalindrome(const string &s, int i, int j){
        while(i<=j && s[i]==s[j]) 
            i++, j--;
        return j<i;
    }
};