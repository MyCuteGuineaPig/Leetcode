/*
547. Friend Circles

Time	Space	Difficulty	
O(n^2)	O(n)	Medium


There are N students in a class. Some of them are friends, while some are not. Their friendship is transitive in nature. For example, if A is a direct friend of B, and B is a direct friend of C, then A is an indirect friend of C. And we defined a friend circle is a group of students who are direct or indirect friends.

Given a N*N matrix M representing the friend relationship between students in the class. If M[i][j] = 1, then the ith and jth students are direct friends with each other, otherwise not. And you have to output the total number of friend circles among all the students.

Example 1:
Input: 
[[1,1,0],
 [1,1,0],
 [0,0,1]]
Output: 2
Explanation:The 0th and 1st students are direct friends, so they are in a friend circle. 
The 2nd student himself is in a friend circle. So return 2.
Example 2:
Input: 
[[1,1,0],
 [1,1,1],
 [0,1,1]]
Output: 1
Explanation:The 0th and 1st students are direct friends, the 1st and 2nd students are direct friends, 
so the 0th and 2nd students are indirect friends. All of them are in the same friend circle, so return 1.
Note:
N is in range [1,200].
M[i][i] = 1 for all students.
If M[i][j] = 1, then M[j][i] = 1.


*/

//Write by own, Union Find
class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        if(M.empty() || M[0].empty()) return 0;
        DisjointSet ds(M.size());
        for(int i = 0; i<M.size()-1; i++){
            for(int j = i+1; j<M.size(); j++){
                if(M[i][j]==1)
                    ds.join(i,j);
            }
        }
        return ds.size; 
    }

    struct DisjointSet{
        vector<int>parent;
        int size;
        DisjointSet(int size){
            this->size = size;
            parent.resize(size);
            iota(parent.begin(), parent.end(),0);
        }

        int find(int x){
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        }
        
        void join(int x, int y){
            int px = find(x), py = find(y);
            if(px != py){
                parent[px] = py;
                size--;
            }
        }
    };
};


//With Rank Heuristic

class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        DisjointSet st(M.size());
        for(int i = 0; i<M.size(); ++i){
            for(int j = i+1; j<M.size(); ++j){
                if(M[i][j])
                    st.join(i,j);
            }
        }
        return st.size;
    }
private:
    class DisjointSet{
    public:
        vector<int>parents;
        vector<int>rank;
        int size;
        DisjointSet(int n): size(n){
            parents.resize(n);
            rank.resize(n);
            iota(parents.begin(), parents.end(), 0);
        }
        
        int find(int x){
            return parents[x] == x ? x : parents[x] = find(parents[x]);
        }
        
        void join(int x, int y){
            int px = find(x), py = find(y);
            if(px == py) return;
            --size;
            if(rank[px] > rank[py]) parents[py] = px;
            else if (rank[px] < rank[py]) parents[px] = py;
            else{
                parents[py] = px;
                ++rank[px];
            }
        }
    };
};




//DFS

class Solution {
public:
    vector<bool>visited;
    int n;
    int findCircleNum(vector<vector<int>>& M) {
        n = M.size();
        int teams = 0, num = n;
        visited.resize(n,false);
        for(int i = 0; i<n && num>0;i++)
            if(!visited[i])
                num -= dfs(M, i), teams++;
        return teams;
    }
    
    int dfs(vector<vector<int>>& M, int s){
        visited[s] = true;
        int numfrd = 1;
        for(int i = 0; i<n; i++)
            if(!visited[i] && M[s][i] == 1)
                numfrd += dfs(M, i);
        return numfrd;
    }
};


/*
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4  
0  [[1,0,0,0,0,0,0,0,0,1,0,0,0,0,0],
1   [0,1,0,1,0,0,0,0,0,0,0,0,0,1,0],
2   [0,0,1,0,0,0,0,0,0,0,0,0,0,0,0],
3   [0,1,0,1,0,0,0,1,0,0,0,1,0,0,0],   
4   [0,0,0,0,1,0,0,0,0,0,0,0,1,0,0],
5   [0,0,0,0,0,1,0,0,0,0,0,0,0,0,0],
6   [0,0,0,0,0,0,1,0,0,0,0,0,0,0,0],   
7   [0,0,0,1,0,0,0,1,1,0,0,0,0,0,0],
8   [0,0,0,0,0,0,0,1,1,0,0,0,0,0,0],
9   [1,0,0,0,0,0,0,0,0,1,0,0,0,0,0],
10  [0,0,0,0,0,0,0,0,0,0,1,0,0,0,0],
11  [0,0,0,1,0,0,0,0,0,0,0,1,0,0,0],
12  [0,0,0,0,1,0,0,0,0,0,0,0,1,0,0],
13  [0,1,0,0,0,0,0,0,0,0,0,0,0,1,0],
14  [0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]]


*/
