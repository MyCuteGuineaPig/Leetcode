class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        vector<unordered_set<int>>courses(n+1);
        for(auto &r: relations){
            courses[r[1]].insert(r[0]);
        }
        unordered_map<int, int>cnt; 
        function<int(int)> dfs = [&](int next){
            if (cnt.count(next))
                return cnt[next];
            if(courses[next].empty())
                return 1;
            
            int cur = -1;
            cnt[next] = -1;
            for(auto pre: courses[next]){
                int num_courses = dfs(pre);
                if(num_courses == -1) 
                    return -1;
                cur = max(cur, num_courses+1);
            }
            return cnt[next] = cur;
        };
        for(int i = 1; i<=n; ++i){
            if(dfs(i) == -1) return -1;
        }
        int res = -1;
        for(auto & it: cnt){
            res = max(res, it.second);
        }
        return res;
    }
};

class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        vector<unordered_set<int>>courses(n+1);
        for(auto &r: relations){
            courses[r[1]].insert(r[0]);
        }
        vector<int>cnt(n+1);
        function<int(int)> dfs = [&](int next){
            if (cnt[next]!=0)
                return cnt[next];
            if(courses[next].empty())
                return 1;
            
            int cur = -1;
            cnt[next] = -1;
            for(auto pre: courses[next]){
                int num_courses = dfs(pre);
                if(num_courses == -1) 
                    return -1;
                cur = max(cur, num_courses+1);
            }
            return cnt[next] = cur;
        };
        for(int i = 1; i<=n; ++i){
            if(dfs(i) == -1) return -1;
        }
        return *max_element(cnt.begin()+1, cnt.end());
    }
};



class Solution {
public:
	int minimumSemesters(int N, vector<vector<int>>& relations) {
        vector<int> indegree(N, 0);
        vector<set<int>> g(N);
        for (auto& v : relations) {
            g[v[0] - 1].insert(v[1] - 1);
            indegree[v[1] - 1]++;
        }
        int maxDepth = 0, numStudied = 0;
        queue<pair<int, int>> q; // vertex, depth
        for (int i = 0; i < N; i++) if (indegree[i] == 0) q.push({ i,1 });
        for (; !q.empty(); numStudied++) {
            auto [i, depth] = q.front(); q.pop();
            maxDepth = depth;
            for (auto j : g[i]) if (--indegree[j] == 0) q.push({ j, depth + 1 });
        }
        return numStudied == N ? maxDepth : -1;
    }
};

class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        vector<unordered_set<int>>courses(n+1);
        vector<int>in_degree(n+1, 0);
        for(auto &r: relations){
            courses[r[0]].insert(r[1]);
            ++in_degree[r[1]];
        }
        //如果有循环的，有的indegree不会是0,比如
        // 1->2, 2->3, 3->1, 4->5, 1,2,3 indgree都不是0
        /*
        再比如  
                1
                | 
                v
                2    到达2后不会再process, 因为只有1->2 但到2后 indgree 是1 (2-1 = 1), 
             /   ^          indegree 不是0, 不会push进q
           v      \
           3 ->   4
        */
        queue<int>q;
        unordered_set<int>visited;
        for(int i = 1; i<=n;++i){
            if(in_degree[i] == 0)
                q.push(i);
        }
        int semster = 0;
        while (!q.empty()){
            int size = q.size();
            for(int a = 0; a < size; ++a){
                auto top = q.front(); q.pop();
                --n; //n-1 发生因为 indegree[top] == 0
                for(auto next: courses[top]){
                    if (--in_degree[next] == 0){
                        q.push(next);
                    }
                }
            }
            semster += 1;
        }
        return n  == 0? semster: -1;
    }
};