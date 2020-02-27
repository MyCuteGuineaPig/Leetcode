/*
698. Partition to K Equal Sum Subsets

Given an array of integers nums and a positive integer k, find whether
 it's possible to divide this array into k non-empty subsets whose sums are all equal.

Example 1:
Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
Output: True
Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
Note:

1 <= k <= len(nums) <= 16.
0 < nums[i] < 10000.


*/

//BackTrack with loop buckets
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if( sum % k != 0) 
            return false;
        int avg = sum / k;
        for(auto i: nums) 
            if(i > avg)
                return false;
        sort(nums.begin(), nums.end(), greater<int>()); //需要sort 不sort 会TLE
     //Always start from big numbers for this kind of question, just by doing it yourself for
     //a few times you will find out that the big numbers are the easiest to place.
        vector<int>buckets(k, avg);
        return backTrack(nums, k, 0, buckets);
    }

    bool backTrack(vector<int>&nums, const int& k, int start, vector<int>&buckets){
        if(start == nums.size()) 
            return true;

        for(int i = 0; i < k; ++i)
        {
            if(buckets[i] >= nums[start])
            {
                buckets[i] -= nums[start];
                if (backTrack(nums, k, start +1, buckets))
                    return true;
                buckets[i] += nums[start];
            }
        }
        return false;
    }
};


//BackTrack with loop nums
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for_each(nums.begin(),nums.end(),[&](int a){sum+= a;});
        if(sum%k) return false;
        sum /= k;
        sort(nums.begin(),nums.end(),[](int a, int b){return a>b;});
        return backtrack(nums,k, 0,sum,sum);
    }
    
    bool backtrack(vector<int>& nums, int k, int begin,int rem, const int & sum){
        if(rem == 0){
            k--;
            rem = sum;
        }
        if(k == 0) 
            return true;
        for(int i = begin; i<nums.size(); i++){
            if(nums[i]<=rem){
                swap(nums[i],nums[begin]);
                if(backtrack(nums,k,begin+1,rem-nums[begin],sum)) return true;
                swap(nums[i],nums[begin]);
            }
            if(nums[i]>sum) return false;
        }
        return false;
    }
};




class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for_each(nums.begin(),nums.end(),[&](int a){sum+= a;});
        if(sum%k) return false;
        sum /= k;
        //sort(nums.begin(),nums.end(),[](int a, int b){return a>b;});
        return backtrack(nums,k,0,sum,sum);
    }
    
    bool backtrack(vector<int>& nums, int k, int begin, int rem, const int & sum){
        if(rem == 0)
            return backtrack(nums,k-1, 0, sum, sum);
        if(k == 0) 
            return true;
        for(int i = begin; i<nums.size(); i++){
            if(nums[i]>0 && nums[i]<=rem){
                nums[i] *= -1;
                if(backtrack(nums,k, i+1, rem+nums[i], sum)) return true;
                nums[i] *= -1;
            }
            if(nums[i]>sum) return false;
        }
        return false;
    }
};


//DP, slower than DFS 
//Time Complexity : 0(N*2^N)
//Space COmplexity: 0(2^N)
/*
dp[1] 表示只含有nums[1]能不能组成 分成k份 

dp[5], 101 表示只有 nums[1], nums[3] 能不能分成k 分 

dp[i] indicates whether array of length i can partitioned into k subsets of equal sum. 
Using this technique, the last index of this dp array
will tell whether the whole array can be partitioned into k subsets of equal sum.

total[i] stores the sum of subset with sum less than equal to target sum 
(total sum/k why? because we need to split array into k subset).


这么做肯定有解的原因,下面位置都用二进制表示

比如 位置在 [1,3,4,5,6](二进制是 111101) 有解, dp[111101] = true, 最后index = 1(index = 10), nums[2] 
如果 sums[111101] % target + nums[10] 只能==target, 否则 sum(list) 不能被 target 整除, 之前条件就早已经return False 

如果 dp[011111], dp[101111], dp[110111], dp[111011], dp[111101], dp[111110] 都没有解， 都是false, 那么dp[111111]肯定也是false
    

*/
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        if(nums.empty()) return false;
        int n = nums.size(), target = 0;
        vector<bool> dp(1 << n, false); dp[0] = true;  
        vector<int> sum(1 << n, 0);
        
        for(int &x: nums) target += x;
        if(target % k) return false;
        target /= k;
        
        for(int i = 0; i < (1 << n) -1; ++i){ //不用到 1<<n -1, 因为1<<n -1, 在之前就已经set 
            if(dp[i] == false) continue;
            //int remainder = target - sum[i] % target;
            for(int j = 0; j < n; ++j){
                if(i & (1 << j) || nums[j] + sum[i] % target > target) continue; 
             //i & (1 << j) 比如 binary i = 10101,  1<<j (j=2) binary 100, 表示dp, sum已经包含了j, 
                int new_state = i | (1 << j);
                dp[new_state] = true;
                sum[new_state] = sum[i] + nums[j];
            }
        }
        
       for(int i = 0; i < (1 << n); ++i){
            cout<<i<<" dp "<<dp[i]<<" sum "<<sum[i]<<endl;
        }
     
        return dp[(1 << n) - 1];
    }
};


/*

Example 

[4,3,2,5]
2

0 dp 1 sum 0   
1 dp 1 sum 4 
2 dp 1 sum 3
3 dp 1 sum 7
4 dp 1 sum 2
5 dp 1 sum 6  101
6 dp 1 sum 5  110
7 dp 1 sum 9  111  # (4 + 3) % 7 = 0, 2 + 7 = 9 < target 
8 dp 1 sum 5
9 dp 0 sum 0  1001  4 + 5 > target
10 dp 0 sum 0 1010 3 + 5 > target
11 dp 1 sum 12  1011  4+3 = 7,  7%7 + 5 < target
12 dp 1 sum 7   1100 2 + 5 = 7
13 dp 1 sum 11  1101 2+5 = 7,  7%7 + 4 < target
14 dp 1 sum 10  1110 2+5 = 7， 7%7 + 2　< target
15 dp 1 sum 14
*/
