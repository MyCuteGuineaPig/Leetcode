/*
30. Substring with Concatenation of All Words

You are given a string, s, and a list of words, words, 
that are all of the same length. 
Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

Example 1:

Input:
  s = "barfoothefoobarman",
  words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoor" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.
Example 2:

Input:
  s = "wordgoodstudentgoodword",
  words = ["word","student"]
Output: []

*/


//最快的解
// Time:  O((m + n) * k), m is the length of the string,
//                        n is the size of the dictionary,
//                        k is the length of each word
// Space: O(n * k)

// Sliding window solution. windows size: 一直保持n*k个, 如果现在windows中substr的个数大于count的中的个数，window向右移动

/*
k = 每个word的长度
n = 整个words dictionary的长度
m = S的长度

用string 作为key, count dictionary, 
然后从S的0位置开始，外层是k，起始位置是0,1,2,...,k
内层是每次jump k个, j表示每次substring 都是以s[j]开始的
  如果words不含有当前的substr
    -  如果当前的substr, 不在words 里面，前进左面的开始点left = j + k， count = 0; window map清空
  如果含有当前的substr
    -  如果window含有的substr个数小于words的个数，count++
    -  如果window含有当前的substr大于words的个数，把左面开始点left每次移动k，清空之前在windows map的string，直到
    当前的substring 小于等于words中的数  比如"barfoofoothebar ["foo","bar"，"the"] 当j = 9时，重复了foo,直到left = 9, foo，count(foo) = 1, 减了两回，还要加一回

    -- 当count == word。size(), res.push_back(left), left前进k个，count --，count不清零是因为可能现在点是上个的结束，也可能是下个window的中间
       比如"barfoothefoobar ["foo","bar"，"the"], 中间的the既是第一个的结束，又是第二个的开始
       res = [0,6]

*/

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if(s.empty() || words.empty()) return {};
        vector<int> result;
        const int m = s.length();
        const int n = words.size();
        const int k = words.front().length();
        if (m < n * k) {
            return result;
        }

        unordered_map<string, int> lookup;
        for (const auto& word : words) {
            ++lookup[word];                        // Space: O(n * k)
        }
        for (int i = 0; i < k; ++i) {              // Time:  O(k)
            int left = i, count = 0;
            unordered_map<string, int> tmp;
            for (int j = i; j <= m - k; j += k) {  // Time:  O(m / k)
                const auto& str = s.substr(j, k);  // Time:  O(k)
                if (lookup.count(str)) {
                    ++tmp[str];
                    if (tmp[str] <= lookup[str]) { 
                        ++count;
                    } else {
                        while (tmp[str] > lookup[str]) {
                            const auto& str1 = s.substr(left, k);
                            --tmp[str1];
                            --count;
                            left += k;
                        }
                        count++; //loop到temp 比str多的时候，加1，加的1是现在substring的1
                        //"barfoofoothefoobarman"  ["foo","bar"，"the"]，left到index 6, ++count是加foo(6-9)
                    }
                    if (count == n) {
                        result.emplace_back(left);
                        --tmp[s.substr(left, k)];
                        --count;//注意是count-1
                        left += k;
                    }
                } else {//现在substring都诶出现
                    tmp.clear();
                    count = 0;
                    left = j + k;
                }
            }
        }
        return result;
    }
};

//不固定window size, 用cnt来比较 words.size()
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string, int>wordss;
        for(auto& w: words) wordss[w]++;
        vector<int> res;
        int k = words[0].size();
        for(int start = 0; start<k; ++start){
            int cnt = 0;
            unordered_map<string, int>mp;
            for(int i = start; i<s.size(); i+=k){
                string ss = s.substr(i, k);
                if(wordss.count(ss) == 0){
                    mp.clear();
                    cnt = 0;
                    continue;
                }
                while(mp[ss] == wordss[ss]){
                    int l = i - cnt * k;
                    mp[s.substr(l, k)]--;
                    --cnt;
                }
                mp[ss]++;
                ++cnt;
                if(cnt  == words.size())
                    res.push_back(i-(words.size()-1)*k);
            }
        }
        return res;
    }
};

//不固定window size, 用l 
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string, int>wordss;
        for(auto& w: words) wordss[w]++;
        vector<int> res;
        int k = words[0].size();
        for(int start = 0; start<k; ++start){
            unordered_map<string, int>mp;
            int l = start;
            for(int i = start; i<s.size(); i+=k){
                string ss = s.substr(i, k);
                if(wordss.count(ss) == 0){
                    mp.clear();
                    l = i+k;
                    continue;
                }
                while(mp[ss] == wordss[ss]){
                    mp[s.substr(l, k)]--;
                    l += k;
                }
                mp[ss]++;
                if(i - l  == (words.size()-1)*k)
                    res.push_back(i-(words.size()-1)*k);
            }
        }
        return res;
    }
};


//Sliding wndows: 固定windows size
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if(words.size()==0 || s.empty()) return {};
        unordered_map<string,int>lookup;
        for(auto word: words)
            lookup[word]++;
        int size = s.size(), word_len = words[0].size(), len = words.size();
        vector<int>res;
        for(int j = 0; j<word_len; j++){
            unordered_map<string, int>mp;
            for(int i = j, cnt = words.size(); i<=size - word_len; i+= word_len){
                string cur = s.substr(i,word_len);
                if(lookup.count(cur) && ++mp[cur] <= lookup[cur]) 
                    --cnt;
                if(cnt==0) res.push_back(i-word_len*(len-1));
                if(i-j >= word_len*(len-1) ){
                    string before = s.substr(i-word_len*(len-1), word_len);
                    if(lookup.count(before) && --mp[before] < lookup[before] )
                        ++cnt;
                }
            }
        }
        return res;
    }
};


//Sliding windows 不固定windows size 
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if(s.empty() || words.empty()) return {};
        int size = s.size(), wlen = words[0].size(), len = words.size();
        unordered_map<string, int>lookup;
        for(auto word: words) lookup[word]++;
        vector<int>res;
        for(int j = 0; j<wlen; j++){
            unordered_map<string, int>mp;
            for(int i = j, left = j; i<= size - wlen; i+=wlen){
                string cur = s.substr(i, wlen);
                mp[cur]++;
                if(lookup.count(cur) == 0 || mp[cur] > lookup[cur])
                {
                    while(left <= i && (lookup.count(cur) == 0 || mp[cur] > lookup[cur]))
                    {
                        string before = s.substr(left, wlen);
                        mp[before]--;
                        left += wlen;
                    }
                }
                if(i-left == wlen*(len-1)) res.push_back(left);   
            }
        }
        return res;
    }
};




//不太优化的解
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if(s.empty() || words.empty()) return {};
        int totalLen = words[0].size()*words.size();
        int len = words[0].size();
        if(totalLen > s.size()) return {};
        vector<int> res;
        unordered_map<string,int>counts;
        for(auto i : words)
            counts[i]++;
        for(int i = 0; i<s.length()-totalLen+1; i++){
            unordered_map<string,int>seen;
            for(int j = 0; j<words.size();j++){
                string temp = s.substr(i+j*len,len);
                seen[temp]++;
                if(counts.count(temp)==0 || seen[temp]>counts[temp])
                   break;
                if(j==words.size()-1)
                    res.push_back(i);
            }
            
        }
        return res;
    }
};


// Time:  O((m - n * k) * n * k) ~ O(m * n * k), m is the length of the string,
//                                               n is the size of the dictionary,
//                                               k is the length of each word
// Space: O(n * k)
class Solution2 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        const auto word_length = words.front().length();
        const auto cat_length = word_length * words.size();
        vector<int> result;

        if (s.length() < cat_length) {
            return result;
        }

        unordered_map<string, int> wordCount;
        for (const auto & word : words) {
            ++wordCount[word];
        }

        for (auto it = s.begin(); it != prev(s.end(), cat_length - 1); ++it) {
            unordered_map<string, int> unused(wordCount);
            for (auto jt = it; jt != next(it, cat_length); jt += word_length) {
                auto pos = unused.find(string(jt, next(jt, word_length)));
                if (pos == unused.end()) {
                    break;
                }
                if (--pos->second == 0) {
                    unused.erase(pos);
                }
            }
            if (unused.empty()) {
                result.emplace_back(distance(s.begin(), it));
            }
        }
        return result;
    }
};




class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if(s.empty() || words.empty()) return {};
        int n = s.size(), m = words.size(), k = words[0].size();
        if(n < k*m) return {};
        vector<int>res;
        unordered_map<char,int>map;
        unordered_map<string,int>dict;
        for(int i = 0; i<m; i++){
            dict[words[i]]++;
            for(int j = 0; j<k; j++)
                map[words[i][j]]++;
        }
        
        int count = 0;
        for(int i = 0; i<s.size();i++){
            if(map[s[i]]-- > 0) count++;
            if(count == m*k){
                int start = i - m*k+1;
                unordered_map<string,int>temp;
                for(int j = start;j<=i; j+= k){
                    string cur = s.substr(j,k);
                    if(dict.count(cur) == 0 || ++temp[cur] > dict[cur]) {
                        break;
                    }
                    if(j == i-k+1) res.push_back(start);
                }
            }
            if(i>=m*k-1){
                if(++map[s[i-m*k+1]]>0) count--;
            }
        }
        return res;
    }
};

//用char unordered_map 超慢的,因为multiset的加和删
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if(s.empty() || words.empty()) return {};
        unordered_map<char,int>map_word;
        unordered_map<char,int>map_s;
        int slen = words[0].size(), len = words.size()*slen;
        vector<int>res;
        for(int i = 0; i<words.size(); i++){
            for(int j = 0; j<slen; j++)
                map_s[words[i][j]]++;
        }
        for(int i = 0; i<s.size();i++){
            map_word[s[i]]++;
            if(i>=len-1){
                int start = i - len+1;
                if(map_word == map_s){
                    unordered_multiset<string>dict(words.begin(),words.end());
                    for(int j = start;j<=i; j+= slen){
                        if(dict.count(s.substr(j,slen))) dict.erase(dict.find(s.substr(j,slen)));
                        else break;
                    }
                    if(dict.empty()) res.push_back(start);
                }
                map_word[s[start]]--;
                if(map_word[s[start]] == 0) map_word.erase(s[start]);
            }
        }
        return res;
    }
};



//Hash Solution
class Solution {
// The general idea:
// Construct a hash function f for L, f: vector<string> -> int, 
// Then use the return value of f to check whether a substring is a concatenation 
// of all words in L.
// f has two levels, the first level is a hash function f1 for every single word in L.
// f1 : string -> double
// So with f1, L is converted into a vector of float numbers
// Then another hash function f2 is defined to convert a vector of doubles into a single int.
// Finally f(L) := f2(f1(L))
// To obtain lower complexity, we require f1 and f2 can be computed through moving window.
// The following corner case also needs to be considered:
// f2(f1(["ab", "cd"])) != f2(f1(["ac", "bd"]))
// There are many possible options for f2 and f1. 
// The following code only shows one possibility (probably not the best), 
// f2 is the function "hash" in the class,
// f1([a1, a2, ... , an]) := int( decimal_part(log(a1) + log(a2) + ... + log(an)) * 1000000000 )
public:
    // The complexity of this function is O(nW).
    double hash(double f, double code[], string &word) {
        double result = 0.;
        for (auto &c : word) result = result * f + code[c];
        return result;
    }
    vector<int> findSubstring(string S, vector<string> &L) {
        uniform_real_distribution<double> unif(0., 1.);
        default_random_engine seed;
        double code[128];
        for (auto &d : code) d = unif(seed);
        double f = unif(seed) / 5. + 0.8;
        double value = 0;

        // The complexity of the following for loop is O(L.size( ) * nW).
        for (auto &str : L) value += log(hash(f, code, str));

        int unit = 1e9;
        int key = (value-floor(value))*unit;
        int nS = S.size(), nL = L.size(), nW = L[0].size();
        double fn = pow(f, nW-1.);
        vector<int> result;
        if (nS < nW) return result;
        vector<double> values(nS-nW+1);
        string word(S.begin(), S.begin()+nW);
        values[0] = hash(f, code, word);

        // Use a moving window to hash every word with length nW in S to a float number, 
        // which is stored in vector values[]
        // The complexity of this step is O(nS).
        for (int i=1; i<=nS-nW; ++i) values[i] = (values[i-1] - code[S[i-1]]*fn)*f + code[S[i+nW-1]];

        // This for loop will run nW times, each iteration has a complexity O(nS/nW)
        // So the overall complexity is O(nW * (nS / nW)) = O(nS)
        for (int i=0; i<nW; ++i) {
            int j0=i, j1=i, k=0;
            double sum = 0.;

            // Use a moving window to hash every L.size() continuous words with length nW in S.
            // This while loop will terminate within nS/nW iterations since the increasement of j1 is nW,
            // So the complexity of this while loop is O(nS / nW).
            while(j1<=nS-nW) {
                sum += log(values[j1]);
                ++k;
                j1 += nW;
                if (k==nL) {
                    int key1 = (sum-floor(sum)) * unit;
                    if (key1==key) result.push_back(j0);
                    sum -= log(values[j0]);
                    --k;
                    j0 += nW;
                }
            }
        }
        return result;
    }
};
