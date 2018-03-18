/*
127. Word Ladder

Time	Space	Difficulty
O(n * d)	O(d)	Medium	

Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
UPDATE (2017/1/20):
The wordList parameter had been changed to a list of strings (instead of a set of strings). Please reload the code definition to get the latest changes.



*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string>unused(wordList.begin(),wordList.end());
        queue<string>toVisit;
        int dist = 1;
        addWord(toVisit,beginWord,unused);
        while(toVisit.size()){
            int cursize = toVisit.size();
            for(int i = 0; i<cursize;i++){
                string top = toVisit.front();
                if(top == endWord) return dist+1;
                toVisit.pop();
                addWord(toVisit,top,unused);
            }
            dist++;
        }
        return 0;
    }

    void addWord(queue<string>& toVisit, string word, unordered_set<string>& unused){
        for(int j = 0; j<word.length(); j++){  
            for(int i = 0; i<26; i++){
                string cur = word;
                char at = 'a'+i;
                if(at != word[j]){
                    cur[j] = at;
                    if(unused.count(cur)>0){
                        unused.erase(cur);
                        toVisit.push(cur);
                    }
                }
            }
        }
    }
};

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& worddict) {
        unordered_set<string>head, tail, *phead, *ptail;
        unordered_set<string>wordDict(worddict.begin(),worddict.end());
        head.insert(beginWord);
        if(wordDict.count(endWord)>0)
            tail.insert(endWord);
        int dist = 2;
        while(head.size() && tail.size()){
            if(head.size()<tail.size()){
                phead = &head;
                ptail = &tail;
            }else{
                phead = &tail;
                ptail = &head;
            }
        unordered_set<string>temp;
        for(auto itr = phead->begin(); itr!= phead->end(); itr++){
            string word = *itr;
            wordDict.erase(word);
            for(int p = 0; p<word.length(); p++){
                char letter = word[p];
                for(int k = 0; k<26; k++){
                    word[p] = 'a'+k;
                    if(ptail->count(word)>0)
                        return dist; 
                    if(wordDict.count(word)>0)
                    {
                        temp.insert(word);
                        wordDict.erase(word);
                    }
                }
                word[p] = letter;
            }
        }
        dist++;
        swap(*phead, temp);
        }
        return 0;
    }
};