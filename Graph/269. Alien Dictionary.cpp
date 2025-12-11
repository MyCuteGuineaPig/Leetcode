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
                    //比如 c->p 已经insert到Indegree 了
                    // 但是因为大小关系，需要break
                    if(graph[c].count(p) == 0){ //可能有多个 c -> p, 但是degree 只算一次
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




class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, unordered_set<char>>graph;
        unordered_map<char, int> visited;
        unordered_map<char, int> on_path;

        for(auto w: words)
            for(auto i: w){
                visited[i] = 0;
                on_path[i] = 0;
            }
for(int i = 0; i < words.size() - 1; ++i){
            int size = min(words[i].size(), words[i+1].size());
            for(int k = 0; k< size; ++k){
                char s1 = words[i][k], s2 = words[i+1][k];
                if(s1!=s2) {
                    if (graph[s1].count(s2) == 0){
                        graph[s1].insert(s2);
                    }
                    break;
                } else if (k == size - 1 && words[i].size() > words[i+1].size()) {
                    //like 'ab' is before 'a'
                    return "";
                }
            }
        }

        string res = "";
        auto find_cycle = [&](this auto&& find_cycle, int cur, int parent) -> bool {
            visited[cur] = 1;
            on_path[cur] = 1;
            for(auto & nxt: graph[cur]){
                if(!visited[nxt]) {
                    if(find_cycle(nxt, cur)) {
                        return true;
                    }
                } else if(on_path[nxt]) 
                    return true;
            }
            res += cur;
             on_path[cur] = 0;
            return false;
        };  

        for(auto c: visited){
            if(visited[c.first] == 0) {
                if (find_cycle(c.first, -1)) {
                    return "";
                }
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};