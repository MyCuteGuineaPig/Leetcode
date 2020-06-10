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
                        else 
                            dp[i][j] = min(dp[i][j],steps+dp[i+1][k]); //steps+dp[i+1][k]，  dp[i+1][k]表示key的i+1从ring中k位置来的，steps表示从j到k，让现在ring 和key的imatch
                    }
                }   
            }
        }
        return dp[0][0]+m;
    }
};


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