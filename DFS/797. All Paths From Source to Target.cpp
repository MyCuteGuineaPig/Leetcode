/*
797. All Paths From Source to Target


Given a directed, acyclic graph of N nodes.  Find all possible paths from node 0 to node N-1, and return them in any order.

The graph is given as follows:  the nodes are 0, 1, ..., graph.length - 1.  graph[i] is a list of all nodes j for which the edge (i, j) exists.

Example:
Input: [[1,2], [3], [3], []] 
Output: [[0,1,3],[0,2,3]] 
Explanation: The graph looks like this:
0--->1
|    |
v    v
2--->3
There are two paths: 0 -> 1 -> 3 and 0 -> 2 -> 3.
Note:

The number of nodes in the graph will be in the range [2, 15].
You can print different paths in any order, but you should keep the order of nodes inside one path.
*/

class Solution {
public:
    int n;
    //vector<int>visited;
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<int>path = {0};
        vector<vector<int>>result;
        //visited.resize(n,1);
        n = graph.size()-1;
        dfs(graph,result,path,0);
        return result;
    }

    void dfs(vector<vector<int>>& graph,vector<vector<int>>&result,vector<int>&path, int cur ){
        if(cur == n) result.push_back(path);
        for(auto p: graph[cur]){
            path.push_back(p);
            dfs(graph,result,path, p);
            path.pop_back();
        }
    }
};


class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        vector<vector<int>> res; 
        int n = graph.size(); 
        vector<bool> vstd(n, false);
        vector<int> thisRes; 
        thisRes.push_back(0);
        dfs(graph, vstd, 0, thisRes, res);
        return res;
    }
    
    void dfs(vector<vector<int>>& graph, vector<bool>& vstd, int i, vector<int>& thisRes, vector<vector<int>>& res) {
       // if (vstd[i]) return;  
        if (i == graph.size()-1) {
            res.push_back(thisRes);
            return;
        }
       // vstd[i] = true;
        for (int j = 0; j < graph[i].size(); j++) {
            thisRes.push_back(graph[i][j]);
            dfs(graph, vstd, graph[i][j], thisRes, res);   
            thisRes.pop_back(); 
        }
    }
};

/*
从结尾走到 起点,
 
 1 -> 2     如果从起点走会走两边 1->2->4->5->6, 1->3->4->5->6
 |    |     如果从结尾走，就只走一遍  6->5->4
 v    v
 3 -> 4
      |
      v
      5
      |
      v
      6
*/
class Solution {
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        if(graph.empty()) return {};
        unordered_map<int, vector<int>>my_graph;
        for(int i = 0; i<graph.size(); ++i){
            for(auto j: graph[i])
                my_graph[j].push_back(i);
        }
        vector<vector<int>> res;
        for(int i = 0; i<graph.size(); ++i){
            if(graph[i].empty()){
                vector<int>cur;
                dfs(my_graph, res, cur,i);
            }
        }
        return res;
    }
    
    void dfs(unordered_map<int, vector<int>>&my_graph, vector<vector<int>>& res, vector<int>&cur, int i){
        cur.push_back(i);
        if(my_graph.find(i) == my_graph.end())
            res.push_back(vector<int>(cur.rbegin(), cur.rend()));  
        else{
            for(int j = 0; j<my_graph[i].size(); ++j)
                dfs(my_graph, res, cur, my_graph[i][j]);   
        }
        cur.pop_back();
    }
};


using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
//-------
class Solution {
public:
	vi path;
	vector<vi> ans;
	void dfs(int u, vector<vi> &g) {
		path.pb(u);
		if (u + 1 == sz(g)) {
			ans.pb(path);
		} else {
			for (auto v : g[u])
				dfs(v, g);
		}
		path.pop_back();
	}
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    	dfs(0, graph);
    	return ans;
    }
};
