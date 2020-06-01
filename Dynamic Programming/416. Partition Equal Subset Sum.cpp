
/*
backtrack timeout  NOT PASS,
*/
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int tot = 0;
        for_each(nums.begin(),nums.end(),[&](int i){tot+=i;});
        if(tot & 1) return false;
        int onesum = tot/2;
        for(auto j: nums)
            if(j>onesum)
                return false;
        return backtrack(nums, onesum, 0, 0);
    }
    
    bool backtrack(vector<int>& nums, const int& onesum, int cur, int index){
        //cout<<cur<<" index "<<index<<" nums.size "<<nums.size()<<"         ";
        if(onesum == cur)
            return true;
        else if(cur > onesum)
            return false;
        for(int i = index; i<nums.size();i++){
            if(cur+nums[i]<=onesum && backtrack(nums,onesum,cur-nums[i], i+1))
                return true;
        }
        return false;
    }
};

class Solution {
public:
    bool backtrack(vector<int>& nums, int start, int target) {
        if (target <= 0) return target == 0;
        for (int i = start; i < nums.size(); i++) 
            if (backtrack(nums, i + 1, target - nums[i])) return true;
        return false;
    }
    
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        return !(sum & 1) && backtrack(nums, 0, sum >> 1);
    }
};

/*********************************ACCEPT SOLUTION IF SORT AT FIRST (DFS)*********************************/

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int tot = 0;
        for_each(nums.begin(),nums.end(),[&](int i){tot+=i;});
        if(tot & 1) return false;
        int onesum = tot/2;
        sort(nums.rbegin(),nums.rend());
        return backtrack(nums, onesum, nums[0], 1); //backtrack 要带上第一个数，否则timeout，因为不管怎么样如果可以均分两份，第一个数肯定在一份里面

        /*比如不带第一个数100, cur = 0，剩下全是，1来回来去backtrack，肯定会timeout
        [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,100]
        
        */
    }
    
    bool backtrack(vector<int>& nums, const int& onesum, int cur, int index){
        if(onesum == cur)
            return true;
        else if(cur > onesum)
            return false;
        for(int i = index; i<nums.size();i++){
            if(cur+nums[i]<=onesum && backtrack(nums,onesum,cur+nums[i], i+1))
                return true;
        }
        return false;
    }
};

/*********************************ACCEPT SOLUTION*********************************/
/*
DP
*/

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(),nums.end(),0), target = sum >> 1;
        if(sum & 1) return false;
        vector<int>dp(target+1,0);
        dp[0] = 1;
        for(auto num: nums)
            for(int i = target; i>=num; i--) //只能从target -> num, 如果num -> target 会出现一个数可多次利用情况
                dp[i] = dp[i] || dp[i-num];
        return dp[target];
        
    }
};

//BIT 
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        bitset<10001> bits(1); //10001 位bit， 第二位被设为1, 
        int sum = accumulate(nums.begin(), nums.end(), 0);
        for (auto n : nums) bits |= bits << n;
        return !(sum & 1) && bits[sum >> 1];
    }
};