

/*
140. Word Break II

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, 
add spaces in s to construct a sentence where each word is a valid dictionary word. 
You may assume the dictionary does not contain duplicate words.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

UPDATE (2017/1/4):
The wordDict parameter had been changed to a list of strings (instead of a set of strings). 
Please reload the code definition to get the latest changes.


*/

class Solution {
public:
    unordered_map<int,vector<string>>map;
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string>dict(wordDict.begin(),wordDict.end());
        vector<string> cur;
        return helper(s,dict,0);
    }
    
    
    vector<string> helper(const string & s, unordered_set<string>&dict, int index){
        if(map.count(index)>0)
            return map[index];
        vector<string>res;
        
        for(int i = index; i<s.size();i++){
            string sub = s.substr(index,i-index+1);
            if(dict.find(sub)!=dict.end()){
                if(i==s.length()-1) res.push_back(sub);
                else{
                    vector<string> temp= combine(sub, helper(s,dict,i+1));
                    res.insert(res.end(),temp.begin(),temp.end());
                }
            }
        }
        
        map[index] = res;
        return res;
    }
    
    vector<string>combine(const string& word, vector<string>after){
        for(int i = 0; i<after.size();i++){
            after[i] = word+" "+after[i];
        }
        return after;
    }

};


class Solution {
    unordered_map<string, vector<string>> m;

    vector<string> combine(string word, vector<string> prev){
        for(int i=0;i<prev.size();++i){
            prev[i]+=" "+word;
        }
        return prev;
    }

public:
    vector<string> wordBreak(string s, unordered_set<string>& dict) {
        if(m.count(s)) return m[s]; //take from memory
        vector<string> result;
        if(dict.count(s)){ //a whole string is a word
            result.push_back(s);
        }
        for(int i=1;i<s.size();++i){
            string word=s.substr(i);
            if(dict.count(word)){
                string rem=s.substr(0,i);
                vector<string> prev=combine(word,wordBreak(rem,dict));
                result.insert(result.end(),prev.begin(), prev.end());
            }
        }
        m[s]=result; //memorize
        return result;
    }
};



class Solution {
public:
    
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_map<int,vector<string>>map{{s.size(),{""}}};
        unordered_set<string>dict(wordDict.begin(),wordDict.end());
        function<vector<string>(int)> sentences = [&](int i){
            if(!map.count(i))
                for(int j = i+1; j<=s.size();j++)
                    if(dict.count(s.substr(i,j-i)))
                        for(string tail: sentences(j))
                            map[i].push_back(s.substr(i,j-i)+(tail=="" ? "" : ' '+tail));
            return map[i];
        };
        return sentences(0);
    }
    

};



class Solution {
public:
    void build(vector<vector<int>>&dp, const string& s, vector<string>&res, vector<string>&cur, int index){
        if(index == 0){
            string tmp = "";
            for(int i = cur.size()-1; i >= 0; --i){
                tmp += cur[i]; 
                if (i != 0) tmp += " ";
            }
            res.push_back(tmp);
            return;
        }
        for(auto & prev: dp[index]){
            string tmp = s.substr(prev, index-prev);
            cur.push_back(tmp);
            build(dp, s,res,  cur, prev);
            cur.pop_back();
        }
    }


    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string>seen(wordDict.begin(), wordDict.end());
        int n = s.size();
        vector<vector<int>>dp(n+1);
        for(int i = 0; i < n; ++i){
            if(i== 0 || !dp[i].empty()){
                for(int r = i; r<n; ++r){
                    string tmp = s.substr(i, r-i + 1);
                    if (seen.count(tmp)){
                        dp[r+1].push_back(i);
                    }
                }
            }
        }
        if(dp[n].empty()) {
            return {};
        }
        vector<string> res, cur;
        build(dp, s, res, cur,n);
        return res;
    }
};