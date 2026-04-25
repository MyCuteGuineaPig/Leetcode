
/*
So there are two case.
Case 1. The first is that the subarray take only a middle part, and we know how to find the max subarray sum.
Case2. The second is that the subarray take a part of head array and a part of tail array.
We can transfer this case to the first one.
The maximum result equals to the total sum minus the minimum subarray sum.

*/

/*💡 Key trick

Instead of directly finding the wrap-around subarray, think:

“What if I remove a minimum subarray in the middle?”



If: tot == minSum

It means:
👉 the entire array is the minimum subarray

➡️ So total - minSum = 0
➡️ That would mean “take nothing” ❌ (invalid, must be non-empty)

So we fall back to: maxSum (largest negative number)
*/


class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int maxSum = A[0], curMax = A[0], curMin = A[0], minSum = A[0], tot = A[0];
        for(int i = 1; i<A.size(); ++i){
            curMax = max(curMax+A[i], A[i]);
            maxSum = max(maxSum, curMax);
            curMin = min(curMin + A[i], A[i]);
            minSum = min(minSum, curMin);
            tot += A[i];
        }
        if(tot == minSum) //全是负数
            return maxSum;
        return max(tot - minSum, maxSum);
    }
};


class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        int total = 0, maxSum = A[0], curMax = 0, minSum = A[0], curMin = 0;
        for (int& a : A) {
            curMax = max(curMax + a, a);
            maxSum = max(maxSum, curMax);
            curMin = min(curMin + a, a);
            minSum = min(minSum, curMin);
            total += a;
        }
        return maxSum > 0 ? max(maxSum, total - minSum) : maxSum;
    }
};


class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int curMax = 0;
        int curMin = 0;
        int maxSum = nums[0];
        int minSum = nums[0];
        int totalSum = 0;
        
        for (int num: nums) {
            // Normal Kadane's
            curMax = max(curMax, 0) + num;
            maxSum = max(maxSum, curMax);
            
            // Kadane's but with min to find minimum subarray
            curMin = min(curMin, 0) + num;
            minSum = min(minSum, curMin);
            
            totalSum += num;  
        }

        if (totalSum == minSum) {
            return maxSum;
        }
        
        return max(maxSum, totalSum - minSum);
    }
};