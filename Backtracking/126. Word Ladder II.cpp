/*
126. Word Ladder II

Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from 
beginWord to endWord, such that:

Only one letter can be changed at a time
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]
Return
  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]

*/

class Solution {
public:
    unordered_map<string,unordered_set<string>>parent;
    
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>>res;
        queue<string>q;
        unordered_set<string>wordlist(wordList.begin(), wordList.end());
        if(wordlist.find(endWord) == wordlist.end())
            return res;
        q.push(beginWord);
        bool has = false;
        int count = 0;
        while(q.size()>0 && !has){
            int cursize = q.size();
            count ++;
            for(int i = 0; i<cursize; i++){
                string top = q.front();  
                wordlist.erase(top);
                for(auto itr = top.begin();itr!=top.end();itr++){
                    char o = *(itr);
                    for(int j = 0; j<26; j++){
                        *(itr) = 'a'+j;
                        if(*(itr)!=o){
                            if(wordlist.find(top)!=wordlist.end() && parent[top].find(q.front())==parent[top].end()){
                                if(top==endWord) has = true;
                                parent[top].insert(q.front());
                                if(!has) q.push(top);
                            }
                        }
                    }
                    *itr = o;
                }
                 q.pop();
            }
            if(has) {
                deque<string>cur={endWord};
                getPath(res,cur,beginWord,endWord, count);
            }
        }
        return res;
    }
    
    void getPath(vector<vector<string>>& res, deque<string>& cur, const string& beginWord, string curword, int count){
        if(count<0) return;
        if(curword == beginWord){
            res.push_back(vector<string>(cur.begin(),cur.end()));
            return;
        }
        for(auto itr: parent[curword]){
            //cout<<" begin "<<curword<<" itr " <<itr <<" count "<<count<<endl;;
            cur.push_front(itr);
            getPath(res,cur,beginWord,itr,count-1);
            cur.pop_front();
        }
        
    }
};


/**
 * 
 * TWo end BFS
 * 
*/

class Solution {
public:
    std::vector<std::vector<std::string> > findLadders(std::string beginWord, std::string endWord, std::unordered_set<std::string> &dict) {
		std::vector<std::vector<std::string> > paths;
		std::vector<std::string> path(1, beginWord);
		if (beginWord == endWord) {
			paths.push_back(path);
			return paths;
		}
        std::unordered_set<std::string> words1, words2;
		words1.insert(beginWord);
		words2.insert(endWord);
		std::unordered_map<std::string, std::vector<std::string> > nexts;
		bool words1IsBegin = false;
        if (findLaddersHelper(words1, words2, dict, nexts, words1IsBegin))
			getPath(beginWord, endWord, nexts, path, paths);
		return paths;
    }
private:
    bool findLaddersHelper(
		std::unordered_set<std::string> &words1,
		std::unordered_set<std::string> &words2,
		std::unordered_set<std::string> &dict,
		std::unordered_map<std::string, std::vector<std::string> > &nexts,
		bool &words1IsBegin) {
		words1IsBegin = !words1IsBegin;
		if (words1.empty())
            return false;
		if (words1.size() > words2.size())
			return findLaddersHelper(words2, words1, dict, nexts, words1IsBegin);
		for (auto it = words1.begin(); it != words1.end(); ++it)
			dict.erase(*it);
		for (auto it = words2.begin(); it != words2.end(); ++it)
			dict.erase(*it);
        std::unordered_set<std::string> words3;
		bool reach = false;
        for (auto it = words1.begin(); it != words1.end(); ++it) {
			std::string word = *it;
			for (auto ch = word.begin(); ch != word.end(); ++ch) {
				char tmp = *ch;
                for (*ch = 'a'; *ch <= 'z'; ++(*ch))
					if (*ch != tmp)
						if (words2.find(word) != words2.end()) {
							reach = true;
							words1IsBegin ? nexts[*it].push_back(word) : nexts[word].push_back(*it);
						}
						else if (!reach && dict.find(word) != dict.end()) {
							words3.insert(word);
							words1IsBegin ? nexts[*it].push_back(word) : nexts[word].push_back(*it);
                        }
				*ch = tmp;
            }
        }
        return reach || findLaddersHelper(words2, words3, dict, nexts, words1IsBegin);
    }
	void getPath(
		std::string beginWord,
		std::string &endWord,
		std::unordered_map<std::string, std::vector<std::string> > &nexts,
		std::vector<std::string> &path,
		std::vector<std::vector<std::string> > &paths) {
		if (beginWord == endWord)
			paths.push_back(path);
		else
			for (auto it = nexts[beginWord].begin(); it != nexts[beginWord].end(); ++it) {
				path.push_back(*it);
				getPath(*it, endWord, nexts, path, paths);
				path.pop_back();
			}
	}
};