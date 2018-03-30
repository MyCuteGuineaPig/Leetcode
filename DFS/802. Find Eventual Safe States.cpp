/*
802. Find Eventual Safe States

In a directed graph, we start at some node and every turn, walk along a directed edge of the graph.  
If we reach a node that is terminal (that is, it has no outgoing directed edges), we stop.

Now, say our starting node is eventually safe if and only if we must eventually walk to a terminal node.  
More specifically, there exists a natural number K so that for any choice of where to walk, 
we must have stopped at a terminal node in less than K steps.

Which nodes are eventually safe?  Return them as an array in sorted order.

The directed graph has N nodes with labels 0, 1, ..., N-1, where N is the length of graph.  
The graph is given in the following form: graph[i] is a list of labels j such that (i, j) is a directed edge of the graph.

Example:
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Here is a diagram of the above graph.

Illustration of graph

*/

class Solution {
public: 
    
    vector<int>visited;
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        visited.resize(graph.size(),-1); //-1 is unvisited, 0 visited (state undetermined), 1 cannot reach terminal 2 can reach terminal 
        for(int i = 0; i<graph.size();i++){
            if(visited[i] == -1){
               dfs(graph, i);
            }  
        }
        vector<int>res;
        for(int i = 0; i<graph.size();i++)
            if(visited[i] == 2)
                res.push_back(i);
        return res;
    }


    void dfs(vector<vector<int>>& graph, int cur){ //return true if reach terminal else false
        if(graph[cur].size()==0){
            visited[cur] = 2; 
            return;
        }
        else visited[cur] = 0;
        bool terminate = false;
        for(auto i: graph[cur]){
            if(visited[i] == -1)
                dfs(graph, i);
            if(visited[i] == 2)
                terminate = true;
            else if(visited[i] != 2){
                visited[cur] = 1;
                break;
            }
        }
        if(visited[cur]!=1 && terminate) visited[cur] = 2;
    }
};


class Solution {
public: 
    
    vector<int>visited;
    vector<int>res;
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        visited.resize(graph.size(),-1); //-1 is unvisited, 0 visited (unsafe), 1 safe
        for(int i = 0; i<graph.size();i++){
            if(dfs(graph,i)){
              res.push_back(i);
            }  
        }
        return res;
    }


    bool dfs(vector<vector<int>>& graph, int cur){ //return true if reach terminal else false
        if(visited[cur]!=-1) return visited[cur] == 1;
        visited[cur] = 0;
        for(auto i: graph[cur])
            if(!dfs(graph,i))
                return false;
        return visited[cur] =1 ;
    }
};