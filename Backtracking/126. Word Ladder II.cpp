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





//2020 
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        if(find(wordList.begin(), wordList.end(), endWord) == wordList.end())
            return {};
	    
        unordered_map<int, unordered_set<int>>mp;            
        int endIndex = -1;  
        
        for(int  i = 0; i<wordList.size(); ++i){
            if(isOneDiff(wordList[i], beginWord))
                mp[wordList.size()].insert(i);
		
            for(int j = i+1; j<wordList.size(); ++j){
                if(isOneDiff(wordList[i], wordList[j])){
                    mp[i].insert(j);
                    mp[j].insert(i);
                }
                if (endIndex== -1 && wordList[i] == endWord) endIndex = i; 
                else if(endIndex== -1 && wordList[j] == endWord) endIndex = j;
            }
        }     
        vector<int>visited(wordList.size()+1,0);
        vector<vector<int>>res; 
	    
        queue<pair<int, vector<int>>>q; 
        q.push({wordList.size(),{wordList.size()}});
	    
        while(res.empty() && !q.empty() && q.front().second.size() < wordList.size()){
		//q.front().second.size() < wordList.size(), 让queue 的size 小于dictionary size, 大于不可能有结果
            int size = q.size();
            unordered_set<int>curwords; //没有这个, 会TLE
            for(int i = 0; i<size; ++i){
                auto top = q.front();
                curwords.insert(top.first);
                q.pop();
                for(auto i: mp[top.first]){
                       top.second.push_back(i);
                        if(i == endIndex)
                            res.push_back(top.second);
                        else
			    q.push({i, top.second});
                    top.second.pop_back();
                }
            }
            for(auto i: curwords)//这一轮之后 不会再用到这些word, 用不到这些word了，如果再用, 需要round 也是更多
                mp.erase(i);
	    
	    
        return buildResult(res,wordList, beginWord);
    }



    vector<vector<string>> buildResult(const vector<vector<int>>&res, const vector<string>& wordList, const string& beginWord){
        vector<vector<string>> resStr; 
        for(int i = 0; i<res.size(); ++i){
            resStr.push_back({beginWord});
            
            for(int j = 1 ; j <res[i].size(); ++j)
                resStr.back().push_back(wordList[res[i][j]]);
        }
        return resStr;
    }  


    bool isOneDiff(const string& a, const string&b){
        int diff = 0;
        for(int i = 0; i<a.size(); ++i){
            if (a[i] != b[i]){
                if(diff) return false;
                diff = 1;
            }
        }
        return diff == 1; 
    }
};

	
	
	
	
	
	
//Two-end BFS 
//2020

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        if(find(wordList.begin(), wordList.end(), endWord) == wordList.end()){
            return {};
        }

        unordered_map<int, unordered_set<int>>mp;            
        int endIndex = -1;  
        
        for(int  i = 0; i<wordList.size(); ++i){
            if(isOneDiff(wordList[i], beginWord)){
                mp[wordList.size()].insert(i);
            }
            for(int j = i+1; j<wordList.size(); ++j){
                if(isOneDiff(wordList[i], wordList[j])){
                    mp[i].insert(j);
                    mp[j].insert(i);
                }
                if (endIndex== -1 && wordList[i] == endWord) endIndex = i; 
                else if(endIndex== -1 && wordList[j] == endWord) endIndex = j;
            }
        }     
        vector<vector<int>>res; 
        unordered_multimap<int,vector<int>>begindict = {{wordList.size(), {wordList.size()}}};
        unordered_multimap<int,vector<int>>enddict = {{endIndex, {endIndex}}};
/*

需要unordered_multimap，可能到这个word, 有多个路径
比如 d : a-> b ->c -> d,  d: a->c->b->d 


unordered_multimap: 记住不能用 []获取值，也不能用[] insert 值,
获取值，需要用equal_range
*/	    

	    
        if(twoEndedBFS(begindict, enddict, mp, res, true))
            return buildResult(res,wordList, beginWord);
        return {};
    }


    bool twoEndedBFS(unordered_multimap<int,vector<int>>&begindict, unordered_multimap<int,vector<int>>&enddict, 
    unordered_map<int, unordered_set<int>>& mp, vector<vector<int>>&res, bool isBegin){
        if(begindict.empty())
            return false;
        if(begindict.size() < enddict.size())
            return twoEndedBFS(begindict, enddict, mp, res, !isBegin);

        unordered_set<int>  this_round;//没有this_round, 删除路径, TLE
        unordered_multimap<int, vector<int>>next;

        for(auto itBegin : begindict){
            this_round.insert(itBegin.first);

            for(auto nxt: mp[itBegin.first]){
                auto itendFind = enddict.equal_range(nxt);
                for(auto itend = itendFind.first; itend != itendFind.second; ++itend){
                    vector<int>& endPath = itend->second;
                    auto beginPath = itBegin.second;
                    
                    reverse(endPath.begin(),endPath.end()); 
                    copy(endPath.begin(), endPath.end(), back_inserter(beginPath));
                    if(!isBegin)
                        reverse(beginPath.begin(), beginPath.end());
                    res.push_back(beginPath);
                }
                itBegin.second.push_back(nxt);
                next.insert({nxt,  itBegin.second});
                itBegin.second.pop_back();
            }
        }

        for(auto cur: this_round)
            mp.erase(cur);
        return !res.empty() || twoEndedBFS(next, enddict, mp, res, isBegin);
    }



    vector<vector<string>> buildResult(const vector<vector<int>>&res, const vector<string>& wordList, const string& beginWord){
        vector<vector<string>> resStr; 
        for(int i = 0; i<res.size(); ++i){
            resStr.push_back({beginWord});
            
            for(int j = 1 ; j <res[i].size(); ++j){
                //cout<<" res[i][j] "<<res[i][j]<<endl;
                resStr.back().push_back(wordList[res[i][j]]);
            }
        }
        return resStr;
    }  


    bool isOneDiff(const string& a, const string&b){
        int diff = 0;
        for(int i = 0; i<a.size(); ++i){
            if (a[i] != b[i]){
                if(diff) return false;
                diff = 1;
            }
        }
        return diff == 1; 
    }
    
};
