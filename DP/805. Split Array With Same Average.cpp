/*
805. Split Array With Same Average
In a given integer array A, we must move every element of A to either list B or list C. 
(B and C initially start empty.)

Return true if and only if after such a move, it is possible that the average value of B is equal to the average value of C, 
and B and C are both non-empty.

Example :
Input: 
[1,2,3,4,5,6,7,8]
Output: true
Explanation: We can split the array into [1,4,5,8] and [2,3,6,7], and both of them have the average of 4.5.
Note:

The length of A will be in the range [1, 30].
A[i] will be in the range of [0, 10000].

*/


/*
  totalSum/n = Asum/k = Bsum/(n-k), where k = A.size() and 1 <= k <= n/2;
  Asum = totalSum*k/n, which is an integer. So we have totalSum*k%n == 0;
  不要求 Asum, 和 Bsum一样, 只要totalSum*k%n == 0  --》 totalSum*(n-k)%n == 0;

If totalSumk%n == 0, totalSum(n-k)%n must == 0, because totalSumn%n == 0 and totalSumk + totalSum*(n-k) == totalSum*n
*/

class Solution {
public:
    bool splitArraySameAverage(vector<int>& A) {
        int n = A.size(), total = accumulate(A.begin(), A.end(),0), m = n/2;
        
        bool hassolution = false;
        for(int i = 1; i<=m && !hassolution; i++)
            if(total*i%n == 0)
                hassolution = true;
        if(!hassolution) return false;
        vector<unordered_set<int>>dp(m+1);
        dp[0] = {0};
        for(int num: A) for(int i = m; i>=1; i--) for(auto t: dp[i-1])
            dp[i].insert(t+num);
        
        for(int i = 1; i<=m; i++)
            if(total*i%n == 0 && dp[i].count(total*i/n)) return true;
        return false;

    }
};


class Solution {
public:
    bool splitArraySameAverage(vector<int>& A) {
        int n = A.size(), m = n/2, totalSum = accumulate(A.begin(), A.end(), 0);
        sort(A.rbegin(), A.rend()); // Optimization
        for (int i = 1; i <= m; ++i) 
            if (totalSum*i%n == 0 && combinationSum(A, 0, i, totalSum*i/n)) return true;
        return false;
    }
    bool combinationSum(vector<int>& nums, int idx, int k, int tar) {
        if (tar > k * nums[idx]) return false; // Optimization, A is sorted from large to small
        if (k == 0) return tar == 0;
        for (int i = idx; i <= nums.size()-k; ++i) 
            if (nums[i] <= tar && combinationSum(nums, i+1, k-1, tar-nums[i])) return true;
        return false;
    }
};


bool splitArraySameAverage(vector<int>& A) {        
    int N = A.size(), S = 0;
    for (int a : A) S += a;
    bitset<300001> p[N] = {1};
    for (int a : A)
        for (int n = N - 2; n >= 0; n--)
            p[n+1] |= p[n] << a;
    for (int n = 1; n < N; n++)
        if (S*n%N == 0  &&  p[n][S*n/N])
            return true;
    return false;
}