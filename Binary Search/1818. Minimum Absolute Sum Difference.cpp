class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        set<int>st(nums1.begin(), nums1.end());
        long res = 0;
        long mod = pow(10, 9) + 7;
        long gain = 0;
        for(int i = 0; i<nums1.size(); ++i){
            long cur = abs(nums1[i] - nums2[i]);
            auto it = st.upper_bound(nums2[i]);
            if(it!= st.end())
                gain = max(gain, cur - abs(nums2[i] - *it));
            if(it != st.begin())
                gain = max(gain, cur - abs(nums2[i] - *prev(it)));
            res = (res + cur) % mod;
        }
        return (res - gain)% mod;
    }
};


class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        long origDiff = 0, n = size(nums1), minDiff;
        // calculating original difference without any replacement
        for(int i = 0; i < n; i++) origDiff += abs(nums1[i] - nums2[i]);
        minDiff = origDiff;
        // sorted nums1 needed for using binary search
        vector<int>arr = nums1;
        sort(begin(arr), end(arr));        
        for(int i = 0; i < n; i++){
            // find the newDiff after replacement
            long newDiff = origDiff - abs(nums1[i] - nums2[i]) + abs(bs(arr, nums2[i]) - nums2[i]);
            // minDiff will store minimum possible sum of difference after replacements
            minDiff = min(minDiff, newDiff);
        }
        return minDiff % 1000000007;
    }
    // bs will return the element closest to k in arr.
    int bs(vector<int>& arr, int k){               
        int n = arr.size(), l = 0, r = n - 1, closest;
        while(l < r){
            int m = (l + r) / 2;
            if(arr[m] > k) r = m;            
            else l = m + 1;              
        }
        closest = arr[l];
        if(l - 1 >= 0 && abs(arr[l - 1] - k) < abs(arr[l] - k)) closest = arr[l - 1];
        return closest;
    }
};