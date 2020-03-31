
/*
472. Concatenated Words

Given a list of words (without duplicates), please write a program that returns all concatenated words in the given list of words.
A concatenated word is defined as a string that is comprised entirely of at least two shorter words in the given array.

Example:
Input: ["cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"]

Output: ["catsdogcats","dogcatsdog","ratcatdogcat"]

Explanation: "catsdogcats" can be concatenated by "cats", "dog" and "cats"; 
 "dogcatsdog" can be concatenated by "dog", "cats" and "dog"; 
"ratcatdogcat" can be concatenated by "rat", "cat", "dog" and "cat".
Note:
The number of elements of the given array will not exceed 10,000
The length sum of elements in the given array will not exceed 600,000.
All the input string will only include lower case letters.
The returned elements order does not matter.
*/


class Solution {
public:
    unordered_set<string>conc;
    unordered_set<string>dict;
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        for(auto i: words)
            dict.insert(i);
        vector<string>res;
        for(auto s: words)
            if(check(s, 0, 0))
                res.push_back(s);
        return res;
    }
    
    bool check(const string& s, int beg, int count){
        if(beg == s.size() && count > 1){
            return true;
        }
        for(int i = beg; i<s.size();i++){
            if(dict.count(s.substr(beg,i-beg+1)) && check(s, i+1, count+1)){
                 return true;
            }
        }
        return false;
    }
};

/*
更efficient的解
*/

class Solution {
    vector<string> results;
    unordered_set<string> dict;
    int min_len = 1;
    bool isConcatenated(string const & word)
    {
        if (dict.count(word)) return true;
        for (int i =  min_len; i < word.size() - min_len + 1 ; ++ i)
            if (dict.count(word.substr(0, i)) > 0 && isConcatenated(word.substr(i, word.size() - i)))
                return true;
        return false;
    }
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        sort(words.begin(), words.end(), [](const string &lhs, const string &rhs){return lhs.size() < rhs.size();});
        min_len = max(1ul, words.front().size());
        for (int i = 0; i < words.size(); dict.insert(words[i++]))
            if (words[i].size() >= min_len * 2 && isConcatenated(words[i]))
                results.push_back(words[i]);
        return results;
    }
};

/*
DP solution much slower, 慢的原因是比如dogcatsdog，找到0，3 是dog了，而不是继续往下找别的
而是继续（0,5), (0,6), (0,7)属不属于背别的，而不是从(3,5),(3,6),(3,7)
0后是（1，3），（1，4），（1，5） 有没有来自dictionary，很没有效率

*/

vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
    unordered_set<string> s(words.begin(), words.end());
    vector<string> res;
    for (auto w : words) {
        int n = w.size();
        vector<int> dp(n+1);
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            if (dp[i] == 0) continue;
            for (int j = i+1; j <= n; j++) {
                if (j - i < n && s.count(w.substr(i, j-i))) dp[j] = 1; // j - i < n 控制避免word只是来自于字典中的一个词，而不是多个词合成.
            }
            if (dp[n]) { res.push_back(w); break; }
        }
    }
    return res;
}



/*
有memoization 反而变慢了
*/
class Solution {
public:
    unordered_set<string>memo;
    unordered_set<string>conc;
    unordered_set<string>dict;
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        for(auto i: words)
            dict.insert(i);
        vector<string>res;
        for(auto s: words)
            if(check(s, 0, 0))
                res.push_back(s);
        return res;
    }
    
    bool check(const string& s, int beg, int count){
        if(beg == s.size() && count > 1){
            return true;
        }
        for(int i = beg; i<s.size();i++){
            if(memo.count(s.substr(beg)))
                return true;
            
            if(dict.count(s.substr(beg,i-beg+1)) && check(s, i+1, count+1)){
                if(i!=s.size()-1)
                    memo.insert(s.substr(beg));
                return true;
            }
        }
        return false;
    }
};