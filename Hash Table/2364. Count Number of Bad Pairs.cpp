/*
The real Equation: ( j - i ) != ( A[j] - A[i] )
The simple and more intuitive form of above equation: ( j - A[j] ) != ( i - A[i] )
*/

class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        unordered_map<long long,long long>mp;
        long long res = 0;
        for(int i = 0; i<nums.size(); ++i)
            res += i - mp[i - nums[i]]++;
        return res;
    }
};


class Solution {
public:
    long long countBadPairs(vector<int>& a,long cnt=0) {
        unordered_map<int,int> mp;
        int n=size(a);
        for(int i=0;i<n;i++)
            cnt+= mp[i-a[i]]++;
        return 1L*n*(n-1)/2 - cnt;
    }
};