
/*
下面的比较快，先记录每个字母的位置，然后loop key，用loopup发现现在key的char的位置减去旧的位置作为step + 过去的minstep
旧的位置step存在dp，新的位置的step存在newDp, newDp = min(newDp, dp+step)，step是loop 移动的位置

记录ring每个字母的位置，字母位置push进vector(相同字母不同位置，vector有的长度大于1)，loop key,把i-1的字母vector作为起始点，
把key[i]字母vector作为现在点，loop（比如上一个字母是b,现在字母是c,ring中两个b，两个c，不知道哪个距离哪个最短，所以需要loop），
找到i位置最小移动距离，如果ring[k] = key[i], update dp[k]的值，

*/

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int n = ring.size();
        int m  = key.size();
        unordered_map<char, vector<int>> mp; 
        for (int i = 0; i < n; ++i) {
            mp[ring[i]].push_back(i);
        }
        vector<int>dp(n, numeric_limits<int>::max());
        dp[0] = 0;
        vector<int>prev_indices(1, 0);
        for (int i = 0; i < m; ++i) {
            vector<int>newDp(n, numeric_limits<int>::max());
            for(auto cur_index: mp[key[i]]) {
                for(auto prev_index: prev_indices){
                    int diff = abs(cur_index - prev_index);
                    int steps = min(diff, n - diff);
                    newDp[cur_index] = min(newDp[cur_index], steps + dp[prev_index]);
                }
            }
            dp = newDp;
            prev_indices= mp[key[i]];
        }
        return *min_element(dp.begin(), dp.end()) + m;
    }
};


//Top-downE
class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int n = ring.size();
        int m  = key.size();
        unordered_map<char, vector<int>> mp; 
        for (int i = 0; i < n; ++i) {
            mp[ring[i]].push_back(i);
        }
        vector<vector<int>>dp(m, vector<int>(n, numeric_limits<int>::max()));
        auto f = [&](this auto && f, int k, int cur_index) {
            if ( k == m) return 0;
            if (dp[k][cur_index]!= numeric_limits<int>::max()) 
                return dp[k][cur_index];
            for(auto nxt: mp[key[k]]) {
                int diff = abs(nxt - cur_index);
                int steps = min(diff, n - diff);
                dp[k][cur_index] = min(dp[k][cur_index], steps + f(k +1, nxt));
            }
            return dp[k][cur_index];
        };
        return f(0, 0) + m;
    }
};

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        vector<vector<int>>mp(26);
        for(int i = 0; i<ring.size();i++)
            mp[ring[i]-'a'].push_back(i);

        vector<int>dp(ring.size(),INT_MAX);
        dp[0] = 0;
        vector<int>startIndex(1,0);
        for(int i = 0; i<key.size();i++){
            vector<int>newDp(ring.size(),INT_MAX);
            for(auto j: mp[key[i]-'a']){
                for(auto k: startIndex){
                    int diff = abs(k-j);
                    int step = min(diff, (int)ring.size()-diff);
                    newDp[j] = min(newDp[j], step+dp[k]);
                }
            }
            dp = newDp;
            startIndex = mp[key[i]-'a'];
        }

        int res = INT_MAX;
        for(auto i: dp)
            res = min(res, i);
        return res+key.size();

    }
};

/*
dp[i][j] 代表key中第i个char 是由ring中第j个过来的，上一个是j，到i需要的距离
但是这个solution 比较慢

dp[i][j]代表当key[i] = ring[k],从j到k的需要步数

*/

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int n = ring.size(), m = key.size();
        vector<vector<int>>dp(m,vector<int>(n,100000000));
        for(int i = m-1; i>=0; i--){
            for(int j = 0; j<n; j++){
                for(int k = 0; k<n; k++){
                    if(ring[k] == key[i]){
                        int diff = abs(k-j);
                        int steps = min(n-diff,diff);
                        if(i == m-1)
                            dp[i][j] = min(dp[i][j],steps);
                        //这里需要min, 因为对于一个k 会有多个k match
                        else 
                            dp[i][j] = min(dp[i][j],steps+dp[i+1][k]); //steps+dp[i+1][k]，  dp[i+1][k]表示key的i+1从ring中k位置来的，steps表示从j到k，让现在ring 和key的imatch
                    }
                }   
            }
        }
        return dp[0][0]+m;
    }
};




class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int k = key.size(), r = ring.size();
        vector<vector<int>>dp(k, vector<int>(r,numeric_limits<int>::max()));
        unordered_map<char, unordered_set<int>>index_mp;
        
        for(int i = 0; i<ring.size(); ++i){
            index_mp[ring[i]].insert(i);
        }
        
        unordered_set<int>startIndice = {0};
        for(int i  = 0; i<k; ++i){
            for(auto prev: startIndice){
                for(auto cur: index_mp[key[i]]){
                    int step = min(abs(cur-prev), r - abs(cur-prev)) + 1;
                    if(i!=0)
                        step += dp[i-1][prev];
                    dp[i][cur] = min(dp[i][cur], step);
                }
            }
            startIndice =  index_mp[key[i]];
        }
        
        int res = r*k;
        for(int j = 0; j<r; ++ j)
            res = min(res, dp[k-1][j]);
        return res;
    }
};


/**
 2020 dp[i][j] 表示当 ring[i] == key [j] 所需要的步数
 */
class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int k = key.size(), r = ring.size();
        vector<vector<int>>dp(k, vector<int>(r,numeric_limits<int>::max()));
        for(int i  = 0; i<k; ++i){
            for(int j = 0; j<r; ++j){
                if(key[i] == ring[j]){
                    if(i==0)
                        dp[0][j] = min(j, r - j)+1;
                    else{
                        int step = numeric_limits<int>::max();
                        for(int prev = 0; prev < r; ++prev){
                            if(key[i-1] == ring[prev])
                                step =min(step, min(abs(j-prev), r - abs(j-prev)) + dp[i-1][prev]);                         
                        }
                        dp[i][j] = step + 1;
                    }
                }
            }
        }
        
        int res = r*k;
        for(int j = 0; j<r; ++ j)
            res = min(res, dp[k-1][j]);
        return res;
    }
};

//Top-Down
class Solution {
public:
       int findRotateSteps(string ring, string key) {
        vector<int> pos[26];
        int r = ring.size();
        for(int i=0;i<r;i++) pos[ring[i]-'a'].push_back(i);
        vector<vector<int>> mem(r,vector<int>(key.size()));
        return findSteps(0, 0, ring, key, pos,mem);    
    }
    int findSteps(int p1, int p2, string &ring, string &key, vector<int> pos[26],vector<vector<int>>& mem) {
        if(p2==key.size()) return 0;
        if(mem[p1][p2]) return mem[p1][p2];
        int r = ring.size(), ms=INT_MAX;
        for(int nxt:pos[key[p2]-'a']) {
            int dist = abs(p1-nxt);
            ms = min(ms,min(dist, r-dist)+findSteps(nxt,p2+1,ring,key,pos,mem));    
        }
        return mem[p1][p2]=ms+1;
    }
};


//Top-Down
/*
The state is represented by the 12:00 direction of index p and the current index of key to spell.
Initially, p = 0. Rotate both direction to find the character to match the character in key to spell. 
there are two cases:

1. left rotation and right rotation end up with same index (i==j) then there is only one branch
2. they end up with different index then there are two branch

 */
class Solution {
public:
       int findRotateSteps(string ring, string key) {
       if(ring.size()==0 || key.size()==0) return 0;
       unordered_map<int,unordered_map<int,int>>dp;
       return findSteps(0, 0, ring, key, dp);    
    }
    int findSteps(int r, int k, string &ring, string &key, unordered_map<int,unordered_map<int,int>>&dp) {
        if(k == key.size())
            return 0;
        if(dp.count(r) && dp[r].count(k))
            return dp[r][k];
        int step1 = 0, step2=0, i=r, j=r;
        for(; ring[i]!=key[k]; step1++) {
            i=(i+1)%ring.size();
        }
        for(; ring[j]!=key[k];step2++) {
            j=(j-1+ring.size())%ring.size();
        }
        if(i==j) { //rotate to same location then use the less count one
            dp[r][k]= min(step1,step2)+1 + findSteps(i, k+1, ring, key, dp);
        } else {
            int r1 = findSteps(i, k+1, ring, key, dp) + step1 + 1;
            int r2 = findSteps(j, k+1, ring, key, dp) + step2 + 1;
            dp[r][k] = min(r1,r2);
        }
        return dp[r][k];
    }
};