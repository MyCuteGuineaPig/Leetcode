/*
Binary Search Hint:
tail[i] 存的是递增subarray长度为i+1，组成该长度最小的尾部数字, 
    比如tail = [2,5] 代表当increasing subarray长度为2是，组成递增subarray 末尾最后一位数最小是5 

 */

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        vector<int>dp(nums.size(),1);
        for(int i = 0; i<nums.size();i++)
            for(int j = 0; j<i;j++)
                if(nums[i]>nums[j])
                    dp[i] = max(dp[i],dp[j]+1);
        return *max_element(dp.begin(),dp.end());
    }
};



/*
dp with memoization 
*/
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        vector<int>dp(nums.size(),-1);
        for(int i = 0; i<nums.size();i++)
            helper(nums,dp,i);
        return *max_element(dp.begin(),dp.end());
    }

    int helper(vector<int>& nums, vector<int> &dp, int i){
        if(dp[i]!=-1)
            return dp[i];
        dp[i] = 1;
        for(int j = i-1; j>=0; j--){
            if(nums[i]>nums[j])
                dp[i] = max(dp[i], helper(nums,dp,j)+1);
        }
         return dp[i];
    }

};


/*
tails is an array storing the smallest tail of all increasing subsequences with length i+1 in tails[i].
For example, say we have nums = [4,5,6,3], then all the available increasing subsequences are:

len = 1   :      [4], [5], [6], [3]   => tails[0] = 3
len = 2   :      [4, 5], [5, 6]       => tails[1] = 5
len = 3   :      [4, 5, 6]            => tails[2] = 6
We can easily prove that tails is a increasing array. Therefore it is possible to do a binary search 
in tails array to find the one needs update.

Each time we only do one of the two:

(1) if x is larger than all tails, append it, increase the size by 1
(2) if tails[i-1] < x <= tails[i], update tails[i]
Doing so will maintain the tails invariant. The the final answer is just the size.
*/

/*
dp[i] 存的是 longest increasing array 长度为len = i+1，最小的tail数字
比如dp[2,5] 代表当长度为1时，长度为1是[2], 当increasing subarray长度为2是，组成subarray 末尾最后一位数最小是5 
*/

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int>tail;
        for(int n : nums){
            int i = 0, j = tail.size();
            while(i<j){
                int mid = i + (j-i)/2;
                if(tail[mid]<n)
                    i = mid +1;
                else 
                    j = mid;
            }
            if(i>=tail.size())
                tail.push_back(n);
            else 
                tail[i] = n;
        }
        return tail.size();
    }
};


/*

nums = [8, 1, 6, 2, 3, 10]. 

Let's try to build an increasing subsequence starting with an empty one: sub = [].

8 -> sub = [8] (8 is the smallest tail of all increasing subsequences with length 1)
1 -> sub = [1] (1 is the smallest tail of all increasing subsequences with length 1)  
可以舍弃8，因为1更小，后续的subsequence更有可能是increasing的 

6 -> sub = [1, 6] (6 is the smallest tail of all increasing subsequences with length 2)


One thing to add: this algorithm does not always generate a valid subsequence of the input, 
but the length of the subsequence will always equal the length of the longest increasing subsequence.
For example, with the input [3, 4, 5, 1], at the end we will have sub = [1, 4, 5],
 which isn't a subsequence, but the length is still correct. 


4. Why the lower_bound replacement is safe
You might wonder: "Does replacing an element in the middle of tail break the subsequence?"

The key is that the tail vector does not store the actual LIS. 
It is a conceptual tool. Even if we replace a value in tail that technically appeared 
later in the original array than the values following it in tail, the length remains valid.

Example of the "replacement" logic:
Input: [10, 20, 30, 5]

tail = [10]

tail = [10, 20]

tail = [10, 20, 30]

n = 5: tail becomes [5, 20, 30]

Even though [5, 20, 30] is not a valid subsequence of the input (5 came last), 
the length 3 is still correct because the "30" was originally 
put there by the valid sequence [10, 20, 30]. 
Replacing the 10 with 5 just prepares the array for a potential future sequence like [5, 6, 7, 8].


*/

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int>tail;
        for(int n : nums){
            if(tail.empty() || tail.back()<n)
                tail.push_back(n);
            else {
                auto it = lower_bound(tail.begin(),tail.end(), n);
                *it = n;
            }
        }
        return tail.size();
    }
};



class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> r;
        
        for(auto v : nums) {
            auto p = std::lower_bound(r.begin(), r.end(), v);
            if (r.end() == p)
                r.push_back(v);
            else
                *p = v;
        }
        return r.size();
    }
};




class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.size() == 0)
            return nums.size();

        vector<int>::iterator m = nums.begin();  // m will mark the virtual "S.end()".
        for (int& val : nums) {
            auto it = lower_bound(nums.begin(), m, val);
            *it = val;
            if (it == m)
                m++;
        }

        return m - nums.begin();
    }
};