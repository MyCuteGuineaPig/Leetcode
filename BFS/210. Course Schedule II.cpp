/*
210. Course Schedule II

Time	Space	Difficulty
O(|V| + |E|)	O(|E|)	Medium

There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

For example:

2, [[1,0]]
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1]

4, [[1,0],[2,0],[3,1],[3,2]]
There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is[0,2,1,3].

Note:

The input prerequisites is a graph represented by a list of edges, not adjacency matrices. Read more about how a graph is represented.
You may assume that there are no duplicate edges in the input prerequisites.


*/


//DFS
/*
对于DFS，需要一个onpath，如果检查一个vector<bool> path，发现几个recurssion 后又回来，就发现了循环了,否则就不是循环


*/

class Solution {
public:
    vector<int>res;
    vector<bool>visited;
    vector<bool>onpath;
    vector<vector<int>>graph;

    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        graph.resize(numCourses,vector<int>());
        for(auto i: prerequisites)
            graph[i.second].push_back(i.first);
        
        visited.resize(numCourses,false);
        onpath.resize(numCourses,false);
        for(int i = 0; i<numCourses;i++){
            if(!visited[i] && !dfs(i))
                    return {};
        }
        reverse(res.begin(),res.end());
        return res;
    }

    bool dfs(int id){
        //cout<<"in "<<id<<endl;
        if(onpath[id]) return false;
        if(visited[id]) return true;
        visited[id] = onpath[id] = true;
        for(int num: graph[id])
            if(onpath[num] || !dfs(num))
                return false;
        //cout<<id<<endl;
        res.push_back(id);
        onpath[id] = false;
        return true;
    }
};


/*
BFS
先找到indegree 为0的，代表这个是课程的起点，每一个循环都push back 一个课程， 再找这个课程的所有children的indegree为0的，把他们全部push back进queue，
如果发现还没有push 进所有课程，但是queue已经空了，代表有个循环（比如A->B, B->A, A,B的in degree 不可能为0)

*/

class Solution {
public:

    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>>graph(numCourses,vector<int>());
        for(auto i: prerequisites)
            graph[i.second].push_back(i.first);
        queue<int>q;
        vector<int>degree(numCourses,0);
        vector<int>res;
        for(int i = 0; i<graph.size();i++){
            for(int j: graph[i])
                degree[j]++;
        }
        for(int i = 0; i<degree.size();i++)
            if(degree[i]==0) q.push(i);
           
        for(int i = 0; i<numCourses;i++){
            if(q.empty()) return {};
            int top = q.front();
            q.pop();
            res.push_back(top);
            for(auto k: graph[top]){
                degree[k]--;
                if(degree[k] == 0)
                    q.push(k);
            }
        }
        return res;
    }
};
