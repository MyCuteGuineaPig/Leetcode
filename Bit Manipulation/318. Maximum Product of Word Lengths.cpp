/*
318. Maximum Product of Word Lengths

Given a string array words, find the maximum value of length(word[i]) * length(word[j]) 
where the two words do not share common letters. You may assume that each word will contain only lower case letters. 
If no such two words exist, return 0.

Example 1:

Input: ["abcw","baz","foo","bar","xtfn","abcdef"]
Output: 16 
Explanation: The two words can be "abcw", "xtfn".
Example 2:

Input: ["a","ab","abc","d","cd","bcd","abcd"]
Output: 4 
Explanation: The two words can be "ab", "cd".
Example 3:

Input: ["a","aa","aaa","aaaa"]
Output: 0 
Explanation: No such pair of words.

*/

/*
因为每个字母都是小写，可以用bit代表，比如a是第一位被set，z是第26位被set,
如果两个数 bitand 为0，代表两个数没有交集，字母没有交集

*/

class Solution {
public:
    int maxProduct(vector<string>& words) {
        if(words.empty()) return 0;
        vector<int>len(words.size());
        for(int i = 0; i<words.size(); i++){
            for(auto j: words[i]){
                len[i] |= 1<<(j-'a');
            }
        }
        int res = 0;
        for(int i = 0; i<words.size()-1;i++){
            for(int j = i+1; j<words.size();j++){
                if((len[i] & len[j]) == 0 && words[i].size()*words[j].size() > res){
                    res = words[i].size()*words[j].size();
                }
            }
        }
        return res;
    }
};


class Solution {
public:
    int maxProduct(vector<string>& words) {
        unordered_map<int,int> maxlen;
        int result = 0;
        for (string word : words) {
            int mask = 0;
            for (char c : word)
                mask |= 1 << (c - 'a');
            maxlen[mask] = max(maxlen[mask], (int) word.size());
            for (auto maskAndLen : maxlen)
                if (!(mask & maskAndLen.first))
                    result = max(result, (int) word.size() * maskAndLen.second);
        }
        return result;
    }
};

// Time:  O(n) ~ O(n^2)
// Space: O(n)

// Counting Sort + Pruning + Bit Manipulation
class Solution {
public:
    int maxProduct(vector<string>& words) {
        words = counting_sort(words);
        vector<int> bits(words.size());
        for (int i = 0; i < words.size(); ++i) {
            for (const auto& c : words[i]) {
                bits[i] |= (1 << (c - 'a'));
            }
        }
        int max_product = 0;
        for (int i = 0; i + 1 < words.size() && pow(words[i].length(), 2) > max_product; ++i) {
            for (int j = i + 1; j < words.size() && words[i].length() * words[j].length() > max_product; ++j) {
                if (!(bits[i] & bits[j])) {
                    max_product = words[i].length() * words[j].length();
                }
            }
        }
        return max_product;
    }

    vector<string> counting_sort(const vector<string>& words) {
        const int k = 1000;  // k is max length of words in the dictionary
        vector<vector<string>> buckets(k);
        for (const auto& word : words) {
            buckets[word.length()].emplace_back(word);
        }
        vector<string> res;
        for (int i = k - 1; i >= 0; --i) {
            if (!buckets[i].empty()) {
                move(buckets[i].begin(), buckets[i].end(), back_inserter(res));
            }
        }
        return res;
    }
};

// Time:  O(nlogn) ~ O(n^2)
// Space: O(n)
// Sorting + Pruning + Bit Manipulation
class Solution {
public:
    int maxProduct(vector<string>& words) {
        sort(words.begin(), words.end(), [](const string& a, const string& b) { return a.length() > b.length(); });
        vector<int> bits(words.size());
        for (int i = 0; i < words.size(); ++i) {
            for (const auto& c : words[i]) {
                bits[i] |= (1 << (c - 'a'));
            }
        }
        int max_product = 0;
        for (int i = 0; i + 1 < words.size() && pow(words[i].length(), 2) > max_product; ++i) {
            for (int j = i + 1; j < words.size() && words[i].length() * words[j].length() > max_product; ++j) {
                if (!(bits[i] & bits[j])) {
                    max_product = words[i].length() * words[j].length();
                }
            }
        }
        return max_product;
    }
};