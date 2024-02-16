/*

785. Is Graph Bipartite?.cpp

Time	        Space	Difficulty
O(|V| + |E|)	O(|V|)	Medium

Given an undirected graph, return true if and only if it is bipartite.

Recall that a graph is bipartite if we can split it's set of nodes into two independent subsets A and B such that every edge in the graph has one node in A and another node in B.

The graph is given in the following form: graph[i] is a list of indexes j for which the edge between nodes i and j exists.  Each node is an integer between 0 and graph.length - 1.  There are no self edges or parallel edges: graph[i] does not contain i, and it doesn't contain any element twice.

Example 1:
Input: [[1,3], [0,2], [1,3], [0,2]]
Output: true
Explanation: 
The graph looks like this:
0----1
|    |
|    |
3----2
We can divide the vertices into two groups: {0, 2} and {1, 3}.
Example 2:
Input: [[1,2,3], [0,2], [0,1,3], [0,2]]
Output: false
Explanation: 
The graph looks like this:
0----1
| \  |
|  \ |
3----2
We cannot find a way to divide the set of nodes into two independent subsets.
 

Note:

graph will have length in range [1, 100].
graph[i] will contain integers in range [0, graph.length - 1].
graph[i] will not contain i or duplicate values.
The graph is undirected: if any element j is in graph[i], then i will be in graph[j].


*/



/*
note:

Our goal is trying to use two colors to color the graph and see if there are any adjacent nodes having the same color.
Initialize a color[] array for each node. Here are three states for colors[] array:
-1: Haven't been colored.
0: Blue.
1: Red.
For each node,

If it hasn’t been colored, use a color to color it. Then use another color to color all its adjacent nodes (DFS).
If it has been colored, check if the current color is the same as the color that is going to be used to color it. (Please forgive my english… Hope you can understand it.)


*/


//DFS + Bit Mask
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int>dp(graph.size());
        for(int i = 0; i<graph.size(); ++i)
            if(!dp[i] && !dfs(graph, dp, 1, i)) //!dp[i] has not visited before
                return false;
        return true;
    }
    //两种颜色, 1 和 2
    bool dfs(const vector<vector<int>>& graph, vector<int>&dp, int color, int index){
        if(dp[index])
            return dp[index] & color;
        dp[index] = color; 
        for(auto next: graph[index])
            if(!dfs(graph, dp, 3 ^ color, next))  //3 ^ color, 3 ^ 1 = 2, 3 ^ 2 = 1
                return false;
        return true;
    }
};
/*
DFS
*/
//write by own
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<int>color(graph.size(), -1);
        for(int i = 0; i<graph.size(); i++){
            if(color[i] ==-1 && !helper(graph, 1, i, color)) return false;
        }
        return true;
    }
    
    bool helper(vector<vector<int>>& graph, int c, int start, vector<int>& color){
        color[start] = c;
        for(auto p : graph[start]){
            if(color[p]!=-1 && !(color[start] ^ color[p]) || color[p]==-1 && !helper(graph, 1-c, p, color)) return false;
        }
        return true;
    }
};

class Solution {
public:
    vector<int>color;
    int n;
    bool isBipartite(vector<vector<int>>& graph) {
        n = graph.size();
        color.resize(n,-1);

        for(int i = 0; i<n; i++){
            if(color[i]== -1 && !isvalid(graph,i,1)) return false;
        }
        return true;
    }

    bool isvalid(vector<vector<int>>& graph, int i, int c){
        color[i] = c;
        for(int j = 0; j<graph[i].size();j++){
            int cur = graph[i][j];
            if(color[cur] != -1 && color[cur] != 1 - c ) return false;
            else if(color[cur] == -1 && !isvalid(graph,cur,1-c)) return false;
        }
        return true;
    }
};



class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int size = graph.size();
        vector<int>color(size,-1);
        int c = 1;
        for(int i = 0; i<size; i++){
            if(color[i] == -1){
                queue<int>q; q.push(i);
                color[i] = c;
                while(q.size()){
                    int cursize = q.size();
                    for(int j = 0; j<cursize; j++){
                        int front = q.front(); q.pop();
                        for(auto p: graph[front]){
                            if(color[p] == color[front]) return false;
                            if(color[p]==-1){
                                color[p] = 1-c;
                                q.push(p);
                            }
                        }
                    }
                    c = 1- c;
                }
            }

        }
        return true;
    }
};

/*
Java BFS
*/
class Solution {
    public boolean isBipartite(int[][] graph) {
        //BFS
        // 0(not meet), 1(black), 2(white)
        int[] visited = new int[graph.length];
        
        for (int i = 0; i < graph.length; i++) {
            if (graph[i].length != 0 && visited[i] == 0) {
                visited[i] = 1;
                Queue<Integer> q = new LinkedList<>();
                q.offer(i);
                while(! q.isEmpty()) {
                    int current = q.poll();
                    for (int c: graph[current]) {

                            if (visited[c] == 0) {
                                visited[c] = (visited[current] == 1) ? 2 : 1;
                                q.offer(c);
                            } else {
                                if (visited[c] == visited[current]) return false;
                            }
                    }
                }                        
                
            }
        }
        
        return true;
    }
}
