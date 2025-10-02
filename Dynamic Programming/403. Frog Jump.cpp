

/*
backtrack 会timeout 因为这个会重复很多，比如现在move是10， next move 11，start 是100, 
vector有100，101，102，103，104，105，106，107，108，112，往前动了12，发现不行，又回到100，
然后next move是10，再roll from 100到110，又动了10还是不行
然后next move是9，再roll from 100到109，发现不行，于是重复了很多遍

*/

class Solution {
public:
    bool canCross(vector<int>& stones) {
        return backtrack(stones,1,1);
    }
    
    bool backtrack(vector<int>&stones, int index, int k){
        if(index == stones.size())
            return true;
        for(int i = index; i<stones.size()&& stones[i]<=stones[index-1]+k;i++){
            if(stones[i] == stones[index-1]+k){
                if(backtrack(stones,i+1, k+1) || backtrack(stones,i+1, k) || (k>1 && backtrack(stones,i+1, k-1)))
                    return true;
            }
        }
        return false;
    }
};

/*
DFS 也timeout 

*/

class Solution {
public:
    bool canCross(vector<int>& stones, int pos = 0, int k = 0) {
        for (int i = pos + 1; i < stones.size(); i++) {
            int gap = stones[i] - stones[pos];
            if (gap < k - 1) continue;  //小于当前的step, 继续
            if (gap > k + 1) return false; //大于当前的step + 1, 不能继续
            if (canCross(stones, i, gap)) return true;
        }
        return pos == stones.size() - 1;
    }
};



/****************ACCEPT SOLUTION ***********************/

/*
Bit Solution: 

把k和 pos combine起来，比如第8位置的k=2， 和第8位置k=3，key是不一样的

*/
class Solution {
public:
unordered_map<int, bool> dp;

    bool canCross(vector<int>& stones, int pos = 0, int k = 0) {
        int key = pos | k << 11;

        if (dp.count(key) > 0)
            return dp[key];

        for (int i = pos + 1; i < stones.size(); i++) {
            int gap = stones[i] - stones[pos];
            if (gap < k - 1)
                continue;
            if (gap > k + 1)
                return dp[key] = false;
            if (canCross(stones, i, gap))
                return dp[key] = true;
        }

        return dp[key] = (pos == stones.size() - 1);
    }
};

/****************ACCEPT SOLUTION ***********************/
/*
DP
*/


class Solution {
public:
    bool canCross(vector<int>& stones) {
        if(stones[1]!=1) return false;
        unordered_map<int,unordered_set<int>>dp;
        for(auto i: stones)
            dp[i] = {};
        dp[1].insert(1);
        for(int i = 1; i<stones.size()-1;i++){
            for(auto j: dp[stones[i]]){
                for(int move: {j-1, j, j+1}){
                    if(move>0 && dp.count(move+stones[i])){
                        dp[move+stones[i]].insert(move);
                    }
                }
            }
        }
        return dp[stones.back()].size()!=0;
    }
};


class Solution {
public:
    bool canCross(vector<int>& stones) {
        int N = stones.size();
        vector<vector<int>>dp(N+1, vector<int>(N+1));
        //dp[i][j] 表示可以从i出发前进j 步
        dp[0][1] = true;
        
        for(int i = 1; i < N; ++i){
            for(int j = 0; j < i; ++j){
                int diff = stones[i] - stones[j];
                if(diff < 0 || diff > N || !dp[j][diff]) continue;
                dp[i][diff] = true;
                if(diff - 1 >= 0) dp[i][diff - 1] = true;
                if(diff + 1 <= N) dp[i][diff + 1] = true;
                if(i == N - 1) return true;
            }
        }

        return false;
    }
};


//2020 Top-Down DFS
class Solution {
public:
    bool canCross(vector<int>& stones) {
        if(stones[1]!=1)
            return false;
        unordered_set<int>st(stones.begin(), stones.end());
        unordered_map<int, unordered_set<int>>visited;
        return dfs(st, visited, stones.back(), 1, 1);
    }
    
    bool dfs(unordered_set<int>&stones, unordered_map<int, unordered_set<int>>&visited, int last, int cur, int step){
        //cout<<cur<<" step "<<step<<endl;
        if(visited.count(cur) && visited[cur].count(step))
            return false;
        if(cur == last)
            return true;
        for(int i = -1; i<=1; ++i){
            if(step + i > 0 && stones.count(cur+step + i) && dfs(stones, visited, last, cur + step+i, step+i))
                return true;
        }
        visited[cur].insert(step);
        return false;
    }
};

//2025
class Solution {
public:
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        if (stones[1] != 1) return false;
        unordered_map<int, unordered_set<int>> visited;
        unordered_set<int>stones_dict(stones.begin(), stones.end());
        auto f = [&](this auto&& f, int cur, int step) {
            if(cur == stones.back())
                return true;
            if (visited.count(cur) && visited[cur].count(step)) return false;
            for(auto move : {step -1, step, step + 1}) {
                if ( move > 0 &&  stones_dict.count(cur + move) && f(cur + move, move))
                    return true;
            }
            visited[cur].insert(step);
            return false;
        };
        return f(1, 1);
    }
};

//2020 BFS
class Solution {
public:
    bool canCross(vector<int>& stones) {
        if(stones[1]!=1)
            return false;
        unordered_set<int>st(stones.begin(), stones.end());
        unordered_map<int, unordered_set<int>>visited;
        queue<pair<int,int>>q; q.push({1,1});
        
        int step = 1;
        while(q.size()){
            int size = q.size();
            for(int z = 0; z<size; ++z){
                int point, step;
                tie(point, step) = q.front(); q.pop();
                if(point == stones.back())
                    return true;
                for(int i = -1; i<=1; ++i){    
                    if(step + i > 0 && st.count(point + step + i) && visited[point+step+i].count(step+i) == 0){
                        visited[point+step+i].insert(step+i); 
                        //注意： 不能把visited insert 放到for loop 外面, visited[point].insert(step), 这会重复算point
                        //      因为加进queue了，还没有pop且没放进 visited, 可能有其他一样的point和step会visit
                        q.push({point + step +i , step + i});
                    }
                    
                }
            }
        }
        
        return false;
    }
};

//2020 Bottom-up
class Solution {
public:
    bool canCross(vector<int>& stones) {
        if(stones[1]!=1)
            return false;
        unordered_map<int, unordered_set<int>>st;
        st[1].insert(1);
        for(int i = 1; i<stones.size()-1;++i){
            for(auto nxt: st[stones[i]]){
                for(int j = -1; j<=1; ++j){
                    if(nxt + j > 0)
                        st[stones[i]+nxt+j].insert(nxt + j);
                }
            }
        }
        return st[stones.back()].size();
    }
};