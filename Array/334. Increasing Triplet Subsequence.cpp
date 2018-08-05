/*
334. Increasing Triplet Subsequence

Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.

Formally the function should:

Return true if there exists i, j, k 
such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.
Note: Your algorithm should run in O(n) time complexity and O(1) space complexity.

Example 1:

Input: [1,2,3,4,5]
Output: true
Example 2:

Input: [5,4,3,2,1]
Output: false

Input: [5,1,5,5,2,5,4]
Output: false

*/


/*
用两个数表示 当前最小c 和第二小的数b，

如果新的 a <= b 更新最小的

如果当前数 a<=c, 更新第二小的

如果当前数 a > b > c，return true


这不用怕新出来的数更小

新的数小于 c, 
比如 [10,9,4,7,0,8] 到0，更新c，因为第三大的数要大于b （a>b)，所以当c设为更小数的时候，不用担心不成立，
因为 b > c, 新的c小于原来的c，但是原来的c和新的c都小于b，如果判断为true，不管怎么样，必须满足 a>b

更新b为更小的数，此时 a> c, 更新b，所以更利于之后的C


*/


class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int c = numeric_limits<int>::max(), b = numeric_limits<int>::max();
        for(auto a : nums){
            if(a<=c) c = a; //为了避免同样的数，比如[1,1,1,1]
            else if (a<=b) b = a;
            else return true;
        }
        return false;
    }
};



// Time:  O(n * logk)
// Space: O(k)
// Generalization of k-uplet.
class Solution_Generalization {
public:
    bool increasingTriplet(vector<int>& nums) {
        return increasingKUplet(nums, 3);
    }

private:
    bool increasingKUplet(const vector<int>& nums, const size_t k) {
        vector<int> inc(k - 1, numeric_limits<int>::max());
        for (const auto& num : nums) {
            auto it = lower_bound(inc.begin(), inc.end(), num);
            if (distance(inc.begin(), it) >= k - 1) {
                return true;
            }
            *it = num;
        }
        return k == 0;
    }
};