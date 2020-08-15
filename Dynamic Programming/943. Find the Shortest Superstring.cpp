/*
Travelling Salesman Problem

dp[val][i]: 走过的路径为val, 最后的到达的i所需要的最小cost
path[val][i]: 走过的路径为val, 最后的到达的i所需要的最小cost 的上一点

*/
class Solution {
public:
    string shortestSuperstring(vector<string>& A) {
        int n = A.size();
        vector<vector<int>>graph(n, vector<int>(n));
        for(int i = 0; i<n; ++i){
            for(int j = 0; j<n; ++j){
                graph[i][j] = calc(A[i], A[j]);
                graph[j][i] = calc(A[j], A[i]);
            }
        }
        
        vector<vector<int>>dp(1<<n, vector<int>(n,numeric_limits<int>::max()));
        vector<vector<int>>path(1<<n, vector<int>(n));
        
        int minv = numeric_limits<int>::max();
        int last = -1;
        for(int i = 1; i<(1<<n);++i){
            for(int j = 0; j<n; ++j){
                if(i & (1<<j)){
                    int prev = i - (1<<j);
                    if(prev == 0)
                    {
                        dp[i][j] = A[j].size();
                    }
                    else{
                        for(int k = 0; k<n; ++k){
                            if(dp[prev][k]!= numeric_limits<int>::max()  && dp[prev][k] + graph[k][j] < dp[i][j]){
                                dp[i][j] = dp[prev][k] + graph[k][j];
                                path[i][j] = k;
                                /*
                                比如 i =  3,  j = 0
                                dp[3][0] = min(dp[2][0] + graph[0][0], dp[2][1] + graph[1][0]); //dp[2][0] = INTMAX
                                
                                所以如果更新 dp[3][0]  只能是 dp[2][1] + graph[1][0], 0和1点都经过
                                 */
                            }
                        }
                    }
                }
                if(i == (1 << n)- 1 && dp[i][j] < minv){
                    minv = dp[i][j];
                    last = j;
                }
            }
        }
        
        string res = A[last];
        int lastTwo = path[(1<<n)-1][last];
        int val = (1<<n)-1 - (1<<last);
        while(val){
            int nlastTwo = A[lastTwo].size(), nlast = A[last].size();
            res = A[lastTwo].substr(0, nlastTwo-(nlast-graph[lastTwo][last])) + res;
            last = lastTwo;
            int tmp = path[val][lastTwo];
            val -= (1 << lastTwo);
            lastTwo = tmp;
        }
        return res;
    }
    
    int calc(const string& A, const string&B){
        int na = A.size(), nb = B.size();
        for(int i = 1; i<A.size(); ++i){//从1开始，因为no string in A is substring of another string in A.
            if(B.substr(0, na-i) == A.substr(i) ){
                return nb - (na - i);
            }
        }
        return nb;
    }
};


class Solution {
public:
   string shortestSuperstring(vector<string>& A) {
        int n = A.size();
        // dp[mask][i] : min superstring made by strings in mask,
        // and the last one is A[i]
        vector<vector<string>> dp(1<<n,vector<string>(n));
        vector<vector<int>> overlap(n,vector<int>(n,0));
        
        // 1. calculate overlap for A[i]+A[j].substr(?)
        for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) if(i!=j){
            for(int k = min(A[i].size(), A[j].size()); k>0; --k)
                if(A[i].substr(A[i].size()-k)==A[j].substr(0,k)){
                    overlap[i][j] = k; 
                    break;
                }
        }
        // 2. set inital val for dp
        for(int i=0; i<n; ++i) dp[1<<i][i] += A[i];
        // 3. fill the dp
        for(int mask=1; mask<(1<<n); ++mask){
            for(int j=0; j<n; ++j) if((mask&(1<<j))>0){
                for(int i=0; i<n; ++i) if(i!=j && (mask&(1<<i))>0){
                    string tmp = dp[mask^(1<<j)][i]+A[j].substr(overlap[i][j]);
                    if(dp[mask][j].empty() || tmp.size()<dp[mask][j].size())
                        dp[mask][j] = tmp;
                }
            }
        }
        // 4. get the result
        int last = (1<<n)-1;
        string res = dp[last][0];
        for(int i=1; i<n; ++i) if(dp[last][i].size()<res.size()){
            res = dp[last][i];
        }
        return res;
    }
};






/*
Travelling Salesman Problem

dp[val][i]: 走过的路径为val, 最后的到达的i所需要的最小cost
path[val][i]: 走过的路径为val, 最后的到达的i所需要的最小cost 的上一点
*/
class Solution {
public:
string shortestSuperstring(vector<string>& A) {
        int n = A.size();
        
        vector<vector<int>> overlaps(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int m = min(A[i].size(), A[j].size());
                for (int k = m; k >= 0; --k) {
                    if (A[i].substr(A[i].size() - k) == A[j].substr(0, k)) {
                        overlaps[i][j] = k;
                        break;
                    }
                }
            }
        }
  
        // dp[mask][i] = most overlap with mask, ending with ith element (ith 也包含在了mask里面)
        vector<vector<int>> dp(1<<n, vector<int>(n, 0));
        vector<vector<int>> parent(1<<n, vector<int>(n, -1));
        
        for (int mask = 0; mask < (1<<n); ++mask) {
            //以下循环是为了计算dp[mask][bit]
            for (int bit = 0; bit < n; ++bit) {
                if (((mask>>bit)&1) > 0) {//说明bit位在mask里面，此时dp[mask][bit]才有意义
                    int pmask = mask^(1<<bit);//这一步是为了把bit位从mask里面去掉
                    if (pmask == 0) continue;//如果mask里面只有一个词，那么跳过
                    for (int i = 0; i < n; ++i) {
                        if (((pmask>>i)&1) > 0) {//如果pmask里面包含了第i位，那么计算以i结尾的pmask，再接上bit位
                            int val = dp[pmask][i] + overlaps[i][bit];
                            /*
                            
                            因为val 是取最大值，比如 ["alexb","loves","kosds"], overlap都是1，
                            从而parent, dp 都没有更新
                             */


                            if (val > dp[mask][bit]) {//如果新算出来的overlap比较大，那么替换原有overlap
                                dp[mask][bit] = val;
                                parent[mask][bit] = i;//保存这种情况下以bit结尾的前一个词。
                            }
                        }
                    }
                }
            }
        }
        
        vector<int> perm;
        vector<bool> seen(n); 
        int mask = (1<<n) - 1;
        
        int p = 0;//先计算出答案的最后一个单词
        for (int i = 0; i < n; ++i) {
            if (dp[(1<<n) - 1][i] > dp[(1<<n) - 1][p]) {
                p = i;
            }
        }
        
        //通过parent数组依次回溯出最后一个单词是p这种情况下，前面所有的排列
        while (p != -1) {
            perm.push_back(p);
            seen[p] = true;
            int p2 = parent[mask][p];
            mask ^= (1<<p);//从mask里面移走p
            p = p2;
        }
        
        //由于回溯出来的是反的，倒一下
        reverse(perm.begin(), perm.end());
        
        //加上没有出现的单词
        for (int i = 0; i < n; ++i) {
            if (!seen[i]) {
                perm.push_back(i);
            }
        }
        
        string ans = A[perm[0]];
        for (int i = 1; i < n; ++i) {
            int overlap = overlaps[perm[i - 1]][perm[i]];
            ans += A[perm[i]].substr(overlap);
        }
        
        return ans;
        
    }
};