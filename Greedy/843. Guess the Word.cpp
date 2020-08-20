/*
843. Guess the Word

This problem is an interactive problem new to the LeetCode platform.

We are given a word list of unique words, each word is 6 letters long, and one word in this list is chosen as secret.

You may call master.guess(word) to guess a word.  The guessed word should have type string and must be from the original list with 6 lowercase letters.

This function returns an integer type, representing the number of exact matches (value and position) of your guess to the secret word.  Also, if your guess is not in the given wordlist, it will return -1 instead.

For each test case, you have 10 guesses to guess the word. At the end of any number of calls, if you have made 10 or less calls to master.guess and at least one of these guesses was the secret, you pass the testcase.

Besides the example test case below, there will be 5 additional test cases, each with 100 words in the word list.  The letters of each word in those testcases were chosen independently at random from 'a' to 'z', such that every word in the given word lists is unique.

Example 1:
Input: secret = "acckzz", wordlist = ["acckzz","ccbazz","eiowzz","abcczz"]

Explanation:

master.guess("aaaaaa") returns -1, because "aaaaaa" is not in wordlist.
master.guess("acckzz") returns 6, because "acckzz" is secret and has all 6 matches.
master.guess("ccbazz") returns 3, because "ccbazz" has 3 matches.
master.guess("eiowzz") returns 2, because "eiowzz" has 2 matches.
master.guess("abcczz") returns 4, because "abcczz" has 4 matches.

We made 5 calls to master.guess and one of them was the secret, so we pass the test case.
Note:  Any solutions that attempt to circumvent the judge will result in disqualification.



*/


/*
Solution 1: minmax

先找与别的单词重合最多的单词猜（guess the word with minimum 0 matches.），然后根据结果，缩小范围，
再根据新的范围内重合最小的单词猜，重复以上步骤直到猜对

minimum 0 matches可以减小worse case

histogram peak (max) is smallest (min)

*/
/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        int x = -1;
        for(int z = 0; z<100 && x <6; z++){
            unordered_map<string, int>count;//数完全没有重合的
            for(auto w: wordlist) for(auto j: wordlist) if (match(w, j) == 0) count[w]++;
            string next = wordlist[0]; int curmin = count[wordlist[0]];
            
            for(auto it: count) if (it.second<curmin) { next = it.first; curmin = it.second;}
            
            x = master.guess(next);
            if(x == 6) break;
            vector<string>wordlist2;
            for(auto w: wordlist) if(match(w, next) == x) wordlist2.push_back(w);
            wordlist = wordlist2;
            
        }
    }
    
    int match(const string& l, const string& r){
        int count = 0;
        for(int i = 0; i<l.size();i++)
            if(l[i] == r[i]) count++;
        return count;
    }
};


//Solution 2
class Solution {
#define um unordered_map
#define us unordered_set
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        //for(string&s:wordlist)lower(s);
        us<string>unio;//候选词集合
        um<string,um<int,us<string>>>g;//建立一个表，保存着与每个单词重合字母数为0~5所对应的单词集合
        for(int i=0;i<(int)wordlist.size()-1;i++){
            for(int j=i+1;j<(int)wordlist.size();j++){
                int same=check(wordlist[i],wordlist[j]);
                g[wordlist[i]][same].insert(wordlist[j]);
                g[wordlist[j]][same].insert(wordlist[i]);
            }
        }//随机选一个词作为开头
        string s=wordlist[rand()%(int)wordlist.size()];
        for(int i=0;i<10;i++){
            if(i==0){//第一次猜，候选词集合就是与第一猜的词重合字母数为master.guess(s)的集合
                int same=master.guess(s);
                if(same==6)return;
                unio=g[s][same];
                s=*unio.begin();//从集合中选出一个词
            }else{//第2~10次猜，候选词集合会缩小为原集合与此次所猜词重合字母数为master.guess(s)的集合，一步步缩小范围
                int same=master.guess(s);
                if(same==6)return;
                auto&tempset=g[s][same];
                us<string>temp;
                for(auto it=unio.begin();it!=unio.end();it++){
                    if(tempset.find(*it)!=tempset.end())
                        temp.insert(*it);
                }
                unio=temp;
                s=*unio.begin();
            }
        }
    }
private:
    int check(string&a,string&b){//统计两个词的重合字母数量
        int res=0;
        for(int i=0;i<(int)a.size();i++)
            if(a[i]==b[i])
                res++;
        return res;
    }
    void lower(string&s){
        for(char&c:s)
            if(!(c>='a'&&c<='z'))
                c-=32;
    }
};

/*
Histogram:  histogram[i][s] 表示第i个字母s的频率， 
每次测试测试测频率最高的，然后trim 结果，如果match(word, x)!= res, trim wodlsit： 删除x，减小每个位置的char 的frequence by 1

The secret word is never taken out, 
because it is always the same match. In your case: when the candidate word is "troeee" and secret word is ["trophy"], 
matches = 3, so you eliminate all the words that do not have the same match with [troeee].
[troeee] [physss] = 0, removed
[troeee][troeee] = 6 ,removed
[troeee][trophy] = 3 ,stays
[troeee][trophi] = 3 ,stays

*/

class Solution {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        
        vector<vector<int>>prob(6, vector<int>(26));
        for(auto w: wordlist) for(int i = 0; i<6; i++) prob[i][w[i]-'a']++;
        int x = -1;
        for(int z = 0; z<100; z++){
            string next = bestcandidate(wordlist, prob);
            x = master.guess(next);
            if(x == 6) break;
            vector<string>wordlist2;
            for(auto w: wordlist) {
                if(match(w, next) == x) wordlist2.push_back(w);
                else for(int i = 0; i<6; i++) prob[i][w[i]-'a']--;
            }
            wordlist = wordlist2;
        }
    }
    
    int match(const string& l, const string& r){
        int count = 0;
        for(int i = 0; i<l.size();i++)
            if(l[i] == r[i]) count++;
        return count;
    }
    
    string bestcandidate(vector<string>& wordlist, vector<vector<int>>& prob){
        string best; int maxscore = 0;
        for(auto w: wordlist){
            int cur = 1; 
            for(int i = 0; i<6; i++)
                cur *= prob[i][w[i]-'a'];
            if(cur>maxscore) {
                maxscore = cur; 
                best = w;
            }
        }
        return best;
    }
    
    
};


/*
Minmax
*/

class Solution {

    int dist(const string& a, const string &b) 
    {
        // Maybe this can be memoized if too slow.
        int dist = 0;
        for (int idx = 0; idx < a.size(); ++idx) {
            dist += a[idx] == b[idx];
        }
        return dist;
    }
    
    int maxEquidistantSetSize(const string& word, const unordered_set<string>& guessSet) 
    {
        vector<int> hist(word.size() + 1, 0);    
        for (auto& guess : guessSet) {
            ++hist[dist(word, guess)];
        }
        return *max_element(hist.cbegin(), hist.cend());//找当前word guess与其他重合最多的是有几个重合了
    }
    
    string maxPartitioningGuess(const vector<string>& wordlist, const unordered_set<string>& guessSet)
    {
        auto maxGuessIt = wordlist.cend();
        int minMax = wordlist.size();
        for (auto it = wordlist.cbegin(); it != wordlist.cend(); ++it) {
            int curMax = maxEquidistantSetSize(*it, guessSet);
            if (curMax < minMax) { //update重合最多中最小的, 可以在eliminate the most
                minMax = curMax;
                maxGuessIt = it;
            }
        }
        return *maxGuessIt;
    }
    
public:
    void findSecretWord(vector<string>& wordlist, Master& master) 
    {
        // Start guessing
        unordered_set<string> guessSet(wordlist.cbegin(), wordlist.cend());
        while (guessSet.size() > 1) {
            // Calculate max partitioning elem taken from full word list
            string guessWord = maxPartitioningGuess(wordlist, guessSet);
        
            // Try the guess
            int d = master.guess(guessWord);
            if (d == guessWord.size()) return; // Got lucky!

            // Eliminate words whose distance != d
            for (auto it = guessSet.begin(); it != guessSet.end();) {
                if (dist(guessWord, *it) != d) {
                    it = guessSet.erase(it);
                } else {
                    ++it;
                }
            }
        }
        if (!guessSet.empty()) {
            master.guess(*guessSet.cbegin());
        }
    }
};