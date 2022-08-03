class Solution {
public:
    void dfs(const vector<int>&edges, int cur, int cnt, vector<int>&mp, unordered_set<int>&visited){
        if (visited.count(cur))
            return;
        visited.insert(cur);
        mp[cur] = cnt;
        if (edges[cur] == -1)
            return;
        dfs(edges,edges[cur], cnt+1, mp,visited);
    }
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        vector<int>dist1 (edges.size(), -1);
        vector<int>dist2 (edges.size(), -1); 
        unordered_set<int>visited;
        dfs(edges, node1, 0, dist1, visited);
        visited.clear();
        dfs(edges, node2, 0, dist2, visited);
        int min_dist = numeric_limits<int>::max();
        int res = -1;
        for(int i = 0; i<edges.size(); ++i){
            if (min(dist1[i], dist2[i]) >= 0 && max(dist1[i], dist2[i]) < min_dist) {
                min_dist = max(dist1[i], dist2[i]);
                res = i;
            }
        }
        return res;
    }
};

class Solution {
public:
    void dfs(int i, int dist, vector<int>& e, vector<int>& memo) {
        while (i != -1 && memo[i] == -1) {
            memo[i] = dist++;
            i = e[i];
        }
    }
    int closestMeetingNode(vector<int>& e, int node1, int node2) {
        int res = -1, min_dist = INT_MAX;
        vector<int> m1(e.size(), -1), m2(e.size(), -1);
        dfs(node1, 0, e, m1);
        dfs(node2, 0, e, m2);
        for (int i = 0; i < e.size(); ++i)
            if (min(m1[i], m2[i]) >= 0 && max(m1[i], m2[i]) < min_dist) {
                min_dist = max(m1[i], m2[i]);
                res = i;
            }
        return res;
    }
};



class Solution {
public:
    int closestMeetingNode(vector<int>& e, int node1, int node2) {
        int res = -1, min_dist = INT_MAX;
        vector<int> m1(e.size(), -1), m2(e.size(), -1);
        for (int i = node1, dist = 0; i != -1 && m1[i] == -1; i = e[i])
            m1[i] = dist++;
        for (int i = node2, dist = 0; i != -1 && m2[i] == -1; i = e[i]) {
            m2[i] = dist++;
            if (m1[i] >= 0 && max(m1[i], m2[i]) <= min_dist) {
                res = max(m1[i], m2[i]) == min_dist ? min(i, res) : i;
                min_dist = max(m1[i], m2[i]);
            }
        }
        return res;
    }
};


//BFS
class Solution {
public:
    int closestMeetingNode(vector<int>& e, int n1, int n2) {
        auto bfs=[&](int src, vector<int> &dist,vector<int>& edge,int n){
            queue<int> q;
            q.push(src);
            dist[src]=0;
            while(q.size()>0){
                auto p= q.front(); q.pop();
                if(edge[p]!=-1 and dist[edge[p]]==INT_MAX){
                   q.push(edge[p]);  
                   dist[edge[p]]= dist[p]+1;
                }
            }
        };
        int n= e.size();
        vector<int> A(n,INT_MAX), B(n,INT_MAX);
        bfs(n1,A,e,n);   bfs(n2,B,e,n);
        int res= INT_MAX, node=-1;
        for(int i=0;i<n;i++){
            if(A[i]==INT_MAX or B[i]==INT_MAX) continue;
            if(res>max(A[i],B[i])) node=i,res= max(A[i],B[i]);
        }
        return node;
    }
};