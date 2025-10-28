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

//2025
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int l = 0; 
        long diff = 0;
        int res = 0;
        for(int i = 0; i < n; ++i){
            if(i > 0 && nums[i] != nums[i-1])
                diff += (long)(nums[i]-nums[i-1])*(i-l);
            while (diff > k) {
                diff -= nums[i] - nums[l++];
            }
            res = max(res, i-l+1);
        }
        return res;
    }
};

//2025
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int l = 0; 
        long diff = 0;
        int res = 0;
        for(int i = 0; i < n; ++i){
            if(i > 0 && nums[i] != nums[i-1])
                diff += (long)(nums[i]-nums[i-1])*(i-l);
            if (diff > k) {
                diff -= nums[i] - nums[l++];
            }
        }
        return n-l;
    }
};
/*

valid windows

k  >= windows_size * max - sum

k + sum >= windows_size * max


For every new element A[j] to the sliding window,
Add it to the sum by sum += A[j].
Check if it'a valid window by
sum + k < (long)A[j] * (j - i + 1)

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