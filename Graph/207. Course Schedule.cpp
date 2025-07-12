/*
207. Course Schedule

Time	Space	Difficulty
O(|V| + |E|)	O(|E|)	Medium

There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.

2, [[1,0],[0,1]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

Note:
The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.

注意： 判断in out degree, loop through n次，如果还degree 有一次不是0，则返回有

*/

class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>>graph(numCourses,vector<int>());
        vector<int>degree(numCourses,0);
        for(int i = 0; i<prerequisites.size();i++){
            graph[prerequisites[i].first].push_back(prerequisites[i].second);
            degree[prerequisites[i].second]++;//in degree
        }

        for(int i = 0; i<numCourses;i++){
            for(int j = 0; j<numCourses; j++){
                if(degree[j]==0){
                    degree[j] = -1;
                    for(int k = 0; k<graph[j].size(); k++)
                        degree[graph[j][k]]--;
                    break;
                }
                else if(j == numCourses-1)
                    return false;                    
            }
        }
        return true;
    }
};


class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& pre) {
        vector<int>indegree(numCourses); 
        int n = numCourses;
        unordered_map<int,unordered_set<int>>graph;
        for(int i = 0; i < pre.size(); ++i){
            ++indegree[pre[i][0]];
            graph[pre[i][1]].insert(pre[i][0]);
        }
        queue<int>q;
        int points = 0;
        for(int i = 0; i <n; ++i){
            if(indegree[i] == 0) {
                //cout<<" cur "<<i<<endl;
                q.push(i);
                ++points;
            }
        }
        while(!q.empty() && points <= n){
            int cur = q.front(); q.pop();
            for(auto nxt: graph[cur]){
                if(--indegree[nxt] == 0) {
                    q.push(nxt);
                    ++points;
                }
            }
        }
        return points == n;
    }
};



class Solution {
public:
    bool canFinish(int n, vector<vector<int>>& pre) {
        vector<vector<int>>graph(n);
        for(auto i: pre){
            graph[i[0]].push_back(i[1]);
        }
        vector<int>visited(n);
        vector<int>on_path(n);
        auto detect_cycle = [&](this auto&& detect_cycle, int cur)->bool{
            /*
            需要on_path(n);

            比如  
               1 -> 2 -> 3 
                         ^
                         |
                    4 -- 
               如果 1 -> 2 ->3 发现没有cycle, 再到4 开始， If(visited[3]) return true, wrong
             */
            if(on_path[cur])
                return true;
            if(visited[cur]){
                return false;
            }
            on_path[cur] = 1;
            visited[cur] = 1;
            for(auto nxt: graph[cur]){
                if(detect_cycle(nxt)) return true;
            }
            on_path[cur] = 0;
            return false;
        };
        for(int i = 0; i < n; ++i){
            if(detect_cycle(i)) return false;
        }
        return true;
    }
};