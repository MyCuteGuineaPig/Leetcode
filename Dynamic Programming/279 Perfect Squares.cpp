/*
279. Perfect Squares
https://leetcode.com/problems/perfect-squares/description/
Given a positive integer n, find the least number of perfect square numbers 
(for example, 1, 4, 9, 16, ...) which sum to n.
For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.
*/



class Solution {
public:
    int numSquares(int n) {
        if(n<=0 ) return 0;
        static vector<int>cntPerfectSquares({0});
        while(cntPerfectSquares.size()<=n){
            int m = cntPerfectSquares.size();
            int cur = INT_MAX;
            for(int i = 1; i*i<=m; i++){
                cur = min(cur, cntPerfectSquares[m-i*i]+1);
            }
            cntPerfectSquares.push_back(cur);
        }
        return cntPerfectSquares[n];
    }
};




1.Dynamic Programming: 440ms

class Solution 
{
public:
    int numSquares(int n) 
    {
        // cntPerfectSquares[i] = the least number of perfect square numbers 
        // which sum to i. Note that cntPerfectSquares[0] is 0.
        vector<int> cntPerfectSquares(n + 1, INT_MAX);
        cntPerfectSquares[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            // For each i, it must be the sum of some number (i - j*j) and 
            // a perfect square number (j*j).
            for (int j = 1; j*j <= i; j++) // 这个会慢，因为有重复比如 13-9 = 4 又会做13-9 = 4, 做了两回的operation
            {
                cntPerfectSquares[i] = 
                    min(cntPerfectSquares[i], cntPerfectSquares[i - j*j] + 1);
            }
        }
        
        return cntPerfectSquares.back();
    }
};

class Solution {  // 它的complexity是 O(sqrt(n)/2)*O(n)
public:
    int numSquares(int n) 
    {
        // cntPerfectSquares[i] = the least number of perfect square numbers 
        // which sum to i. Note that cntPerfectSquares[0] is 0.
        vector<int> cntPerfectSquares(n + 1, INT_MAX);
        cntPerfectSquares[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j*j <= i/2; j++) // 这个会慢，因为有重复比如 13-9 = 4 又会做13-9 = 4, 做了两回的operation
            {
                cntPerfectSquares[i] = 
                    min(cntPerfectSquares[i], cntPerfectSquares[i - j*j] + 1);
            }
        }
        return cntPerfectSquares.back();
    }
};


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


2.Static Dynamic Programming: 12ms

class Solution { //用了static dynamic programming
public:
    int numSquares(int n) {
        static vector<int>dp = {1};  
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












class Solution 
{
public:
    int numSquares(int n) 
    {
        if (n <= 0)
        {
            return 0;
        }
        
        // perfectSquares contain all perfect square numbers which 
        // are smaller than or equal to n.
        vector<int> perfectSquares;
        // cntPerfectSquares[i - 1] = the least number of perfect 
        // square numbers which sum to i.
        vector<int> cntPerfectSquares(n);
        
        // Get all the perfect square numbers which are smaller than 
        // or equal to n.
        for (int i = 1; i*i <= n; i++)
        {
            perfectSquares.push_back(i*i);
            cntPerfectSquares[i*i - 1] = 1;
        }
        
        // If n is a perfect square number, return 1 immediately.
        if (perfectSquares.back() == n)
        {
            return 1;
        }
        
        // Consider a graph which consists of number 0, 1,...,n as
        // its nodes. Node j is connected to node i via an edge if  
        // and only if either j = i + (a perfect square number) or 
        // i = j + (a perfect square number). Starting from node 0, 
        // do the breadth-first search. If we reach node n at step 
        // m, then the least number of perfect square numbers which 
        // sum to n is m. Here since we have already obtained the 
        // perfect square numbers, we have actually finished the 
        // search at step 1.
        queue<int> searchQ;
        for (auto& i : perfectSquares)
        {
            searchQ.push(i);
        }
        
        int currCntPerfectSquares = 1;
        while (!searchQ.empty())
        {
            currCntPerfectSquares++;
            
            int searchQSize = searchQ.size();
            for (int i = 0; i < searchQSize; i++)
            {
                int tmp = searchQ.front();
                // Check the neighbors of node tmp which are the sum 
                // of tmp and a perfect square number.
                for (auto& j : perfectSquares)
                {
                    if (tmp + j == n)
                    {
                        // We have reached node n.
                        return currCntPerfectSquares;
                    }
                    else if ((tmp + j < n) && (cntPerfectSquares[tmp + j - 1] == 0))
                    {
                        // If cntPerfectSquares[tmp + j - 1] > 0, this is not 
                        // the first time that we visit this node and we should 
                        // skip the node (tmp + j).
                        cntPerfectSquares[tmp + j - 1] = currCntPerfectSquares;
                        searchQ.push(tmp + j);
                    }
                    else if (tmp + j > n)
                    {
                        // We don't need to consider the nodes which are greater ]
                        // than n.
                        break;
                    }
                }
                
                searchQ.pop();
            }
        }
        
        return 0;
    }
};


