/*
691. Stickers to Spell Word

We are given N different types of stickers. Each sticker has a lowercase English word on it.

You would like to spell out the given target string by cutting individual letters from your collection of stickers and rearranging them.

You can use each sticker more than once if you want, and you have infinite quantities of each sticker.

What is the minimum number of stickers that you need to spell out the target? If the task is impossible, return -1.

Example 1:

Input:

["with", "example", "science"], "thehat"
Output:

3
Explanation:

We can use 2 "with" stickers, and 1 "example" sticker.
After cutting and rearrange the letters of those stickers, we can form the target "thehat".
Also, this is the minimum number of stickers necessary to form the target string.
Example 2:

Input:

["notice", "possible"], "basicbasic"
Output:

-1
Explanation:

We can't form the target "basicbasic" from cutting letters from the given stickers.
Note:

stickers has length in the range [1, 50].
stickers consists of lowercase English words (without apostrophes).
target has length in the range [1, 15], and consists of lowercase English letters.
In all test cases, all words were chosen randomly from the 1000 most common US English words, and the target was chosen as a concatenation of two random words.
The time limit may be more challenging than usual. It is expected that a 50 sticker test case can be solved within 35ms on average.


*/

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        int n = target.size(), N = 1 << n;
        vector<uint> dp(N, -1); dp[0] = 0;
        for(int i = 0; i<N; i++){
            if(dp[i]==-1) continue;
            for(auto sticker: stickers){
                int now = i;
                for(char s: sticker){
                    for(int r = 0; r<n; r++){
                        if(target[r] != s || (now>>r) & 1) continue; //r位被set了
                        now |= 1<<r;
                        break; //每个sticker中字母在target中只能用一次
                    }
                }
                dp[now] = min(dp[now], dp[i]+1);
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
                if(!has) clean_count.push_back(stickers_count[i]);
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
最快接
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
            if (s.find(t[0]) != -1) {
                string n;
                set_difference(t.begin(), t.end(), s.begin(), s.end(), back_inserter(n));
                num = min(num, getNum(n, v, dp));
            }
        }
        return dp[t] = ++num;
    }
};


class Solution {
public:
    int minStickers(vector<string>& stickers, string target) { 
        unordered_map<string,uint>dp; dp[""] = 0;
        sort(target.begin(),target.end());
        for(string & s: stickers)
            sort(s.begin(),s.end());
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
        unordered_map<string, int> dp;
        vector<string> v = stickers;
        sort(target.begin(), target.end());
        for (auto& a : v) {
            sort(a.begin(), a.end());
        }
        dp[""] = 0;
        getNum(target, v, dp);
        cout<<" dp size "<<dp.size()<<endl;
        return dp[target] >= 1e6 ? -1 : dp[target];
    }

private:
    int getNum(const string& t, const vector<string>& v, unordered_map<string, int>& dp) {
        cout<<" in target "<<t<<endl;
        auto it = dp.find(t);
        if (it != dp.end()) {
            return it->second;
        }
        int num = 1e6;
        for (const auto& s : v) {
            if (s.find(t[0]) != -1) {
                cout<<" find difference "<<s;
                string n;
                set_difference(t.begin(), t.end(), s.begin(), s.end(), back_inserter(n));
                cout<<"  new t "<<n<<endl;
                num = min(num, getNum(n, v, dp));
                cout<<" t "<<t<<" after return "<<num<<endl;
            }
        }
        cout<<" return num "<<num+1<<endl;
        return dp[t] = ++num;
    }
};

