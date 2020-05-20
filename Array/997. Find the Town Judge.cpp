/**
Consider trust as a graph, all pairs are directed edge.
    The point with in-degree - out-degree = N - 1 become the judge.

如果有两个judge, in-degree - out-degree != N -1 
比如 
    [[1,3],[2,3],[3,2],[1,2]], 3的indegree 2, outdegree = 1,  2-1 = 1
 */

class Solution {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
        unordered_set<int>judge;
        for(int i = 1; i<=N; i++)
            judge.insert(i);
        unordered_map<int,unordered_set<int>>mp;
        for(auto t: trust){
            judge.erase(t[0]);
            mp[t[1]].insert(t[0]);
        }
        if(judge.size() != 1 || mp[*judge.begin()].size() != N-1)
            return -1;
        return *judge.begin();
    }
};


class Solution {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
        vector<int> degrees(N);
        for (const auto& t : trust) {
            --degrees[t[0] - 1];
            ++degrees[t[1] - 1];
        } 
        for (int i = 0; i < degrees.size(); ++i) {
            if (degrees[i] == N - 1) {
                return i + 1;
            }
        }
        return -1;
    }
};


class Solution {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
    vector<int> trusts(N + 1), trusted(N + 1);
    for (auto &t : trust) ++trusts[t[0]], ++trusted[t[1]];
    for (auto i = 1; i <= N; ++i) if (trusts[i] == 0 && trusted[i] == N - 1) return i;
    return -1;
    }
};