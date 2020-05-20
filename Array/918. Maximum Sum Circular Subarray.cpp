
/*
So there are two case.
Case 1. The first is that the subarray take only a middle part, and we know how to find the max subarray sum.
Case2. The second is that the subarray take a part of head array and a part of tail array.
We can transfer this case to the first one.
The maximum result equals to the total sum minus the minimum subarray sum.

*/

/*
Example-
1, 6, -8, 4, 4, -2
Result should be = 4 + 4 + -2 + 1 + 6 =13
Logic-
min sub array sum = -8,
Total Sum = 5
Result = 5 - (-8) = 13

3, 6, -8, 2, -4, 6, 4
Result should be = 6 + 4 + 3 + 6 =19
Logic-
min sub array sum = -8 + 2 + -4 = -10
Total Sum =9
Result = 9 - (-10) = 19


Corner case
Just one to pay attention:
If all numbers are negative, maxSum = max(A) and minSum = sum(A).
In this case, max(maxSum, total - minSum) = 0, which means the sum of an empty subarray.
According to the deacription, We need to return the max(A), instead of sum of am empty subarray.
So we return the maxSum to handle this corner case.
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