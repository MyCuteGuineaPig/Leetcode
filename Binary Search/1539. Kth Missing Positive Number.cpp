class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int l = 0, r = arr.size() ;
        while (l< r){
            int mid = l + (r-l)/2;
            if (arr[mid] - (mid + 1) < k)
                l = mid + 1;
            else 
                r = mid;
        }
        return l+k ; // 比l小的所有index都不满足,
            // arr[l] - (l + 1) >= k,   
            // l 前面已经有 l 个数满足条件 即不是缺失的数,
        // 所以 l + k 就是第k个缺失的正整数
    }
};