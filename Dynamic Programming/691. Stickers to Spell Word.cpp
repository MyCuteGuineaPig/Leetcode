/*

一个长度为2^T array, array的j位记录此binary number的i位为1的,在target中被set 需要最小sticker数，
比如target长度为4，array长度为16，j = 5(1001) dp\[5] 表示当第0位和第三位在target中被set 所需最小sticker数 
 */
class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        int n = target.size(), N = 1 << n;
        vector<uint> dp(N, -1); dp[0] = 0;
        for(int i = 0; i < N; ++i){
            if(dp[i] == -1) continue;

            for(auto& word: stickers) {
                int now = i;
                for (auto &c: word){
                    for(int j = 0; j < n; ++j){
                        if(target[j] != c || now & (1<<j)) continue;
                        // now & (1<<j) means j's th bit already set by now 
                        now |= (1<<j);
                        break; //记得break 
                    }
                }
                dp[now] = min(dp[now], dp[i] + 1);
            }
            
        }
        return dp.back();
    }
};

/*
并没有speed up

*/

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        unordered_map<char, int>t_count;
        for_each(target.begin(), target.end(), [&](const char & a){t_count[a]++;});
        vector<unordered_map<char, int>>stickers_count(stickers.size());
        
        for(int i = 0; i<stickers.size();i++){
            for_each(stickers[i].begin(), stickers[i].end(), [&](const char & b){
                if(t_count.count(b)) stickers_count[i][b]++;
            });
        }
        vector<unordered_map<char, int>>clean_count(stickers.size());
        for(int i = 0; i<stickers_count.size();i++){
            if(stickers_count[i].size()>0){
                bool has = false;
                for(int j = 0; j<clean_count.size();j++){
                    if(clean_count[j] == stickers_count[i]){
                        has = true;
                        break;
                    }
                }
                if(!has) clean_count.push_back(stickers_count[i]);//如果有一眼的unordered_map 就不要添加了
            }
        }
        
        int n = target.size(), N = 1 << n;
        vector<uint> dp(N, -1); dp[0] = 0;
        for(int i = 0; i<N; i++){
            if(dp[i]==-1) continue;
            for(auto sticker: clean_count){
                int now = i;
                for(auto s: sticker){
                    for(int k = 0; k<s.second; k++)
                    {
                        for(int r = 0; r<n; r++){
                        if(target[r] != s.first || (now>>r) & 1) continue; //r位被set了
                        now |= 1<<r;
                        break; //每个sticker中字母在target中只能用一次
                        }   
                    }
                }
                dp[now] = min(dp[now], dp[i]+1);
            }
            
        }
        return dp.back();
    }
};



/*
最快解
*/

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        unordered_map<string, int> dp;
        vector<string> v = stickers;
        sort(target.begin(), target.end());
        for (auto& a : v) {
            sort(a.begin(), a.end());
        }
        dp[""] = 0;
        getNum(target, v, dp);
        return dp[target] >= 1e6 ? -1 : dp[target];
    }

private:
    int getNum(const string& t, const vector<string>& v, unordered_map<string, int>& dp) {
        auto it = dp.find(t);
        if (it != dp.end()) {
            return it->second;
        }
        int num = 1e6;
        for (const auto& s : v) {
            if (s.find(t[0]) != -1) { //如果set_difference == t, 陷入无限循环
                string n;
                set_difference(t.begin(), t.end(), s.begin(), s.end(), back_inserter(n));
                num = min(num, getNum(n, v, dp) + 1);
            }
        }
        return dp[t] = num;
    }
};


class Solution {
public:
    int minStickers(vector<string>& stickers, string target) { 
        unordered_map<string,uint>dp; dp[""] = 0;
        sort(target.begin(),target.end());
        for(string & s: stickers)
            sort(s.begin(),s.end()); //比如target 最小是a, 有的sticker 最小是b, 那么肯定需要其他的sticker 才可以组成target
        return helper(dp, stickers, target);
    }
    
    uint helper(unordered_map<string,uint>& dp, const vector<string>& v, string t ){
        auto it = dp.find(t);
        if(it!=dp.end())
            return dp[t];
        dp[t] = -1;
        for(auto s: v){
            if(s.find(t[0]) != -1){
                string newt;
                set_difference(t.begin(),t.end(),s.begin(), s.end(), back_inserter(newt));
                uint get = helper(dp, v, newt);
                dp[t] = min(dp[t], get==-1? -1: get+1);
            }
        }
        return dp[t];
    }
};


class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        unordered_map<string, int>dp;
        dp[""] = 0;
        int res = helper(dp, stickers, target);
        return res == 1000000 ? -1 : res;
    }
    
    int helper(unordered_map<string, int>&dp, vector<string>& stickers, const string& cur){
        if(dp.count(cur))
            return dp[cur];
        int res = 1000000;
        for(auto sticker: stickers){
            //相当于set difference
            string nxt;
            int now = 0;
            for(int i = 0; i<cur.size(); ++i){
                for(int j = 0; j< sticker.size(); ++j){
                    if((now & 1<<j) == 0 && sticker[j] == cur[i]){
                        now |= 1<<j;
                        break;
                    }
                    else if(j == sticker.size()-1){
                        nxt += cur[i];
                    }
                }
            }

            if(now)
                res = min(res, helper(dp, stickers, nxt)+1);
        }
        return dp[cur] = res;
    }
};


// Time:  O(T * S^T)
// Space: O(T * S^T)
class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        int m = stickers.size();
        vector<vector<int>> mp(m, vector<int>(26, 0));
        unordered_map<string, int> dp;
        // count characters a-z for each sticker 
        for (int i = 0; i < m; i++) 
            for (char c:stickers[i]) mp[i][c-'a']++;
        dp[""] = 0;
        return helper(dp, mp, target);
    }
private:
    int helper(unordered_map<string, int>& dp, vector<vector<int>>& mp, string target) {
        if (dp.count(target)) return dp[target];
        int ans = INT_MAX, n = mp.size();
        vector<int> tar(26, 0);
        for (char c:target) tar[c-'a']++;
        // try every sticker
        for (int i = 0; i < n; i++) {
            // optimization
            if (mp[i][target[0]-'a'] == 0) continue; 
            string s;
            // apply a sticker on every character a-z
            for (int j = 0; j < 26; j++) 
                if (tar[j]-mp[i][j] > 0) s += string(tar[j]-mp[i][j], 'a'+j);
            int tmp = helper(dp, mp, s);
            if (tmp!= -1) ans = min(ans, 1+tmp);
        }
        dp[target] = ans == INT_MAX? -1:ans;
        return dp[target];
    }
};