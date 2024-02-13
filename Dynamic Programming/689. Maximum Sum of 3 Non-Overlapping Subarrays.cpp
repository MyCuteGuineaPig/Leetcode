/*
 W记录每个点往后k个sum, left, right记录到j点左面和右面最大k个sum的index, 这样可以O(n) 完成


因为是3个non overlapping, 可以用这种sliding window的方法，如果是4个，就不行了

 */


class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        vector<int>W(nums.size()-k+1, 0);
        vector<int>left(nums.size()-k+1, 0);
        vector<int>right(nums.size()-k+1, 0);
        int best = 0;
        for(int i = 0, cur = 0; i<nums.size(); i++){
            cur += nums[i];
            if(i>=k)
                cur -= nums[i-k];
            if(i>=k-1){
                W[i-k+1] = cur;
                if(W[i-k+1]>W[best])
                    best = i-k+1;
                left[i-k+1] = best;
            }
        }
        best = nums.size()-k;
        for(int i = nums.size()-k; i>=0; i--){
            if(W[i]>=W[best])
                best = i;
            right[i] = best;
        }
        vector<int>res={0, k, 2*k};
        for(int i = k; i<=nums.size()-2*k; i++){
            if(W[left[i-k]]+W[i]+ W[right[i+k]] > W[res[0]] + W[res[1]] + W[res[2]])
                res = {left[i-k], i, right[i+k]};
        }
        return res;
    }
};


/*

            7   13   20   19   19   2   10   1   1   19   k = 3
    W       40  52   58   40   31   13  12   21 
    left    0   1    2    2    2    2   2    2 
    right   2   2    2    3    4    7   7    7 

*/



//2020 
class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>>left(n,vector<int>(2,0)); //[i][0] 不算nums[i] 左侧最大sum 和起始index
        vector<vector<int>>right(n,vector<int>(2,0)); //[i][0] 不算nums[i] 右侧最大sum 和起始index
        for(int i = 0, cur = 0, leftmax = 0, index = 0; i<nums.size(); ++i){
            if(i >= k){
                if(cur > leftmax){
                    leftmax = cur;
                    index = i - k;
                }
                left[i] = {leftmax, index};
                cur -= nums[i-k];
            }
            cur += nums[i];
        }

        for(int i = n-1, cur = 0, rightmax = 0, index = 0; i>=0; --i){
            if(i < n - k){
                if(cur >= rightmax){ //注意是大于等于
                    rightmax = cur;
                    index = i + 1;
                }
                right[i] = {rightmax, index};
                cur -= nums[i+k];
            }
            cur += nums[i];
        }
        
        vector<int>res;
        for(int i = k, cur = 0, totmax = 0; i<nums.size()-k; ++i){
            cur += nums[i];
            if(i >= 2*k -1){
                if(left[i-k+1][0] + right[i][0] + cur > totmax){     //  x  x x | 1 2 3 | x x  x 
                    totmax = left[i-k+1][0] + right[i][0] + cur;    //          |     i |
                    res = {left[i-k+1][1], i-k+1, right[i][1]};                 | i-k+1
                }
                cur-=nums[i-k+1];
            }
        }
        return res;
    }
};



/**
  Idea is similar to stock purchasing
    
  maxSum[i][j]: 当有i个non-overlapping subarrays j 个数, 当前最大的sum
  pos[i][j]:   当有i个non-overlapping subarrays j 个数, 当前最大的sum 第j个interval 的起始index
  sum[j]:  nums[j-k: j-1] 的sum

if maxSum[i-1][j-k] + sum[j] > tot: 前一个i-1 个nonoverlapping 的最大sum, 加上当前sum[j] 大于 tot;
    更新tot 和 pos

  e.g   [1,2,1,2,6,7,5,1], 2

Index   0   1   2   3   4   5   6   7
        1   2   1   2   6   7   5   1
 sum        0   3   3   3   8  13  12 , 6       
 i = 1
 maxSum[1]  0   3   3   3   8  13  13  13 
 pos[1]     0   0   0   0   3   4   4   4
 i = 2, 
 maxSum[2]              6, 11  16  20  20 
 pos[2]              2  2   3   4   5   5
 i = 3                      
 maxSum[3]                      19  23  23
 pos[2]                      4   4   5   5 


 */

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        if (n < 3*k) return {};
        vector<int>sum(n);
        vector<vector<vector<int>>> cnt(3, vector<vector<int>>(n, vector<int>(2)));
        int best_index = 0, cur = 0, best = 0;
        for(int i = 0; i<n; ++i){
            cur += nums[i];
            if (i >= k- 1){
                sum[i-k+1] = cur;
                cur -= nums[i-k+1];
            }
        }
        for(int j = 0; j <=2; ++j){
            best = (j == 0 ? 0 : cnt[j][j*k-k][0]) + sum[j*k];
            best_index  = j*k;
            for(int i = j*k; i<=n-k; ++i){
                int tmp = (j == 0 ? 0 : cnt[j-1][i-k][0]) + sum[i];
                if(tmp > best){
                    best = tmp;
                    best_index = i;
                }
                cnt[j][i] = {best, best_index};
            }
        }

        vector<int>res(3);
        best_index = n-k;
        for(int j = 2; j>=0; --j){
            best_index = cnt[j][best_index][1];
            res[j] = best_index;
            best_index -= k; //跳过k个，因为不能重复
        }
        return res;
    }
};


class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int m = 3;
        
        vector<vector<int>>maxSum(m+1, vector<int>(n+1,0));
        vector<vector<int>>pos(m+1, vector<int>(n+1,0));
        vector<int>sum(n+1, 0); 
        
        for(int i = 0, cur = 0; i<nums.size(); ++i){
            cur += nums[i];
            if(i >= k-1){
                sum[i+1] = cur;
                cur -= nums[i-k+1];
            }
        }

        for(int i = 1; i<=m; ++i){
            for(int j = i*k; j<=n; ++j){
                
                if(maxSum[i-1][j-k] + sum[j] > maxSum[i][j-1]){
                    maxSum[i][j] = maxSum[i-1][j-k] + sum[j];
                    pos[i][j] = j - k;
                }
                else{
                    maxSum[i][j] = maxSum[i][j-1];
                    pos[i][j] = pos[i][j-1];
                }
            }
        }
        vector<int>res(m);
        for(int i = m-1, cur = n; i>=0; --i){
            res[i] = pos[i+1][cur];
            cur = res[i];
        }
 
        return res;
    }
};


//A greedy solution using three sliding windows where you keep track of the best indexes/sums as you go.
//Many people solved this problem using DP. But just three pointer is enough. It is quite good and underrated solution :)

/*

sum[0], sum[1], sum[2] 不会overlap
因为sum[0], sum[1], sum[2] 全是一起Move, 隔开的，即使全部更新，也不会有overlap
    因为idx[0][0] >= idx[1][0], 可能更新max_sum0, 不更新max_sum1
       idx [1][1] >= idx[2][1], idx[1][0] >= idx[2][0], 可能更新max_sum1, 不更新max_sum2

         2 1 2 | 3 1 2 | 5 2 1 | 2 1 7   IDX  
  sum[0]     5 |       |       |          0
  sum[1]       |     6 |       |          0  3
  sum[2]       |             8 |          0  3  6
移动一位
  sum[0]       | 6      |       |         1
  sum[1]       |        | 8     |         1  4
  sum[2]       |        |       |5        0  3  6
移动一位
  sum[0]       |    6   |       |         1
  sum[1]       |        |   9   |         1  5
  sum[2]       |        |       |   5     0  3  6
移动一位
  sum[0]       |       6|       |         1
  sum[1]       |        |     8 |         1  5
  sum[2]       |        |       |     10  1  5  9
  

 */
class Solution {
public:
        vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        // sum[k]: records the current kth subarray sum
        // max_sum[k]: records the max sum of 0th, ..., kth subarray sum 
        vector<int> sum(3, 0), max_sum(3, 0);
        vector<vector<int>> idx(3, vector<int>(3, 0));
        
        // records the index
        idx[0] = vector<int>{0};
        idx[1] = vector<int>{0, k};
        idx[2] = vector<int>{0, k, 2*k};
        
        // init the sum
        sum[0] = accumulate(nums.begin(), nums.begin() + k, 0);
        sum[1] = accumulate(nums.begin() + k, nums.begin() + 2*k, 0);
        sum[2] = accumulate(nums.begin() + 2*k, nums.begin() + 3*k, 0);
        
        // init the max_sum
        max_sum[0] = sum[0];
        max_sum[1] = sum[0] + sum[1];
        max_sum[2] = sum[0] + sum[1] + sum[2];
        
        for (int i = 1; i <= n - 3*k; ++i) {
            // update current sum
            sum[0] += nums[i+k-1] - nums[i-1];
            sum[1] += nums[i+2*k-1] - nums[i+k-1];
            sum[2] += nums[i+3*k-1] - nums[i+2*k-1];
            
            // update max_sum[0] and idx[0] if possible
            if (sum[0] > max_sum[0]) {
                max_sum[0] = sum[0];
                idx[0][0] = i;
            }
            
            // update max_sum[1] and idx[1] if possible
            if (sum[1] + max_sum[0] > max_sum[1]) {
                max_sum[1] = sum[1] + max_sum[0];
                idx[1][0] = idx[0][0];
                idx[1][1] = i+k;
            }
            
            // update max_sum[2] and idx[2] if possible
            if (sum[2] + max_sum[1] > max_sum[2]) {
                max_sum[2] = sum[2] + max_sum[1];
                idx[2][0] = idx[1][0];
                idx[2][1] = idx[1][1];
                idx[2][2] = i + 2*k;
            }
        }
        
        return idx[2];
    }

};