/*
820. Short Encoding of Words

Given a list of words, we may encode it by writing a reference string S and a list of indexes A.

For example, if the list of words is ["time", "me", "bell"], we can write it as S = "time#bell#" and indexes = [0, 2, 5].

Then for each index, we will recover the word by reading from the reference string from that index until we reach a "#" character.

What is the length of the shortest reference string S possible that encodes the given words?

Example:

Input: words = ["time", "me", "bell"]
Output: 10
Explanation: S = "time#bell#" and indexes = [0, 2, 5].
Note:

1 <= words.length <= 2000.
1 <= words[i].length <= 7.
Each word has only lowercase letters.

*/



class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        Trie trie;
        for(auto &i: words) reverse(i.begin(), i.end());
        trie.build(words);
        int res = 0;
        for(auto word: words){
            if(trie.isSubstr(word)) res += word.size()+1;
        }
        return res;
    }
    
    struct Trie{
        unordered_map<char, Trie*>child;
        bool isCome = false;
        
        void build(const vector<string>& words){
            for(auto word: words){
                Trie* T = this;
                //reverse(word.begin(), word.end());
                for(auto w: word){
                    if (T->child.find(w) == T->child.end())
                        T->child[w] = new Trie();
                    T = T->child[w];
                }
                //T->isLeaf = true;
            }
        }
        
        bool isSubstr(const string & word){
            Trie* T = this;
            for(auto w: word){
                T = T->child[w];
            }
            if(T->isCome) return false;
            T->isCome = true;
            return T->child.empty();
        }
        ~Trie() {
            for (auto& node : child) {
                delete node.second;
            }
        }
    };
};




class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        TrieNode *root = new TrieNode;
        vector<pair<TrieNode *, int>> leaves;
        for (auto & w : unordered_set<string> (words.begin(), words.end())) {
            TrieNode *cur = root;
            for (int i = w.length() - 1; i >= 0; --i) {
                if (cur->next.count(w[i]) == 0) cur->next[w[i]] = new TrieNode;
                cur = cur->next[w[i]];
            }
            leaves.push_back(make_pair(cur, w.length() + 1));
        }
        int res = 0;
        for (auto leaf : leaves) if ((leaf.first->next).size() == 0) res += leaf.second;
        return res;
    }
};


class TrieNode {
public:
    unordered_map<char, TrieNode *> next;
};

//先sort 只需和下一个比较
//sort 是每一位比较alphabettly, 再按长度
//比如以下是按sort 排序的 aacd, aacddd, abc, ac, 
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        for(auto &i: words) reverse(i.begin(), i.end());
        sort(words.begin(), words.end());
        int res = 0;
        for(int i=0; i<words.size(); ++i) {
            bool ok = true;
            if (i + 1 == words.size()) ok = false;
            else {
                for(int j=0; j<words[i].size(); ++j) {
                    if (j == words[i+1].size() || words[i+1][j]!= words[i][j]) {
                        ok = false;
                        break;
                    }
                }
            }
            if (!ok) res += words[i].size() + 1;
        }
        return res;
    }
};



/*
Explanation of solution
Base on @awice's idea. This solution is not my intuition but it is really simple to write, compared with Trie solution.

Build a set of words.
Iterate on all words and remove all suffixes of every word from the set.
Finally the set will the set of all encoding words.
Iterate on the set and return sum(word's length + 1 for every word in the set)
Complexity
O(NK^2) for time and 'O(NK)' for space.
It is really kind of K with K <= 7, almost ignorable.
I should have suggested for bigger 'K' cases.
I believe it will take more time for most people to solve this problem if we have a big K.


*/
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        unordered_set<string> s(words.begin(), words.end());
        for (string w : s)
            for (int i = 1; i < w.size(); ++i)
                s.erase(w.substr(i));
        int res = 0;
        for (string w : s) res += w.size() + 1;
        return res;
    }
};