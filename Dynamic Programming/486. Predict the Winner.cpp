
/*
不能用 memoization 原因 Person 到达 [i,j], 之前累积的数可能不一样

比如
[12, 5, 13, 35, 7]

[2,3] 表示index
B [2,3]: 方式一:  第一步 A: 12,  第二步: B: 5, 第三步 A: 7 +12 = 19.    A : 19 vs B: 5
         方式二:  第一步 A: 12,  第二步： B: 7,  第三步 A: 12 + 5 = 17   A: 17  vs B: 7

 */

class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        return dfs(nums, 0, static_cast<int>(nums.size())-1, 0, 0);
    }
    
    bool dfs(const vector<int>&nums, int i, int j, int cur, int prev){
        if (i == j)
            return prev + nums[i] >= cur;
        
        if(i == j-1)
            return nums[i] + prev >= cur + nums[j] || nums[j] + prev >= cur + nums[i];
        
        return !dfs(nums, i+1, j, prev + nums[i], cur) || !dfs(nums, i,j-1, prev + nums[j], cur);
        //比如 [0,5] A赢的前提是 [0,4] or [1,5] B 必须输
    }
};


// DP
/**
 dp[i][j] saves how much more scores that the first-in-action player will get from i to j than the second player. 
 
 First-in-action means whomever moves first. You can still make the code even shorter but I think it looks clean in this way.


 对于 Recursive， 有重复，比如

 player 1 picks left, then player 2 picks left, then player 1 picks right, then player 2 picks right"  
 the same as 
 "player 1 picks right, then player 2 picks right, then player 1 picks left, then player 2 picks left". 
 So, we may want to use dynamic programming to save intermediate states.

 */
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size(); 
        vector<vector<int>>dp(n,vector<int>(n,0));
        for(int i = 0; i<nums.size(); ++i)
            dp[i][i] = nums[i];
        
        for(int len = 1; len<n; ++len){
            for(int i = 0; i < n - len; i++){
                int j = i + len;
                dp[i][j] = max(nums[i] - dp[i+1][j], nums[j] - dp[i][j-1]);
            }   
        }
        return dp[0][n-1] >= 0;
    }
};


class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size(); 
        vector<vector<int>>dp(n,vector<int>(n,0));
        for(int j = 0; j<n; ++j){
            dp[j][j] = nums[j];
            for(int i = j-1; i>=0; i--){
                dp[i][j] = max(nums[i] - dp[i+1][j], nums[j] - dp[i][j-1]);
            }   
        }
        return dp[0][n-1] >= 0;
    }
};

//Space O(n)

class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size(); 
        vector<int>dp(n,0);
        for(int i = n -1; i>=0; --i){
            dp[i] = nums[i];
            for(int j = i + 1; j<n; ++j){
                dp[j] = max(nums[j] - dp[j-1], nums[i] - dp[j]);
            }
        }
        return dp[n-1] >= 0;
    }
};


/*

So dp[i][i] means only one coin and we pick firstly, dp[i][i+1] means there are two coins, we pick the larger one.

dp[i][j] = max( nums[i] + dp[i + 1][j], dp[i][j - 1] + nums[j]) 但是 dp[i+1][j], dp[i][j-1] 是opponent make not optimal for us

So the correct dp formula would be
dp[i][j] = max( min (dp[i + 1][j - 1], dp[i + 2][ j]) + v[i], min (dp[i][j - 2], dp[i + 1][ j - 1]) + v[j]}) .

如果选择了i, 对手subproblem 是 dp[i+1][j], 如何选择 i + 1 or j 让我们得到的值(dp[i+2][j] or dp[i+1][j-1])最小，
同理, 如果我们选择j, 对手subproblem 是 dp[i][j-1], 如何选择 i  or j-1 让我们得到的值(dp[i+1][j-1] or dp[i][j-2])最小，
 */

class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {

        int n = nums.size(), sum = 0;
	    if(n % 2 == 0) return true;
        //If n is even, the first player can choose element from either all odd indices or even indices (easily proven by induction),
        // so it's a simply comparison between sum of all odd and all even positions.
        vector<vector<int>>dp(n, vector<int>(n));
        
        for(int i=0; i < n; i++) {
            dp[i][i] = nums[i];
            sum += nums[i];
        }

        for(int j = 0; j < n; j++){
            for(int i = j - 1; i >= 0; i--){
            	int a = (i + 1 < n && j - 1 >= 0) ? dp[i + 1][j - 1] : 0;
		int b = (i + 2 < n) ? dp[i + 2][ j] : 0;
		int c = (j - 2 >= 0) ? dp[i][j - 2] : 0;
                dp[i][j] = max(min(a, b) + nums[i], min(a, c) + nums[j]);
            }
        }

        return dp[0][n - 1] * 2 >= sum;
    }
};



//跟上面是一样的逻辑， top-Down
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        if(nums.size()% 2 == 0) return true;
        
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        
        int myBest = utill(nums, dp, 0, n-1);
        return 2*myBest >= accumulate(nums.begin(), nums.end(), 0);
    }
    
    int utill(vector<int>& v, vector<vector<int>> &dp, int i, int j){
        if(i > j) return 0;
        if(dp[i][j] != -1) return dp[i][j];
        
        int a = v[i] + min(utill(v,dp, i+1, j-1), utill(v, dp, i+2, j));
        int b = v[j] + min(utill(v,dp,i, j-2), utill(v,dp, i+1, j-1));
        dp[i][j] = max(a, b);
                        
        return dp[i][j];
    }



//Time: Without cache/mem, it is O(2^n), because each node can have 2 children. 
//With cache/mem, it is O(n^2), same as DP, because at most, we will calculate all index * index combinations and others are just read from cache.
// There are n ^ 2 of possible combinations.

class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
       return helper(nums, 0, nums.size()-1)>=0;
    }
    
    int helper(const vector<int>& nums, int s, int e){        
        return s==e ? nums[e] : max(nums[e] - helper(nums, s, e-1), nums[s] - helper(nums, s+1, e));
    }
};


class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        unordered_map<int, unordered_map<int,int>> dp;
        return helper(dp, nums, 0, nums.size()-1)>=0;
    }
    
    int helper(unordered_map<int, unordered_map<int,int>>& dp, const vector<int>& nums, int s, int e){    
        if(dp.count(s) && dp[s].count(e))
            return dp[s][e];
        return s==e ? nums[e] : max(nums[e] - helper(dp, nums, s, e-1), nums[s] - helper(dp, nums, s+1, e));
    }
};