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