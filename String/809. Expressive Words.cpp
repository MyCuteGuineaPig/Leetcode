/*
809. Expressive Words

Sometimes people repeat letters to represent extra feeling, such as "hello" -> "heeellooo", 
"hi" -> "hiiii".  Here, we have groups, of adjacent letters that are all the same character, 
and adjacent characters to the group are different.  A group is extended if that group is length 3 or more, 
so "e" and "o" would be extended in the first example, and "i" would be extended in the second example.  
As another example, the groups of "abbcccaaaa" would be "a", "bb", "ccc", and "aaaa"; and "ccc" and "aaaa" are the extended groups of that string.

For some given string S, a query word is stretchy if it can be made to be equal to S by extending some groups.  
Formally, we are allowed to repeatedly choose a group (as defined above) of characters c, 
and add some number of the same character c to it so that the length of the group is 3 or more. 
Note that we cannot extend a group of size one like "h" to a group of size two like "hh" - all extensions must leave the group extended - ie., 
at least 3 characters long.

Given a list of query words, return the number of words that are stretchy. 

Example:
Input: 
S = "heeellooo"
words = ["hello", "hi", "helo"]
Output: 1
Explanation: 
We can extend "e" and "o" in the word "hello" to get "heeellooo".
We can't extend "helo" to get "heeellooo" because the group "ll" is not extended.
Notes:

0 <= len(S) <= 100.
0 <= len(words) <= 100.
0 <= len(words[i]) <= 100.
S and all words in words consist only of lowercase letters
 

*/


/*
注意 "heee"
["hee"] 是成立的，所以对比条件是 因为ee加一个e变成连字
if (c1 < max(c2, 3) && c1 != c2) {
    break;
}

*/

/*
如果word[i]!=S[j] 的时候， 看S的j-1, j, j+1是不是连续是三个，若不是，再看过去是不是连续三个，若不是，break

Two pointer: 一个记录word位置，一个记录S的位置
当出现word[i]!=S[j] 的时候，就看是不是上个，现在，下个是连续三个的，如果是连续的前进j一位，跳过下个，直接到S的下下个
比如  h  e  e  e 
            _
     h  e   
     第二个e不相等，看是不是匹配的，如果是，前进j，不动i，因为S[j+1] = S[j] = S[j-1] = word[i]

当出现word[i]!=S[j], 且S[j+1] 和 S[j] 和 S[j-1] 不是连续三个，就要看过去三个的是不是连续三个 s[j+1] s[j] s[j-1]
如果不是，就break掉
比如  h  e  e  e  
              _
     h  e  e   
    
    过去的是连续三个,满足条件继续

比如  h  e  e  e   a
                  _
     h  e  e  e

    在a点没有过去的是连续三个,满足不满足

比如  e  e  
     _
     h  e  
    在e点 j 不大于1，没有过去三个，不满足

*/
class Solution {
public:
    int expressiveWords(string S, vector<string>& words) {
        int res = 0;
        for(auto word: words){
            int i = 0, j =0;
            for(; j<S.size(); j++){
                if(i < word.size() && word[i] == S[j]) i++;  
                else if(j>0 && S[j-1] == S[j] && j+1 < S.size() && S[j+1] == S[j]) j++;
                else if(!(j>1 && S[j-2] == S[j-1] && S[j-1] == S[j]))
                    break;
            }
            
            if(i == word.size() && j == S.size()) res++;
        }
        return res;
    }
};

class Solution {
public:
    int expressiveWords(string S, vector<string>& words) {
        int res = 0;
        for (auto &W : words) if (check(S, W)) res++;
        return res;
    }

    bool check(string S, string W) {
        int n = S.size(), m = W.size(), j = 0;
        for (int i = 0; i < n; i++)
            if (j < m && S[i] == W[j]) j++;
            else if (i > 1 && S[i - 2] == S[i - 1] && S[i - 1] == S[i]);
            else if (0 < i && i < n - 1 && S[i - 1] == S[i] && S[i] == S[i + 1]);
            else return false;
        return j == m;
    }

    /*
    
        bool check(string S, string W) {
        int n = S.size(), m = W.size(), i = 0, j = 0;
        for (int i2 = 0, j2 = 0; i < n && j < m; i = i2, j = j2) {
            if (S[i] != W[j]) return false;
            while (i2 < n && S[i2] == S[i]) i2++;
            while (j2 < m && W[j2] == W[j]) j2++;
            if (i2 - i != j2 - j && i2 - i < max(3, j2 - j)) return false;
        }
        return i == n && j == m;
    }
    
    */
};


class Solution {
public:
    int expressiveWords(string S, vector<string>& words) {
        int result = 0;
        const auto& R = RLE(S);
        for (const auto& word : words) {
            const auto& R2 = RLE(word);
            if (R.key != R2.key) {
                continue;
            }
            int i;
            for (i = 0; i < R.counts.size(); ++i) {
               const auto& c1 = R.counts[i];
               const auto& c2 = R2.counts[i];
               if (c1 < max(c2, 3) && c1 != c2) {
                   break;
               }
            }
            if (i == R.counts.size()) {
                ++result;
            }
        }
        return result;
    }

private:
    struct RLE {
        string key;
        vector<int> counts;
        RLE(const string& s) {
            int prev = -1;
            for (int i = 0; i < s.length(); ++i) {
                if (i == s.length() - 1 || s[i] != s[i + 1]) {
                    key.push_back(s[i]);
                    counts.emplace_back(i - prev);
                    prev = i;
                }
            }
        }
    };
};