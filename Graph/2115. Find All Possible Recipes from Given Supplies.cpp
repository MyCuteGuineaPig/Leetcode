class Solution {
public:
    void dfs(unordered_map<string, unordered_set<string>>&graph,  unordered_map<string, int>&degree, const string& cur){
        if(graph.count(cur) == 0)
            return;
        for(auto & parent: graph[cur]){
            degree[parent]-= 1;
            if (degree[parent] == 0){
                dfs(graph, degree, parent);
            }
        }
    }

    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        int n = recipes.size();
        unordered_map<string, unordered_set<string>>graph;
        unordered_map<string,int>degree;
        for(int i = 0; i < recipes.size(); ++i){
            for(auto & ingredient: ingredients[i]){
                graph[ingredient].insert(recipes[i]);
            }
            degree[recipes[i]] += ingredients[i].size();
        }
        for(int i = 0; i < supplies.size(); ++i){
            dfs(graph, degree, supplies[i]);
        }
        vector<string>res;
        for(auto it: degree){
            if(it.second == 0)
                res.push_back(it.first);
        }
        return res;
    }
};


class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        int n = recipes.size();
        unordered_map<string, unordered_set<string>>graph;
        unordered_map<string,int>degree;
        for(int i = 0; i < recipes.size(); ++i){
            for(auto & ingredient: ingredients[i]){
                graph[ingredient].insert(recipes[i]);
            }
            degree[recipes[i]] += ingredients[i].size();
        }
        queue<string>q;
        for(auto & s: supplies){
            q.push(s);
        }
        while(!q.empty()){
            string cur = q.front(); q.pop();
            for(auto parent: graph[cur]){
                if(--degree[parent]==0){
                    q.push(parent);
                }
            }
        }
        vector<string>res;
        for(auto it: degree){
            if(it.second == 0)
                res.push_back(it.first);
        }
        return res;
    }
};



class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        unordered_map<string, unordered_set<string>>graph;
        unordered_map<string, int>degree;
        int n = recipes.size();
        for(int i = 0; i < n; ++i){
            for(auto& ing: ingredients[i]){
                graph[ing].insert(recipes[i]);
            }
            degree[recipes[i]] = ingredients[i].size();
        }
        vector<string>res;
        for(auto sup: supplies){
            for(auto& nxt: graph[sup]){
                if(--degree[nxt] == 0) {
                    res.push_back(nxt);
                }
            }
        }
        for(int i = 0; i < res.size(); ++i){
            string cur = res[i];
            for(auto& nxt: graph[cur]){
                if(--degree[nxt] == 0) {
                    res.push_back(nxt);
                }
            }
        }
        return res;
    }
};


//DFS
class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        unordered_map<string, unordered_set<string>>graph;
        unordered_map<string, int>degree;
        int n = recipes.size();
        for(int i = 0; i < n; ++i){
            for(auto& ing: ingredients[i]){
                graph[ing].insert(recipes[i]);
            }
            degree[recipes[i]] = ingredients[i].size();
        }
        vector<string>res; 

        auto dfs = [&](this auto&& dfs, const string& cur)->void{
            for(auto& nxt: graph[cur]){
                if(--degree[nxt] == 0){
                    res.push_back(nxt);
                    dfs(nxt);
                }
            }
        };
        for(auto& sup: supplies)
            dfs(sup);
        return res;
    }
};



//BFS 

class Solution {
public:
    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        unordered_map<string, unordered_set<string>>graph;
        unordered_map<string, int>degree;
        int n = recipes.size();
        for(int i = 0; i < n; ++i){
            for(auto& ing: ingredients[i]){
                graph[ing].insert(recipes[i]);
            }
            degree[recipes[i]] = ingredients[i].size();
        }
        vector<string>res; 
        queue <string> q; 
        for(auto& sup: supplies)
            q.push(sup);
        while(!q.empty()){
            string cur = q.front(); q.pop(); 
            for(auto& nxt: graph[cur]){
                if(--degree[nxt] == 0) {
                    res.push_back(nxt);
                    q.push(nxt);
                }
            }
        } 
        return res;
    }
};