class Solution {
public:
    struct Trie{
        unordered_map<int, Trie*>t;
        long long count = 0;
    };
    long long countPrefixSuffixPairs(vector<string>& words) {
        Trie* cur = new Trie;
        long long res = 0;
        for(auto w: words){
            int n = w.size();
            Trie* tmp = cur;
            for(int i = 0; i<n; ++i){
                int key = (w[i] - 'a')*128 + (w[n-i-1] - 'a');
                tmp = tmp->t.insert({key, new Trie()}).first->second;
                res += tmp->count;
            }
            tmp->count+=1;
        }
        return res;
    }
};

class Solution {
public:
    struct Trie{
        unordered_map<int, Trie*>t;
        long long count = 0;
    };
    long long countPrefixSuffixPairs(vector<string>& words) {
        Trie* cur = new Trie;
        long long res = 0;
        for(auto w: words){
            int n = w.size();
            Trie* tmp = cur;
            for(int i = 0; i<n; ++i){
                int key = (w[i] - 'a')*128 + (w[n-i-1] - 'a');
                if (tmp->t.count(key) == 0){
                    tmp->t[key] = new Trie();
                }
                tmp = tmp->t[key];
                res += tmp->count;
            }
            tmp->count+=1;
        }
        return res;
    }
};


//1LL 表示 1 是long long 
class Solution {
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        unordered_map<int64_t, int>freq;
        long long mod = (long long)1e17 + 3;
        long long res = 0;
        for(auto& w: words){
            long long lhash = 0, rhash = 0, pow = 1; 
            int n = w.size();
            for(int i = 0; i<n; ++i){
                lhash = (lhash * 27 + (1LL + (w[i]-'a'))) % mod;
                rhash = ((1LL + (w[n-i-1]-'a'))*pow + rhash) % mod;
                pow = pow * 27 % mod;
                if (lhash == rhash && freq.count(lhash)){
                    res += freq[lhash];
                }
            }
            ++freq[lhash];
        }
        return res;
    }
};