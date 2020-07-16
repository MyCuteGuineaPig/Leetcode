
/*
相当于house robbery，不能同时rob两个邻居的
*/

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int values[100001]={0};
        for (int num : nums) {
            values[num] += num;
        }
        int take = 0, skip = 0;
        for (int value : values) {
            int temp = max(skip + value, take);
            skip = take;
            take = temp;
        }
        return take;
    }
};

/*
最快
*/

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        if(nums.empty())
            return 0;
        int n = *max_element(nums.begin(),nums.end());
        
        vector<int> dp(n+1,0);
        for(auto k : nums)
            dp[k]+=k;
        
        for(int i = 2; i <=n;++i) {
            dp[i] = max(dp[i-2]+dp[i], dp[i-1]);
        }
        return dp[n];
    }
};


class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        if(nums.empty())return 0;
        int n = *max_element(nums.begin(),nums.end());
        vector<int>dp(n+1,0);
        for(int i:nums)
            dp[i]+=i;
        for(int i = 2; i<=n; i++) /*take i 或者skip i*/
            dp[i] = max(dp[i]+dp[i-2],dp[i-1]);
        return dp.back();
    }
};

//2020 Bottom-up
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        vector<int>cnt(10001, 0);
        for(int i = 0; i<nums.size(); ++i)
            ++cnt[nums[i]];
        vector<int>dp(10001, 0);
        dp[1] = cnt[1];
        
        for(int i = 2; i<=10000; ++i){
            dp[i] = max(dp[i-1], dp[i-2]+cnt[i]*i);
        }
        return dp.back();
    }
};

//2020 TopDown
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        if(nums.empty())
            return 0;
        vector<int>cnt(10001, 0);
        for(int i = 0; i<nums.size(); ++i)
            ++cnt[nums[i]];
        vector<int>dp(10001, 0);
        dp[1] = cnt[1];
        return topDown(dp, cnt, 10000);
    }
    
    int topDown(vector<int>&dp, vector<int>&cnt, int i){
        if(i <= 1 || dp[i])
            return dp[i];
        return dp[i] = max(topDown(dp, cnt, i-1), topDown(dp, cnt, i-2) + cnt[i]*i);
    }
};



class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        int curr = 0, prev1 = 0, prev2 = 0,  i = 0, count = 0, key, prevNum = 0;
        
        // prev1 : stores the maximum score obtained by including the last number 
        // prev2 : stores the maximum score obtained by including the last to last number
        // curr : stores the maximum score obtained after including the current number
        // prevNum : previous number for which we included the scored, prev1 corresponds to the score
        while(i < n){
            
            // counting the number 
            key  = nums[i];
            count = 1;
            while(nums[++i] == key) count++;
            
            // if prevNum included is one less than key, then we can either take score from including prev1
            // or from adding current key score to the last to last key score
            // number correponding to prev2 is less than prevNum and thus its score can be to current Number
            if (prevNum == key - 1) curr = max(count * key + prev2, prev1);
            
            // we can simply include the prevNum with the current number
            else curr = key * count + prev1;
            
            prevNum = key;
            prev2 = prev1;
            prev1 = curr;
            
        }
        
        return curr;
    }
    
};