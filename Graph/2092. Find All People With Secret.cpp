class Solution {
public:
    
    int find(vector<int>&parents, int cur){
        return parents[cur] == cur ? cur:parents[cur]=find(parents,parents[cur]);
    }

    void join(vector<int>&parents, int x, int y){
        int px = find(parents, x);
        int py = find(parents, y);
        if (px == py) {
            return;
        }
        parents[py] = px;
    }

    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        vector<int>parents(n); 
        iota(parents.begin(), parents.end(), 0);
        join(parents, 0, firstPerson);

        sort(meetings.begin(), meetings.end(), [](vector<int>& a, vector<int>&b){return a[2] < b[2];});
        
        for(int i = 0; i < meetings.size(); ){
            unordered_set<int>persons;
            int cur_time = meetings[i][2];
            for(; i<meetings.size() && meetings[i][2] == cur_time; ++i){
                join(parents, meetings[i][0], meetings[i][1]);
                persons.insert(meetings[i][0]);
                persons.insert(meetings[i][1]);
            }

            for(auto p: persons){
                if(find(parents,p) != find(parents, 0)){
                    parents[p] = p; //reset
                }
            }
        }
        vector<int>res = {0};
        for(int i = 1; i <n; ++i){
            if(find(parents,i) == find(parents, 0))
                res.push_back(i);
        }
        return res;
    }
};



// OJ: https://leetcode.com/problems/find-all-people-with-secret/
// Author: github.com/lzl124631x
// Time:O(M⋅(logM+N))
// Space: O(M + N). Can be reduced to O(N) if we make `ppl` an `unordered_set`.
class UnionFind {
    vector<int> id;
public:
    UnionFind(int n) : id(n) {
        iota(begin(id), end(id), 0);
    }
    void connect(int a, int b) {
        id[find(b)] = find(a);
    }
    int find(int a) {
        return id[a] == a ? a : (id[a] = find(id[a]));
    }
    bool connected(int a, int b) {
        return find(a) == find(b);
    }
    void reset(int a) { id[a] = a; }
};
class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& A, int firstPerson) {
        sort(begin(A), end(A), [](auto &a, auto &b) { return a[2] < b[2]; }); // Sort the meetings in ascending order of meeting time
        UnionFind uf(n);
        uf.connect(0, firstPerson); // Connect person 0 with the first person
        vector<int> ppl;
        for (int i = 0, M = A.size(); i < M; ) {
            ppl.clear();
            int time = A[i][2];
            for (; i < M && A[i][2] == time; ++i) { // For all the meetings happening at the same time
                uf.connect(A[i][0], A[i][1]); // Connect the two persons
                ppl.push_back(A[i][0]); // Add both persons into the pool
                ppl.push_back(A[i][1]);
            }
            for (int n : ppl) { // For each person in the pool, check if he/she's connected with person 0.
                if (!uf.connected(0, n)) uf.reset(n); // If not, this person doesn't have secret, reset it.
            }
        }
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (uf.connected(0, i)) ans.push_back(i); // Push all the persons who are connected with person 0 into answer array
        }
        return ans;
    }
};



//BFS O((M+N)⋅M) total. time spend in while loop O((M+N)⋅M)
class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        // For every person, we store the meeting time and label of the person met.
        unordered_map<int, vector<pair<int, int>>> graph;
        for (auto& meeting : meetings) {
            int x = meeting[0], y = meeting[1], t = meeting[2];
            graph[x].emplace_back(t, y);
            graph[y].emplace_back(t, x);
        }

        // Earliest time at which a person learned the secret
        // as per current state of knowledge. If due to some new information,
        // the earliest time of knowing the secret changes, we will update it
        // and again process all the people whom he/she meets after the time
        // at which he/she learned the secret.
        vector<int> earliest(n, INT_MAX);
        earliest[0] = 0;
        earliest[firstPerson] = 0;

        // Queue for BFS. It will store (person, time of knowing the secret)
        queue<pair<int, int>> q;
        q.emplace(0, 0);
        q.emplace(firstPerson, 0);

        // Do BFS
        while (!q.empty()) {
            auto [person, time] = q.front();
            q.pop();
            for (auto [t, nextPerson] : graph[person]) {
                if (t >= time && earliest[nextPerson] > t) {
                    earliest[nextPerson] = t;
                    q.emplace(nextPerson, t);
                }
            }
        }

        // Since we visited only those people who know the secret,
        // we need to return indices of all visited people.
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (earliest[i] != INT_MAX) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};