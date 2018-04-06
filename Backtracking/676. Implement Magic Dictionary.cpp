
/*
676. Implement Magic Dictionary

Implement a magic directory with buildDict, and search methods.

For the method buildDict, you'll be given a list of non-repetitive words to build a dictionary.

For the method search, you'll be given a word, and judge whether if you modify exactly one character into another character in this word,
 the modified word is in the dictionary you just built.

Example 1:
Input: buildDict(["hello", "leetcode"]), Output: Null
Input: search("hello"), Output: False
Input: search("hhllo"), Output: True
Input: search("hell"), Output: False
Input: search("leetcoded"), Output: False
Note:
You may assume that all the inputs are consist of lowercase letters a-z.
For contest purpose, the test data is rather small by now. You could think about highly efficient algorithm after the contest.
Please remember to RESET your class variables declared in class MagicDictionary, as static/class variables are persisted across 
multiple test cases. Please see here for more details.

*/


class MagicDictionary {
public:
	/** Initialize your data structure here. */
	MagicDictionary() {

	}

	/** Build a dictionary through a list of words */
	void buildDict(vector<string> dict) {
		map.insert(dict.begin(), dict.end());
	}

	/** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
	bool search(string word) {
		for (int i = 0; i < word.size(); i++) {
			for (int j = 0; j <= 25; j++){
				if (word[i] == 'a' + j) continue;
				char k = word[i];
				word[i] = 'a' + j;
				if (map.count(word) > 0) return true;
				word[i] = k;
			}
		}
		return false;
	}

	unordered_set<string>map;
};



/**
 * 
 * instead search every chars from A-Z, search hello as *ello, h*llo
 * /

class MagicDictionary {
public:
	/** Initialize your data structure here. */
	MagicDictionary() {

	}

	/** Build a dictionary through a list of words */
	void buildDict(vector<string> dict) {
		map.insert(dict.begin(), dict.end());
        for(auto word: dict){
            int len = word.size();
            for(int i = 0; i<len; i++){
                char ch = word[i];
                word[i] = '*';
                transform[len][word]++;
                word[i] = ch;
            }
        }
	}

	/** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
	bool search(string word) {
		int len = word.size();
        if(transform.count(len)==0 ) return false;
        for(int i = 0; i<len; i++){
            string tword = word;
            tword[i] = '*';
            if(transform[len].find(tword)!=transform[len].end() && (transform[len][tword]>1 || transform[len][tword]==1 && map.count(word)==0)) return true;
        }
		return false;
	}

	unordered_set<string>map;
    unordered_map<int,unordered_map<string,int>>transform;
};


/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary obj = new MagicDictionary();
 * obj.buildDict(dict);
 * bool param_2 = obj.search(word);
 */