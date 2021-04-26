class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int res = 1, start = 0;
        long cur = 0;
        sort(nums.begin(), nums.end());
        for(int i = 1; i<nums.size(); ++i){
            cur += static_cast<long>( (nums[i] - nums[i-1])) * (i-start); //把之前每个数都增加到 nums[i]
            while(cur > k && start <= i){
                cur -= (nums[i] - nums[start++]);
            }
            res = max(res, i - start + 1);
        }
        return res;
    }
};
/*

valid windows

k  >= windows_size * max - sum

k + sum >= windows_size * max

*/


// (Non-shrinkable)
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int i = 0, j;
        sort(nums.begin(), nums.end());
        for (j = 0; j < nums.size(); ++j) {
            k += nums[j];
            if (k < (long)nums[j] * (j - i + 1))
                k -= nums[i++];
        }
        return j - i;
    }
};

//(Shrinkable)
class Solution {
public:
    int maxFrequency(vector<int>& A, int k) {
        sort(begin(A), end(A));
        long i = 0, N = A.size(), ans = 1, sum = 0;
        for (int j = 0; j < N; ++j) {
            sum += A[j];
            while ((j - i + 1) * A[j] - sum > k) sum -= A[i++];
            ans = max(ans, j - i + 1);
        }
        return ans;
    }
};