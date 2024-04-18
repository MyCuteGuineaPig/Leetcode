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