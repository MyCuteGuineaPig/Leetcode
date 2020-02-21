/*
399. Evaluate Division

Time	    Space	Difficulty
O(q * |V|!)	O(e)	Medium

Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.

Example:
Given a / b = 2.0, b / c = 3.0. 
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? . 
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.

According to the example above:

equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 
The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.



*/


class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string,vector<pair<string,double>>>graph;
        for(int i = 0; i<equations.size(); i++){
            graph[equations[i].first].push_back({equations[i].second,values[i]});
            if(values[i]!=0) graph[equations[i].second].push_back({equations[i].first,1/values[i]});
        }
        vector<double>res;
        for(int i = 0; i<queries.size(); i++){
            unordered_map<string,bool>visited;
            double temp = -1;
            if(graph.find(queries[i].first)!= graph.end() && graph.find(queries[i].second)!= graph.end() )
                dfs(graph,visited, queries[i].first, queries[i].second, 1, temp);
            res.push_back(temp);
        }
        return res;
    }
    
    /*
    val is the number divided till now
    now is the cur for this round DFS search
    end is the end of char in queries
    res is used to store result
    */
    void dfs(unordered_map<string,vector<pair<string,double>>>& graph, unordered_map<string,bool>& visited, string now, string end, double val, double& temp ){
        visited[now] = true;
        if(now == end) 
            temp = val;
        for(int i = 0; i<graph[now].size() && temp == -1; i++){
            if(!visited[graph[now][i].first])
                dfs(graph,visited, graph[now][i].first, end, val*graph[now][i].second ,temp);
        }
    }
};





//write by own
class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string, unordered_map<string, double>>mp;
        for(int i = 0; i<equations.size(); i++){
            string a = equations[i].first, b = equations[i].second;
            double val = values[i];
            mp[a][b] = val;
            mp[b][a] = 1/val;
        }
        vector<double>res;
        for(auto i: queries){
            unordered_set<string>visited;
            res.push_back(helper(mp,i.first, i.second, visited)); // a / a 是通过 a/b * b/a 算得
        }
        return res;
    }
    
    double helper(unordered_map<string, unordered_map<string, double>>& mp, string in, string out, unordered_set<string>& visited){
        if(mp.find(in) == mp.end()) return -1;
        if( mp[in].find(out) != mp[in].end()) 
            return mp[in][out];
        for(auto i: mp[in]){
            if(visited.find(i.first)!=visited.end()) continue;
            visited.insert(i.first);
            double res = helper(mp, i.first, out, visited);
            if(res!=-1)
                return i.second *res;
        }
        return -1;
    }
};


class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, 
        vector<double>& values, vector<pair<string, string>> query) 
    {
        unordered_map<string,unordered_map<string, double>> m;
        vector<double> res;
        for (int i = 0; i < values.size(); ++i)
        {
            m[equations[i].first].insert(make_pair(equations[i].second,values[i]));
            if(values[i]!=0)
                m[equations[i].second].insert(make_pair(equations[i].first,1/values[i]));
        }

        for (auto i : query)
        {
            unordered_set<string> s;
            double tmp = check(i.first,i.second,m,s);
            if(tmp) res.push_back(tmp);
            else res.push_back(-1);
        }
        return res;
    }

    double check(string up, string down, 
            unordered_map<string,unordered_map<string, double>> &m,
            unordered_set<string> &s)
    {
        if(m[up].find(down) != m[up].end()) return m[up][down];
        for (auto i : m[up])
        {
            if(s.find(i.first) == s.end())
            {
                s.insert(i.first);
                double tmp = check(i.first,down,m,s);
                if(tmp) return i.second*tmp;
            }
        }
        return 0;
    }
};



class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string,vector<pair<string,double>>>graph;
        for(int i = 0; i<equations.size(); i++){
            graph[equations[i].first].push_back({equations[i].second,values[i]});
            graph[equations[i].second].push_back({equations[i].first,1/values[i]});
        }
        vector<double>res;
        for(int i = 0; i<queries.size(); i++){
            unordered_map<string,bool>visited;
            double temp = dfs(graph,visited, queries[i].first, queries[i].second);
            if (temp) res.push_back(temp);
            else res.push_back(-1);
        }
        return res;
    }
    
    /*
    val is the number divided till now
    now is the cur for this round DFS search
    end is the end of char in queries
    res is used to store result
    */
    double dfs(unordered_map<string,vector<pair<string,double>>>& graph, unordered_map<string,bool>& visited, string now, string end){
        visited[now] = true;
        for(int i = 0; i<graph[now].size(); i++){
            if(graph[now][i].first == end ) return graph[now][i].second;
            if(!visited[graph[now][i].first]){
                 double temp = dfs(graph,visited, graph[now][i].first, end);
                 if(temp) return temp*graph[now][i].second;
            }
        }
        return 0;
    }
};



//Union Find
/*

Union 就是给数赋值过程 

Case 1: 两个都不在map 
 a / b = 5 =>    a = 5, b = 1,    a parent ->  b
 x / y = 8; =>   x = 8, y = 1,    x parent -> y
Case 2: 第二个不在map 
 a / c = 4 =>    a = 5, c = 1.25   c->parent -> a
Case 3: 第一个不在map 
 d / c = 10  =>   d = 12.5,  c = 1.25,  d->parent = c 
Case 4: 两个都在 Union 
    c / x = 10  
    c parent = b,  x->parent  = y, ratio = x * 10 / c = 8 * 10 / 1.25 = 64 
    如果 parent = b,  乘上这个ratio 
           a = 5 * 64 = 320
           b = 1 * 64 = 64
           c = 1.25 * 64 = 80
           d = 12.5 * 64 = 800


*/
class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        unordered_map<string, Node*> map;
        vector<double> res;
        for (int i = 0; i < equations.size(); i ++) {
            string s1 = equations[i].first, s2 = equations[i].second;
            if (map.count(s1) == 0 && map.count(s2) == 0) {
                map[s1] = new Node();
                map[s2] = new Node();
                map[s1] -> value = values[i];
                map[s2] -> value = 1;
                map[s1] -> parent = map[s2];
            } else if (map.count(s1) == 0) {
                map[s1] = new Node();
                map[s1] -> value = map[s2] -> value * values[i];
                map[s1] -> parent = map[s2];
            } else if (map.count(s2) == 0) {
                map[s2] = new Node();
                map[s2] -> value = map[s1] -> value / values[i];
                map[s2] -> parent = map[s1];
            } else {
                unionNodes(map[s1], map[s2], values[i], map);
            }
        }

        for (auto query : queries) {
            if (map.count(query.first) == 0 || map.count(query.second) == 0 || findParent(map[query.first]) != findParent(map[query.second]))
                res.push_back(-1);
            else
                res.push_back(map[query.first] -> value / map[query.second] -> value);
        }
        return res;
    }
    
private:
    struct Node {
        Node* parent;
        double value = 0.0;
        Node()  {parent = this;}
    };
    
    void unionNodes(Node* node1, Node* node2, double num, unordered_map<string, Node*>& map) {
        Node* parent1 = findParent(node1), *parent2 = findParent(node2);
        double ratio = node2 -> value * num / node1 -> value;
        //cout<<"ratio "<<ratio<<endl;
        for (auto it = map.begin(); it != map.end(); it ++)
            if (findParent(it -> second) == parent1)
                it -> second -> value *= ratio;
            
        parent1 -> parent = parent2;
    }
    
    Node* findParent(Node* node) {
        if (node -> parent == node)
            return node;
        node -> parent = findParent(node -> parent);
        return node -> parent;
    }
};
