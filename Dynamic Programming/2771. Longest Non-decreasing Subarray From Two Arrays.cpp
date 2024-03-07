class Solution {
public:
    int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2) {
        vector<int>l1 = {1};
        vector<int>l2 = {1};
        int cnt = 1;
        for(int i = 1; i<nums1.size();++i){
            int l1_cur = 1;
            if(nums1[i] >= nums1[i-1]) {
                l1_cur = max(l1_cur, l1.back()+1);
            }
            if(nums1[i] >= nums2[i-1]){
                l1_cur = max(l1_cur, l2.back()+1);
            }
            int l2_cur = 1;
            if(nums2[i] >= nums1[i-1]) {
                l2_cur = max(l2_cur, l1.back()+1);
            }
            if(nums2[i] >= nums2[i-1]){
                l2_cur = max(l2_cur, l2.back()+1);
            }
            l1.push_back(l1_cur);
            l2.push_back(l2_cur);
            cnt = max(cnt, max(l1_cur, l2_cur));
        }
        return cnt;
    }
};


class Solution {
public:
    int maxNonDecreasingLength(vector<int>& A, vector<int>& B) {
        int res = 1, dp1 = 1, dp2 = 1, n = A.size(), t11, t12, t21, t22;
        for (int i = 1; i < n; ++i) {
            t11 =  A[i - 1] <= A[i] ? dp1 + 1 : 1;
            t12 = A[i - 1] <= B[i] ? dp1 + 1 : 1;
            t21 = B[i - 1] <= A[i] ? dp2 + 1 : 1;
            t22 = B[i - 1] <= B[i] ? dp2 + 1 : 1;
            dp1 = max(t11, t21);
            dp2 = max(t12, t22);
            res = max(res, max(dp1, dp2));
        }
        return res;
    }
};


class Solution {
public:
    
    
    int find(int ind,vector<int>&nums1,vector<int>&nums2,int last,vector<vector<int>>&dp)
    {
        if(ind==nums1.size())
        {
            return 0;
        }
        
        if(dp[ind][last+1]!=-1)
            return dp[ind][last+1];
        
        int ans=0;
        if(last==-1)
        {
            ans=max(ans,1+find(ind+1,nums1,nums2,0,dp));
            ans=max(ans,1+find(ind+1,nums1,nums2,1,dp));
            ans=max(ans,find(ind+1,nums1,nums2,-1,dp));
        }
        else
        {
            int val=0;
            if(last==0)
                val=nums1[ind-1];
            else
                val=nums2[ind-1];
            
            if(nums1[ind]>=val)
                ans=max(ans,1+find(ind+1,nums1,nums2,0,dp));
            
            if(nums2[ind]>=val)
                ans=max(ans,1+find(ind+1,nums1,nums2,1,dp));   
        }
        return dp[ind][last+1]=ans;
    }
    int maxNonDecreasingLength(vector<int>& nums1, vector<int>& nums2)
    {
        vector<vector<int>>dp(nums1.size(),vector<int>(3,-1));// Max value of last can be when last_num is from nums2 
                                                             //so last=1 and add 1 so max last=2
        int ans=find(0,nums1,nums2,-1,dp);
        return ans;
    }
};