/*
313. Super Ugly Number
Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k.

Example:

Input: n = 12, primes = [2,7,13,19]
Output: 32 
Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12 
             super ugly numbers given primes = [2,7,13,19] of size 4.
Note:

1 is a super ugly number for any given primes.
The given numbers in primes are in ascending order.
0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
The nth super ugly number is guaranteed to fit in a 32-bit signed integer.


*/

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int k = primes.size();
        vector<int>pt(k,0);
        vector<int>dp(n,1);
        for(int i = 1; i<n; i++){
            int minval = numeric_limits<int>::max();
            vector<int>minID;
            for(int j = 0; j<k; j++){
                if(dp[pt[j]]*primes[j] < minval){
                    minID = {j};
                    minval = dp[pt[j]]*primes[j];
                }else if(dp[pt[j]]*primes[j] == minval){
                    minID.push_back(j);
                }
            }
            dp[i] = minval;
            for(auto j: minID){
                pt[j]++;
            }
        }
        return dp[n-1];
    }
};

// Time:  O(n * k)
// Space: O(n + k)
// DP solution. 
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        int k = primes.size();
        vector<int> dp(1,1);
        vector<int> tmp(k,0);
        for(int i=1; i<n; i++){
            int min_element=INT_MAX;
            for(int j=0; j<k; j++){
                min_element=min(dp[tmp[j]]*primes[j], min_element);
            }
            dp.push_back(min_element);
            for(int j=0; j<k;j++){
                if(dp[tmp[j]]*primes[j] == min_element){
                    tmp[j]++;
                }
            }
        }
        
        return dp[n-1];
    }
};





/*

heap solution 要保证每次push进heap 数不能有重复

12
[7,2,19,13]

我要保证 只能push 2*7，一次，
So, 第i个prime只能push第i个及它以前数的乘积
比如 这次是通过乘以7是最小的ugly number，下一个push进的数，只能是7*7, 不能是7*2

需要 1.  pt(用过几次prime【k]push进queue) 指向每个prime。 pt[k] 表示刚刚push进heap的数
        是由prime[k]乘*ugly中pt[k]指的数  =  prime[k]*ugly[pt[k]]
    2.  ugly_by_which_prime,  ugly_by_which_prime[i]表示 第i个ugly数, 是通过ulgy[pt[k]-1]最后乘以prime[ugly_by_which_prime[i]]过来的,


每次heap 返回一个top, (cur_ugly, k)  
cur_ugly是现在最小ugly number，
k是这个ungly number是通过乘以prime[k]过来的, ugly_by_which_prime【i] = k

然后whileloop ugly_by_which_prime[pt[k]] 看看是不是下个乘以prime[k]的 是由上个乘以prime[j(given j>K)]过来的，这样子的话不用这个数，pt[k]++
比如[7,2,19,13], 现在cur_ugly是7，7不能乘以2，因为需要用2乘以7，所以就++pt[k] 直到ugly_by_which_prime[pt[k]] <= k, 这个while最多到ugly_by_which_prime[i]
停止，因为直到ugly_by_which_prime【i] = k


*/



class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
        vector<int>ugly(n), ugly_by_which_prime(n), pt(primes.size());
        for(int i = 0; i<primes.size();i++){
            pq.push({primes[i],i});
        }
        ugly[0] = 1; 
        int k;
        for(int i = 1; i<n; i++){
            tie(ugly[i],k) = pq.top();
            pq.pop();
            pt[k]++;
            ugly_by_which_prime[i] = k;
            while(ugly_by_which_prime[pt[k]]>k) pt[k]++;
            pq.push({primes[k]*ugly[pt[k]],k});
        }
        return ugly[n-1];
    }
};



// Time:  O(n * logk) ~ O(n * klogk)
// Space: O(k^2)
// Heap solution. (612ms)  
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        priority_queue<long long , vector<long long>, greater<long long>> heap;
        for(int i = 0; i<primes.size();i++){
            heap.push(primes[i]);
        }
        long long ugly = 1;
        for(int i = 1; i<n; i++){
            ugly = heap.top(); heap.pop();
            for(int k = 0; k<primes.size();k++){
                if(ugly % primes[k] == 0){   //保证假如现在的数能整除primes[i],就乘以primes[i]以前的primes
                /*
                比如primes = [7,2,13, 5]
                现在ugly = 7, push 进的只有49
                现在ugly = 4, push 进的有 4*7 = 28 和 4*2 = 8
                现在ugly = 5, push 进的有 5*7, 2*5, 13*5, 5*5
                
                
                */
                    for(int  j = 0; j<=k;j++)
                        heap.push(ugly*primes[j]);
                    break;
                }
            }
        }
        return ugly;
    }
};


//用priority_queue 把所有push进heap的放进unordered_set, ++pt,直到乘后的数不在unordered_set，就可以push进heap
// Time:  O(n * k)
// Space: O(n + k)
// Hash solution. (804ms)
class Solution4 {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        unordered_set<int> ugly_set{1};
        vector<int> uglies(n), idx(primes.size());
        uglies[0] = 1;

        for (int k = 0; k < primes.size(); ++k) {
            heap.emplace(primes[k], k);
            ugly_set.emplace(primes[k]);
        }

        for (int i = 1; i < n; ++i) {
            int k;
            tie(uglies[i], k) = heap.top();
            heap.pop();
            while (ugly_set.count(primes[k] * uglies[idx[k]])) {
                ++idx[k];
            }
            heap.emplace(primes[k] * uglies[idx[k]], k);
            ugly_set.emplace(primes[k] * uglies[idx[k]]);
        }
    
        return uglies[n - 1]; 
    }
};