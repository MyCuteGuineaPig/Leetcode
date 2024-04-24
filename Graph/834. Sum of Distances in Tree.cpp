class Solution {
public:
    vector<unordered_set<int>>graph;
    vector<int>count;//count 表示以i 为root 的subtree count(且包括点i)
    vector<int>res;

    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        graph.resize(n);
        count.resize(n, 1);
        res.resize(n);
        for(auto & e: edges){
            graph[e[0]].insert(e[1]);
            graph[e[1]].insert(e[0]);
        }
        dfs(0, -1);
        dfs2(0, -1);
        return res;
    }

    void dfs(int cur, int pre){ //post order
        for(auto nxt: graph[cur]){
            if(nxt == pre) continue;
            dfs(nxt, cur);
            count[cur] += count[nxt];
            res[cur] += res[nxt] + count[nxt];
            //属于nxt的res 到cur 全部增加1，总过有count[nxt]个点 => res[nxt] + count[nxt]

            //cout<<" cur "<<cur <<" count[cur] "<<count[cur] << " nxt "<<nxt<<" count[nxt] "<<count[nxt]<<" res "<<res[cur]<< " pre "<<pre<<endl;
            
        }
    }
    void dfs2(int cur, int pre){ // pre order
        for(auto &nxt: graph[cur]){
            if(nxt == pre) continue;
            res[nxt] = res[cur] - count[nxt] + count.size() - count[nxt];

            //从nxt -> root 每个以nxt为parent 点距离都加1， 从root->nxt, 减去这些点
            // 其他所有parent 不是nxt的点 从root 到nxt 距离都加1， count.size() - count[nxt]
            dfs2(nxt, cur);
        }
    }
};


class Solution {
public:
    vector<unordered_set<int>> tree;
    vector<int> res, count;

    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        tree.resize(N);
        res.assign(N, 0);
        count.assign(N, 1);
        for (auto e : edges) {
            tree[e[0]].insert(e[1]);
            tree[e[1]].insert(e[0]);
        }
        dfs(0, -1);
        dfs2(0, -1);
        return res;

    }

    void dfs(int root, int pre) {
        for (auto i : tree[root]) {
            if (i == pre) continue;
            dfs(i, root);
            count[root] += count[i];
            res[root] += res[i] + count[i];
            cout<<" root "<<root<<" i "<<i<<" count[i] "<<count[i]<<" pre "<<pre<<" pre "<< "  count[root] "<< count[root]<<" res[root]  "<<res[root] <<endl;
        }
    }

    void dfs2(int root, int pre) {
        for (auto i : tree[root]) {
            if (i == pre) continue;
            res[i] = res[root] - count[i] + count.size() - count[i];
            dfs2(i, root);
        }
    }
};