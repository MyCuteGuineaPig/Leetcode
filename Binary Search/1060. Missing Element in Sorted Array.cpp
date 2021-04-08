class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int l = 0, h = nums.size();
        while(l < h) {
            int m = l + (h - l) / 2;
            nums[m] - m - k >= nums[0] ? h = m : l = m + 1; //A[0] + mid + k <= nums[mid]
        }
        /*
 When search terminates, lo is the smallest index value such that A[lo] covers the projection, 
 and we have A[0] + lo + k <= A[lo], or we have edge case where lo == len(A)       
        
        */
        return nums[0] + l-1 + k;
    }
};


class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int l = 0, r = nums.size()-1;
        auto f = [&](int i){
          return   nums[i] - nums[0] -i;
        };
        while(l < r){
            int mid = (l + r)/2;
            if(f(mid)< k)
                l = mid + 1;
            else
                r = mid;
        }
        if(f(l) < k)
            return nums[l] +  k - f(l);
        return nums[l-1] +  k -f(l-1 );
    }
};