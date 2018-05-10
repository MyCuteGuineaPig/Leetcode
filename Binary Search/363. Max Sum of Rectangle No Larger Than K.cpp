/*
363. Max Sum of Rectangle No Larger Than K

Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix such that its sum is no larger than k.

Example:
Given matrix = [
  [1,  0, 1],
  [0, -2, 3]
]
k = 2
The answer is 2. Because the sum of rectangle [[0, 1], [-2, 3]] is 2 and 2 is the max number no larger than k (k = 2).

Note:
The rectangle inside the matrix must have an area > 0.
What if the number of rows is much larger than the number of columns?


*/


/*
brute force O((mn)^2)
https://www.youtube.com/watch?v=yCQN096CwWM

*/

/*
naive approach, time O((nm)^2), space O(mn)
*/
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int n = matrix.size(), m = matrix[0].size(); int res = INT_MIN;
        for(int si = 1; si<=n; si++){ //si是row 开始的起点,
            vector<vector<int>>dp(n+1,vector<int>(m+1,0));
            for(int i = si; i<=n; i++ ){
                for(int j = 1; j<=m; j++){//sj是column的起点
                    dp[i][j] = -dp[i-1][j-1] + dp[i-1][j]+dp[i][j-1] + matrix[i-1][j-1];
                    for(int sj = 0;sj<j; sj++)
                    {
                        int cur = dp[i][j] - dp[i][sj]; //算的是row[si,i], column 是[j,sj], 是不是最大的，不会有重复的
                        if(cur<=k)
                            res = max(res, cur);
                    }
                }
            }
        }
        return res;
    }
};


/* 下面这个算法进一步的优化了运行时间，这个算法是基于计算二维数组中最大子矩阵和的算法，
可以参见youtube上的这个视频Maximum Sum Rectangular Submatrix in Matrix dynamic programming/2D kadane。
这个算法巧妙在把二维数组按行或列拆成多个一维数组，然后利用一维数组的累加和来找符合要求的数字，这里用了lower_bound来加快我们的搜索速度，
也可以使用二分搜索法来替代。我们建立一个集合set，然后开始先放个0进去，为啥要放0呢，因为我们要找lower_bound(curSum - k)，当curSum和k相等时，
0就可以被返回了，这样我们就能更新结果了。由于我们对于一维数组建立了累积和，
那么sum[i,j] = sum[j] - sum[i]，其中sums[i,j]就是目标子数组需要其和小于等于k，然后sums[j]是curSum，而sum[i]就是我们要找值，
当我们使用二分搜索法找sum[i]时，sum[i]的和需要>=sum[j] - k，所以也可以使用lower_bound来找
*/
/*
Binary Search approach, time O(min(m,n)^2*max(m,n)*log(max(m,n))), space(O(max(m,n)))
*/
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int n = min(matrix.size(), matrix[0].size());
        int m = max(matrix.size(), matrix[0].size());
        int res = INT_MIN; 
        
        for(int si = 0; si<n; si++){ 
           vector<int>dp(m,0);
           for(int i = si; i<n; i++ ){
                for(int j = 0; j<m; j++){  
                    dp[j] += m == matrix.size() ? matrix[j][i]: matrix[i][j];   
                }     
                    /*算的是如果column是多的，算的是每一个column到第i行为止所得的和，
                      如果row 是多的，算的是每一个row第i列所得的和

                      比如： [[2,1,3],[4,8,7]], col是多的, row是少的,  inner loop是col
                      当si = 0;
                      当i = 0,  dp[0] = 2, dp[1] = 1, dp[2] = 3
                      当i = 1,  dp[0] = 6, dp[1] = 9, dp[2] = 10

                      比如： [[2,1], [4,3],[8,7]], col是少的, row是多的, inner loop 是row
                      当si = 0时
                      当i = 0,  dp[0] = 2, dp[1] = 4, dp[2] = 8
                      当i = 1,  dp[0] = 3, dp[1] = 7, dp[2] = 15

                    */
                set<int>s;
                s.insert(0); int cursum = 0;
                for(auto sums: dp)
                {
                    cursum += sums;
                    auto it = s.lower_bound(cursum-k); 
                    /*比如cursum 是15, k = 4， 15-4= 11,找大于等于11，如果有比如12，15-12 = 3 <=k, 
                    cursum 是 比如row 多，是column从si开始到i, row 0到j的所有数和
                              if column 多，是row从si开始到i, column 0到j的所有数和

                    接着上面的12是可能是 row从si开始到i, column 0到j_1的所有数和  j_1比j小
                    cursum - it 就是 row从si开始到i, column j_1到j的所有数和, 且小于k
                    */
                    if(it!=s.end()) res = max(res, cursum -*it);
                    s.insert(cursum);
                }
            }
        }
        return res;
    }
};


/*
  [1,  0, 1],
  [0, -2, 3]
  3

*/

class Solution {
public:

    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m=matrix.size();
        if(m==0) return 0;
        int n=matrix[0].size();
        int res=INT_MIN;
        for(int i=0;i<n;i++) {  // the number of columns is smaller
            vector<int> sums(m,0);
            for(int j=i;j<n;j++) {
                for(int row=0;row<m;row++) {
                    sums[row]+=matrix[row][j];
                }
                int ms = maxSumArray(sums, k);
                if (ms == k) return ms;
                if (ms < k && ms > res) res = ms;

            }
        }
        return res;
    }

    int maxSumArray(vector<int> & arr, int k) {
        int sum = 0, maxS = INT_MIN;
        for (int i = 0; i < arr.size(); i++) {  //it's a trick. Maybe O(n) to solve this problem
            sum += arr[i];
            maxS = max(sum, maxS);
            if (sum == k ) return sum;
            if (sum < 0) sum = 0;
        }
        if (maxS <= k) return maxS;
        maxS= INT_MIN;
        set<int>sums;
        sum = 0;
        sums.insert(0);
        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i];
            auto it = sums.lower_bound(sum - k);
            if (it != sums.end()) maxS = max(sum - *it, maxS);
            sums.insert(sum);
        }
        return maxS;
    }      
};