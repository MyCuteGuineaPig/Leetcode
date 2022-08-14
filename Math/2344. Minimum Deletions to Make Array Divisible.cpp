/*

def gcd(a, b):
 if a == b:
 return a
 if a > b:
 gcd(a – b, b)
 else:
 gcd(a, b – a)


divides all the elements of numsDivide"
equals to
"divides gcd of all the elements of numsDivide"
where gcd is the greatest common divisor.

So the first step, find out the gcd of numsDivide,
then sort input nums A,
and find out the smallest element A[i] in A divides gcd.

We need to remove all elements smaller than A[i].
If no such A[i], return -1

*/


class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& numsDivide) {
        sort(nums.begin(), nums.end());
        int div = reduce(numsDivide.begin(), numsDivide.end(), numsDivide[0], [](int a, int b){return gcd(a, b);}); //a is the accumulate int, b is cur from numsDivide
        for(int i = 0; i<nums.size() && nums[i] <= div; ++i){
            if(div % nums[i] == 0)
                return i;
        }
        return -1;
    }
};



class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& divs) {
        int div = reduce(begin(divs), end(divs), divs[0], [](int a, int b){ return gcd(a, b); });
        int mn = INT_MAX;
        for (int n : nums)
            mn = min(mn, div % n == 0 ? n : INT_MAX);
        return mn == INT_MAX ? -1 : count_if(begin(nums), end(nums), [&](int n){ return n < mn; });
    }
};