/*
Time complexity O(nnd)
Space complexity O(n)

*/

class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int D) {
        int n = jobDifficulty.size(), inf = 1e9, maxd;
        if (n < D) return -1;
        vector<int> dp(n, 1e9);
        int curmax = 0;
        for(int i = 0; i<n; ++i)
        {
            curmax = max(curmax, jobDifficulty[i]);
            dp[i] = curmax;
        }
        
        for (int d = 1; d < D; ++d) {
            for (int i = n-1; i>=0; --i) {
                maxd = jobDifficulty[i], dp[i] = inf;
                for (int j = i-1; j >=0 ; --j) {
                    dp[i] = min(dp[i], maxd + dp[j]);
                    maxd = max(maxd, jobDifficulty[j]);
                }
            }
        }
        return dp.back();
    }
};



class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int D) {
        int n = jobDifficulty.size(), inf = 1e9, maxd;
        if (n < D) return -1;
        vector<int> dp(n+1, 1e9);
        int curmax = 0;
        dp[0] = 0;
        for (int d = 0; d < D; ++d) {
            for (int i = n-1; i>=d; --i) {
                maxd = 0, dp[i+1] = inf;
                for (int j = i; j >=d; --j) {
                    maxd = max(maxd, jobDifficulty[j]);
                    dp[i+1] = min(dp[i+1], maxd + dp[j]);
                }
            }
        }
        return dp.back();
    }
};


class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int D) {
        int n = jobDifficulty.size(), inf = 1e9, maxd;
        if (n < D) return -1;
        vector<int> dp(n + 1, 1e9);
        dp[n] = 0;
        for (int d = 1; d <= D; ++d) {
            for (int i = 0; i <= n - d; ++i) {
                maxd = 0, dp[i] = inf;
                for (int j = i; j <= n - d; ++j) {
                    maxd = max(maxd, jobDifficulty[j]);
                    dp[i] = min(dp[i], maxd + dp[j + 1]);
                }
            }
        }
        return dp[0];
    }
};



class Solution {
public:
    int inf = 1e9;
    int minDifficulty(vector<int>& jobDifficulty, int D) {
        unordered_map<int,unordered_map<int,int>>visited;
        int res = topDown(jobDifficulty, jobDifficulty.size()-1, D, visited);
        return res < inf ? res: -1;
    }
    
    int topDown(vector<int>& jobDifficulty, int index, int D, unordered_map<int,unordered_map<int,int>>&visited){
        if (index == -1 && D == 0)
            return 0;
        if(index == -1 || D<=0)
            return inf;
        if(visited.count(index) && visited[index].count(D))
            return visited[index][D];
        visited[index][D] = inf;
        int curmax = 0;
        for(int i = index; i>=0; --i){
            curmax = max(curmax, jobDifficulty[i]);
            visited[index][D] = min(visited[index][D], curmax + topDown(jobDifficulty, i-1, D-1, visited) );
        }
        return visited[index][D];
    }
};


/*
Complexity: O(nd)

stack 是 descending stack 

e.g. [11,111,22,222,33,333,44,444]  d = 6

dp: 

[11, 111, 111, 222, 222, 333, 333, 444]
[inf, 122, 122, 233, 233, 344, 344, 455]
[11, 111, 144, 344, 266, 455, 388, 566]
[inf, 122, 122, 366, 366, 477, 477, 588]
[11, 111, 144, 344, 399, 699, 521, 810]
[inf, 122, 122, 366, 366, 732, 732, 843]


以下注释 详见python 的解

Firstly we have the basic O(nnd) DP solution:
f[i][j]=min{f[i-1][k]+max(val[k+1..j])},i-2<=k<j
where f[i][j] is the minimum difficulty for first j jobs done in i days, and val=jobDifficulty

Define t=l[j] to be the largest t such that t<j and val[t]>=val[j]

Then we know that for t<=k<j, max(val[k+1..j])=val[j]; 
and that for k<t, max(val[k+1..j])=max(val[k+1..t])
So for k<t case we have min{f[i-1][k]+max(val[k+1..j])}=f[i][t]
For t<=k<j case we have max(val[k+1..j])=val[j], so we only need to calculate min(f[i-1][t..j-1])

The DP equation becomes:
f[i][j]=min(f[i][l[j]],val[j]+min(f[i-1][l[j]..j-1]))
Here we notice that if a>b and val[a]>val[b] then for any c>a, l[c]!=b

Therefore for any l[a]<b<a<c, we have l[c]!=b, so we can suppress the interval l[a]..a-1 since they will always be included together
Finally we use a monotonic stack to maintain the array f[i-1][l[a]..a-1]
 where a={...,l[l[j]],l[j],j} is the representatives for the intervals
The time complexity is O(nd) since in each of the d rounds every j will be popped only once, 

and the space is O(n) because f[i][...] only depends on f[i-1][...]

*/
class Solution {
public:
    int inf = 1e9;
    int minDifficulty(vector<int>& jobDifficulty, int D) {
       int n = jobDifficulty.size();
        if (n < D) return -1;
        vector<int> dp(n, 1000), dp2(n), stack;
        for (int d = 0; d < D; ++d) {
            stack.clear();
            for (int i = d; i < n; i++) {
                dp2[i] = i ? dp[i - 1] + jobDifficulty[i] : jobDifficulty[i];
                while (stack.size() && jobDifficulty[stack.back()] <= jobDifficulty[i]) {
                    int j = stack.back(); stack.pop_back();
                    dp2[i] = min(dp2[i], dp2[j] - jobDifficulty[j] + jobDifficulty[i]);//dp2的值 都是由此前的高点update的， 而此前的高点小于当前点，就减去此前的高点
                    /*
                    比如 jobDifficulty 12 3  7  15 
                        dp2           12 12 12   
                        到了15 点，stack 有7, 12, 应用12的点 update  15,  = 12 - 12 + 15 = 15
                        用7点的update， 12 - 7 + 15 =20 会大于 12点update 的值
                    */
                }
                if (stack.size()) {
                    dp2[i] = min(dp2[i], dp2[stack.back()]); //如果当前高度小于前面stack[-1] 的高度，直接等于dp[stack[-1]]], 跟stack.back() 归为一组
                }
                stack.push_back(i);
            }
            swap(dp, dp2);
        }
        return dp[n - 1];
    }
};