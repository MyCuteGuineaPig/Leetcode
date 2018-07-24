/*
648. Replace Words

In English, we have a concept called root, which can be followed by some other words to form another longer word - 
let's call this word successor. For example, the root an, followed by other, which can form another word another.

Now, given a dictionary consisting of many roots and a sentence. 
You need to replace all the successor in the sentence with the root forming it. 
If a successor has many roots can form it, replace it with the root with the shortest length.

You need to output the sentence after the replacement.

Example 1:
Input: dict = ["cat", "bat", "rat"]
sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"
Note:
The input will only have lower-case letters.
1 <= dict words number <= 1000
1 <= sentence words number <= 1000
1 <= root length <= 100
1 <= sentence words length <= 1000

*/



/*

注意Trie， 把child 和leave 弄成public 否则没办法access


*/
class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        Trie trie;
        trie.insert(dict);
        string res;
        size_t j;
        //j = sentence.find_first_of(' ', 1);
        for(int i = 0; i<sentence.size(); i++){
            if(sentence[i]!=' '){
                if((j = sentence.find_first_of(' ', i)) == string::npos) 
                    j = sentence.size();
                string temp = sentence.substr(i, j-i);
                int len = trie.find(temp);
                res += temp.substr(0,len);
                i = j -1;
            }
            else res+=sentence[i];    
        }
        return res;
    }
    
    
    class Trie{
    public:
        unordered_map<char, Trie*>child;
        bool isleaf;
        Trie(){
            isleaf = false;
        }
        
        void insert(const vector<string>& dict){
            for(auto word: dict){
                Trie *T = this;
                for(auto i: word){
                    if(T->child.find(i) == T->child.end())
                        T->child[i] = new Trie();
                    T = T->child[i];
                }
                T->isleaf = true;
            }
        }
        
        int find(const string& word){
            Trie *T = this;
            int i = 0;
            for(;i<word.size(); i++){
                if(T->child.find(word[i]) == T->child.end())
                    i = word.size();
                else{
                    T = T->child[word[i]];
                    if(T->isleaf) return i+1;
                }
            }

            return i;
        }
    };
};



class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        TrieNode trie;
        string result;
        for (const auto& s : dict) {
            trie.Insert(s);
        }
        auto curr = &trie;
        for (const auto& c : sentence) {
            if (c == ' ' || !curr || !curr->isString) {
                result += c;
            }
            if (c == ' ') {
                curr = &trie;
            } else if (curr && !curr->isString) {
                curr = curr->leaves[c];
            }
        }

        /*
        
        stringstream str(sentence);
        string s;

        while(getline(str, s, ' ')) {
            rt += (rt.size()?" ":"") + find(s, trie);
        }
        return rt;       
        
        */
        return result;
    }

private:
    struct TrieNode {
        bool isString = false;
        unordered_map<char, TrieNode *> leaves;
        
        void Insert(const string& s) {
            auto* p = this;
            for (const auto& c : s) {
                if (p->leaves.find(c) == p->leaves.cend()) {
                    p->leaves[c] = new TrieNode;
                }
                p = p->leaves[c];
            }
            p->isString = true;
        }
        
        ~TrieNode() {
            for (auto& kv : leaves) {
                if (kv.second) {
                    delete kv.second;
                }
            }
        }
    };
};



/*
把dict 中每个word的首字母做成key
缺点是可能所有单词首字母都一样，但后面全不一样
*/
class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        string res = "", t= "";
        vector<vector<string>> v(26);
        sort(dict.begin(), dict.end(), [](string& a, string& b){
            return a.size() <b.size();
        });
        istringstream is(sentence);
        for(string word: dict){
            v[word[0]-'a'].push_back(word);
        }
        while(is >> t){
            for(string word : v[t[0]-'a']){
                if(t.substr(0, word.size()) == word) {
                
                    t = word;
                    break;
                } 
            }
            res += t+" ";
        }
        res.pop_back();
        return res;
    }
};