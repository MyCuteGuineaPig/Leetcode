/*
336. Palindrome Pairs

Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, 
so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

Example 1:
Given words = ["bat", "tab", "cat"]
Return [[0, 1], [1, 0]]
The palindromes are ["battab", "tabbat"]
Example 2:
Given words = ["abcd", "dcba", "lls", "s", "sssll"]
Return [[0, 1], [1, 0], [3, 2], [2, 4]]
The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]

*/

/*
把words[i]的reverse 当成hash map的key

loop每个words[i]的substring: l (0,j) r(j,len))
分两个情况: 
1.  l是回字, r是map里，可以组成   map[r] + l + r (注意回字必须在中间)
2.  r是回字，l在map里, 可以组成   l + r + map[r] 
** 上面情况还要注意map的index 不能等于他自己  比如 l = "", r = "s",  map中有"s", 但map中"s" index和words[i] 一样，不可以，因为自己和自己不能组成回字

除了上面情况，还要考虑一种情况，map里有"", 然后words[i] 自己是回字，比如”abba",  map中有"", 因为上面的substring没有loop到 l是word[i], r是""的情况
if(map.find("")!= map.end() && map[""]!=i && isPal(words[i])){
    res.push_back({map[""],i});
}

*/

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        unordered_map<string,int>map;
        for(int i = 0; i<words.size(); i++)
        {
            string temp = words[i];
            reverse(temp.begin(), temp.end());
            map[temp] = i;
        }
        vector<vector<int>>res;

        for(int i = 0; i<words.size(); i++){
            for(int j = 0; j<words[i].size();j++){
                string l = words[i].substr(0,j);
                string r = words[i].substr(j);
                if(map.find(l) != map.end() && map[l]!=i   && isPal(r)) //l可以是空， r是回字， l+r + ""(map[l])
                    res.push_back({i,map[l]});
                if(map.find(r)!=map.end() && map[r]!=i && isPal(l)){ 
                    /*
                    map[r]!=i 否则比如 words[i] = s, map中也是s，不能自己和自己组pal, 
                    如果可以组，l在中间(pal在中间)，比如word = lls, map中有s, ll是pal, slls
                    */
                    res.push_back({map[r],i});
                }
            }
            if(map.find("")!= map.end() && map[""]!=i && isPal(words[i])){
                res.push_back({map[""],i});
            }
        }
        return res;    
    }

    bool isPal(const string& s){
        int i = 0, j = s.size()-1;
        while(i<j){
            if(s[i++]!=s[j--]) return false;
        }
        return true;
    }
};




// Time:  O(n * k^2), n is the number of the words, k is the max length of the words.
// Space: O(n * k)
// Trie solution.


/*

Trie, 存入words的reverse  比如 'ab', suffix trie就是 'ba'
    ''
    |
    'a'
      \
      'b'
每个Trie, 有三个数据，一个是index, 一个是palList, 一个是children
index: 存的words中有在当前trie结束的words，比如['ba'], a的index = 0, 因为ab是list第一个word
palList: 存的是接下来的child trie可以组成回字，比如 'abcddc', 在b的palList,存入'abcddc'的index,表示b后面的('cddc')可以构成回字
        存它的好处是: 方便检测trie中一部分和当前words[i]成回字，另一部分自成回字(来自pallist),trie中只选取一部分，把它构成回字。
        比如 'sl',  trie中的是 'slabba'(原来的词是'abbals') slabbals 可以构成回字。
children： 是子trie的map, 比如['ba'], a的children中含有表示b的trie
* 注意： Trie的顶点是“”, 这是方便检测比如 “ABBA" 和 “”, 如果有的话，直接push 顶点的index 进结果

解法；
 1. 上来先构建trie, 每过一点需要看是不是接下来的点构成回字，if so, 加入pallist
 2. -- loop每个word[i]，先对比trie map顶点有没有index（因为顶点有index，表示words里有“”），
    -- 接下来loop 每个word[i] 如果有trie, 且当前trie是某个word的结束点,就判断当前words[i]的后面是不是回字，比如word[i] = "zyabba",  trie是 "zy"(原来word是'yz')
        如果都满足，append(i, trie.index)
    -- 如果当前word[i] 没有trie，代表字母没有出现，就return function
 3. 如果loop word[i]结尾，还没找到，但是当前trie 后面有回字, 比如words[i] = 'abc', 到结尾了, trie是 'abcyyy' (原来是'yyycba')， append(trie.index, i)


*/

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> res;
        TrieNode trie;
        for (int i = 0; i < words.size(); ++i) {
            trie.insert(words[i], i);
        }
        for (int i = 0; i < words.size(); ++i) {
            trie.search(words[i], i, res);
        }
        return res;
    }

private:
    struct TrieNode{
        int index;
        vector<int>palList;
        unordered_map<char,TrieNode*>children;

        TrieNode(){
            index = -1;
        }
        
        void insert(const string& word, int index){
            auto pt = this;
            for(int i = word.size()-1; i>=0;i--){
                if(pt->children.find(word[i]) == pt->children.end()) pt->children[word[i]] = new TrieNode();
                if(isPal(word, 0, i)) pt->palList.push_back(index);
                pt = pt->children[word[i]];
            }
            pt->palList.push_back(index);
            pt->index = index;
        }

        void search(const string& word, int index, vector<vector<int>>&res){
            auto pt = this;
            for(int i = 0; i<word.size(); i++){
                if(pt->index >= 0 && pt->index != index && isPal(word, i, word.size()-1)) //对比是 word[i-1]点 和trie，如果trie有index,并且 word[i:]是回字
                    res.push_back({index, pt->index}); //比如  'abcyzy', trie是'abc'
                if(pt->children.find(word[i]) == pt->children.end()) return;
                pt = pt->children[word[i]];
            }
            for(auto j: pt->palList) //比如  'abc', trie是'abcyzy', 
                if(j!=index){
                    res.push_back({index, j});
                }

        }


        bool isPal(const string& word, int i, int j){
            while(i<j)
                if(word[i++]!=word[j--]) return false;
            return true;
        }
    };
};
