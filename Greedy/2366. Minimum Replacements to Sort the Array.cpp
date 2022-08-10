/*
Reversely iterate the array A.
x is the current upper bound.
Initiliza x with a big enough value.

For element A[i],
If A[i] % x == 0,
then we can divide A[i] all into x with count k = A[i] / x.
with k - 1 operations,
the upper bound is still x

If A[i] % x > 0,
then we can divide A[i] all into x with count k = A[i] / x + 1.
with k - 1 operations,
the upper bound is A[i] / k. 

? why this work for A[i] % x > 0
因为要最小的数最大， 比如A[i] = 10, x = 4， 2 4 4 是一种分发，3 3 4 是一种分发
已知必须要分出3个数，那么最小的数不能大于， 10 / 3 = 3

*/

class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        if (nums.size() <= 1) return 0;
        long last = nums.back();
        long step = 0;
        for(int i = nums.size()-2; i>=0; --i){
            if (last < nums[i]) {
                long curStep = nums[i]/ last + (nums[i] % last != 0);
                last = nums[i] % last == 0 ? last :  nums[i]/curStep;
                step += (curStep - 1);
            } else {
                last = nums[i];
            } 
        }
        return step;
    }
};

class Solution {
public:
    long long minimumReplacement(vector<int>& nums) {
        long n = nums.size(), x = 1e9, res = 0, k;
        for (int i = n - 1; i >= 0; --i) {
            k = (nums[i] + x - 1) / x;
            x = nums[i] / k;
            res += k - 1;
        }
        return res;
    }
};