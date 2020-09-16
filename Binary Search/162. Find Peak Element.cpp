
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int low = 0, high = nums.size()-1;
        while(low<high){
            int mid = low + (high-low)/2;
            int mid2 = mid+1;
            if(nums[mid]<nums[mid2])
                low = mid2;
            else
                high = mid;
        }
        return low;
    }
};


class Solution {
public:
    int findPeakElement(const vector<int> &num) 
    {
        return helper(num,0,num.size()-1);
    }
    
    int helper(const vector<int> &num, int low, int high){
        if(low>=high) return low;
        int mid1 = (low+high)/2;
        int mid2 = mid1+1;
        if(num[mid1] < num[mid2])
            return helper(num,mid2,high);
        else
            return helper(num,low,mid1);
    }
};


