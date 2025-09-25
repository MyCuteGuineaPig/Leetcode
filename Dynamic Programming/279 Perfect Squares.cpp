
//1.Dynamic Programming: 440ms
// Bottom-up
class Solution 
{
public:
    int numSquares(int n) 
    {
        vector<int> cntPerfectSquares(n + 1, INT_MAX);
        cntPerfectSquares[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j*j <= i; j++) // 这个会慢，因为有重复比如 13-9 = 4 又会做13-9 = 4, 做了两回的operation
            {
                cntPerfectSquares[i] = 
                    min(cntPerfectSquares[i], cntPerfectSquares[i - j*j] + 1);
            }
        }
        
        return cntPerfectSquares.back();
    }
};

// Bottom-up
class Solution {
public:
    int numSquares(int n) {
        vector<int>dp(n+1);
        iota(dp.begin(), dp.end(), 0);
        for(int i = 4; i <=n; ++i){
            for(int j = 2; j*j <= i; ++j){
                dp[i] = min(dp[i], dp[i-j*j]+1);
            }
        } 
        return dp[n];
    }
};

//Topdown 
class Solution {
public:
    int numSquares(int n) {
        vector<int>dp(n+1);
        iota(dp.begin(), dp.end(), 0);
        auto helper = [&](this auto&& helper, int i){
            if(i == 1) {
                return 1;
            }
            if (i == 0) {
                return 0;
            }
            if(dp[i]!= i || i <= 3)
                return dp[i];
            for(int j = 2; j*j <= i; ++j){
                dp[i] = min(dp[i], helper(i-j*j) + 1);
            }
            return dp[i];
        };
        return helper(n);
    }
};


// Bottom-up
class Solution { //更快的解 比起上面的 这个是 O(sqrt(n))*O(n/2)
public:
    int numSquares(int n) {
        vector<int>dp(n,-1);  
        for(int i = 1; i<=sqrt(n); i++){ 
            dp[i*i-1] = 1;
            for(int j = i*i+1; j<=n;j++){
                if (dp[j-1] == -1) dp[j-1] = j;
                dp[j-1]= min(dp[j-1],dp[j-i*i-1]+1);
            }
        }
        return dp[n-1];
    }
};


//Top-Down
class Solution {
public:
    int numSquares(int n) {
        vector<int>dp(n+1,-1);
        return topDown(dp, n);
    }
    
    int topDown(vector<int>&dp, int i){
        if(dp[i] >= 0)
            return dp[i];
        int cur = i;
        for(int j = 1; j*j<=i; ++j){
            cur = min(cur, topDown(dp, i-j*j)+1);
        }
        return dp[i] = cur;
    }
};






//2.Static Dynamic Programming: 12ms

class Solution { 
public:
    int numSquares(int n) {
        static vector<int>dp = {1};  //用了static dynamic programming
        if(dp.size()<n){
            int size = dp.size();
            vector<int>temp(n-dp.size(),-1);
            dp.insert(dp.end(),temp.begin(),temp.end());
            for(int i = 1; i<=sqrt(n); i++){ 
                dp[i*i-1] = 1;
                for(int j = max(i*i+1,size); j<=n;j++){
                    if (dp[j-1] == -1) dp[j-1] = j;
                    dp[j-1]= min(dp[j-1],dp[j-i*i-1]+1);
                }
            }
        }
        return dp[n-1];
    }
};







// BFS

class Solution 
{
public:
    int numSquares(int n)   
    {
        if (n <= 0)
        {
            return 0;
        }
        
        vector<int> perfectSquares;
        vector<int> cntPerfectSquares(n);
        queue<int> searchQ;

        for (int i = 1; i*i <= n; i++)
        {
            perfectSquares.push_back(i*i);
            searchQ.push(i*i);
            cntPerfectSquares[i*i - 1] = 1;
        }
        
        if (perfectSquares.back() == n)
        {
            return 1;
        }
        
        
        int currCntPerfectSquares = 1;
        while (!searchQ.empty())
        {
            currCntPerfectSquares++;
            
            int searchQSize = searchQ.size();
            for (int i = 0; i < searchQSize; i++)
            {
                int tmp = searchQ.front();

                for (auto& j : perfectSquares)
                {
                    if (tmp + j == n)
                    {
                        // We have reached node n.
                        return currCntPerfectSquares;
                    }
                    else if ((tmp + j < n) && (cntPerfectSquares[tmp + j - 1] == 0))
                    {
                        cntPerfectSquares[tmp + j - 1] = currCntPerfectSquares;
                        searchQ.push(tmp + j);
                    }
                    else if (tmp + j > n)
                    {
                        break;
                    }
                }
                
                searchQ.pop();
            }
        }
        
        return 0;
    }
};


