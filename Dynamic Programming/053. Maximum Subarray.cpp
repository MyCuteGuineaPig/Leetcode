/*

53. Maximum Subarray

https://leetcode.com/problems/maximum-subarray/description/

Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

*/


class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        vector<int>dp(nums.size(),0);
		dp[0] = nums[0];
		int maxsum = nums[0];
		for(int i = 1; i<nums.size();i++){
			dp[i] = dp[i-1] + nums[i] > nums[i] ? dp[i-1] + nums[i]: nums[i]; 
			// dp 中存入到i为止（包括i）最大的sum， 如果dp【i]+nums[i] 小于nums[i] 
			// 代表现在只包括nums[i] 是最大sum
			maxsum = maxsum > dp[i] ? maxsum : dp[i]; // 到i为止最大的sum 和 maxsum 对比
		}
		return maxsum;
    }
};

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0;
        int mi = 0, res = nums[0], sum =0; //mi sum 需要是0, 不能是nums[0], e.g. [1,2] 的maxsum = 3
        for(int i = 0; i<nums.size(); ++i){
            sum += nums[i];
            res = max(res, sum - mi);
            mi = min(mi, sum);  
        }
        return res;
    }
};



class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0;
        for(int i = 1; i<nums.size(); ++i){
            if(nums[i-1] > 0)
                nums[i] += nums[i-1];
        }
        return *max_element(nums.begin(), nums.end());
    }
};

//Divide and Conquer
/*
Divide and Conquer

The Divide-and-Conquer algorithm breaks nums into two halves and find the maximum subarray sum in them recursively. 
Well, the most tricky part is to handle the case that the maximum subarray spans the two halves. 
For this case, we use a linear algorithm: starting from the middle element and move to both ends (left and right ends), 
record the maximum sum we have seen. 
In this case, the maximum sum is finally equal to the middle element plus the maximum sum of moving leftwards and the maximum sum of moving rightwards.

*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        return maxSubArray(nums, 0, nums.size() - 1);
    }
private:
    int maxSubArray(vector<int>& nums, int l, int r) {
        if (l > r) {
            return INT_MIN;
        }
        int m = l + (r - l) / 2; 
	    
        int lmax = maxSubArray(nums, l, m - 1);
        int rmax = maxSubArray(nums, m + 1, r);
	    
	int ml = 0, mr = 0;
	    
        for (int i = m - 1, sum = 0; i >= l; i--) {
            sum += nums[i];
            ml = max(sum, ml);
        }
        for (int i = m + 1, sum = 0; i <= r; i++) {
            sum += nums[i];
            mr = max(sum, mr);
        }
        return max(max(lmax, rmax), ml + mr + nums[m]);
    }
};


/*

Step1. Select the middle element of the array.
So the maximum subarray may contain that middle element or not.

Step 2.1 If the maximum subarray does not contain the middle element, then we can apply the same algorithm 
to the the subarray to the left of the middle element and the subarray to the right of the middle element.

Step 2.2 If the maximum subarray does contain the middle element, then the result will be simply 
the maximum suffix subarray of the left subarray plus the maximum prefix subarray of the right subarray

Step 3 return the maximum of those three answer.

Here is a sample code for divide and conquer solution. 
Please try to understand the algorithm before look at the code
*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0;
        return maxSubArrayHelperFunction(nums,0,nums.size()-1);
    }
    
    int maxSubArrayHelperFunction(const vector<int>& A, int left, int right) {
        
        if(right == left) return A[left];
        int middle = (left+right)/2;
        int leftans = maxSubArrayHelperFunction(A, left, middle);
        int rightans = maxSubArrayHelperFunction(A, middle+1, right);
	    
        int leftmax = A[middle]; // 包括A[middle] 左侧最大值
        int rightmax = A[middle+1]; //A[middle+1] 右侧最大值
        int temp = 0;
        for(int i=middle;i>=left;i--) {
            temp += A[i];
            if(temp > leftmax) leftmax = temp; 
        }
        temp = 0;
        for(int i=middle+1;i<=right;i++) {
            temp += A[i];
            if(temp > rightmax) rightmax = temp;
        }
        return max(max(leftans, rightans),leftmax+rightmax); //leftmax + rightmax：包括中间数的最大的值
    }
};
