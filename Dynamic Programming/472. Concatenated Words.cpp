

class Solution {
public:
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
而是继续（0,5), (0,6), (0,7)属不属于别的single word，而不是从(3,5),(3,6),(3,7)
0后是（1，3），（1，4），（1，5） 有没有来自dictionary，很没有效率

*/


class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        unordered_set<string>wordDict(words.begin(), words.end());
        vector<string>res;
        for(auto word: words) {
            int n  = word.size();
            vector<int>dp(n+1); // j - i < n 控制避免word只是来自于字典中的一个词，而不是多个词合成
            dp[0] = 1;
            for(int i = 0; i < n && !dp[n]; ++i) {
                if (!dp[i]) continue;
                for(int j = i + 1; j <=n && !dp[n]; ++j)
                    if (j - i < n && wordDict.count(word.substr(i, j-i)))
                        dp[j] = 1;
            }
            if (dp[n])
                res.push_back(word);
        }
        return res;
    }
};


/*
有memoization 反而变慢了
*/
class Solution {
public:
    unordered_set<string>memo;
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
                if(i!=s.size()-1) //这里不用检查count， s.substr(beg,i-beg+1)是一个词, s[i+1:] 之后是另一个词，count>1
                    memo.insert(s.substr(beg));
                return true;
            }
        }
        return false;
    }
};




//suffix Trie
class Solution {
public:
    struct Trie{
        unordered_map<char,Trie*>mp;
        bool isleaf = false;
    };
    Trie *trie;
    
    void build(const string& word){
        Trie* t = trie;
        for(auto w: word){
            if(t->mp.count(w) == 0)
                t->mp[w] = new Trie();
            t = t->mp[w];
        }
        t->isleaf = true;
    }
    
    bool find(Trie* t, const string& word, int index, int count){
        if(index == word.size())
            return t->isleaf && count > 1;
        if(t->mp.count(word[index]) == 0)
            return false;
        
        t = t->mp[word[index]];
        if(t->isleaf){
            if(find(trie, word, index+1, count+1))
                return true;
                
        }
        return find(t, word, index+1, count);
    }
    
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        trie =  new Trie();
        for(auto w: words)
            if(w.size()>=1) //比如 word ["cat", ""], "cat" 不算是解
                build(w);
        
        vector<string>res;
        for(auto w: words)
            if(find(trie, w, 0, 1))
                res.push_back(w);
        return res;
    }
};