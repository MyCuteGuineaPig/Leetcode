/*
["z","x","a","zb","zx"]

degree:
    b, 0
    a, 1
    x, 2
    z, 1

*/

class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char,unordered_set<char>>graph;
        unordered_map<char, int>degree;
        for(auto word: words)
            for(auto letter: word)
                degree[letter] = 0;
        
        for(int i = 0; i< words.size()-1; ++i){
            int len = min(words[i].size(), words[i+1].size());
            for(int j = 0; j<len; ++j){
                char c = words[i][j];
                char p = words[i+1][j];
                if(c != p){
                    if(graph[c].count(p) == 0){
                        graph[c].insert(p);
                        degree[p]++;
                    }
                    break;
                }
                else if (j == len - 1 and words[i].size() > words[i+1].size()) return ""; // ["abc","ab"] return ""
            }
        }
        queue<char>q;
        for(auto it: degree)
            if(it.second == 0)
                q.push(it.first);
        string res;
        while(q.size()){
            char c = q.front(); q.pop();
            res +=  c;
            for(auto next: graph[c]){
                if(--degree[next] == 0) 
                    q.push(next);
            }
        }
        return res.size() == degree.size() ? res: "";
    }
};