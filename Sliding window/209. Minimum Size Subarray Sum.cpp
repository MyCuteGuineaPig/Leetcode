/*
209. Minimum Size Subarray Sum


Given an array of n positive integers and a positive integer s, 
find the minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.

Example: 

Input: s = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: the subarray [4,3] has the minimal length under the problem constraint.
Follow up:
If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n). 



*/


//Slding Window O(n)
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int res = nums.size()+1, cur = 0;
        for(int i = 0, j = 0; i<nums.size(); i++){
            cur += nums[i];
            while(cur>=s){
                res = min(res,i-j+1);
                cur -= nums[j++];
            }
        }
        return res == nums.size()+1? 0 : res;
    }
};


class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        if(nums.size() == 0) return 0;
        int minLength = nums.size() + 1;
        int lo = 0, hi = 0, curSum = nums[0];
        while(hi < nums.size()) {
            if(curSum < s) {
                hi++;
                curSum += nums[hi];
                continue;
            }
            if(hi - lo + 1 < minLength) minLength = hi - lo + 1;
            curSum -= nums[lo];
            lo++;
        }
        return minLength > nums.size() ? 0 : minLength;
    }
};


class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size(), left = 0, right = 0, sum = 0, minlen = INT_MAX;
        while (right < n) {
            do sum += nums[right++];
            while (right < n && sum < s);
            while (left < right && sum - nums[left] >= s)
                sum -= nums[left++];
            if (sum >= s) minlen = min(minlen, right - left);
        }
        return minlen == INT_MAX ? 0 : minlen;
    }
};

//Binary Search  O(nlogn)
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int l = 1, r = nums.size();
        while(l<=r){ //不能用 l < r 因为l可以等于nums.size(), 但是当l == r == nums.size()时候，不代表l就是解，可能所有数相加都小于s
            int mid = (l+r)>>1;
            for(int i = 0, sum = 0; i<nums.size();i++){
                sum += nums[i];
                if(i>=mid - 1 && sum >= s){
                    r = mid-1; 
                    break;
                }
                if(i>=mid-1) sum -= nums[i-mid+1];//减去之前的
                if(i == nums.size()-1) l = mid + 1; //到最后了，没发现解
            }
        }
        return l == nums.size()+1 ?  0: l;
    }
};




class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int l = 1, r = nums.size();
        while(l<=r){ //不能用 l < r 因为l可以等于nums.size(), 但是当l == r == nums.size()时候，不代表l就是解，可能所有数相加都小于s
            int mid = (l+r)>>1;
            for(int i = 0, sum = 0; i<nums.size();i++){
                sum += nums[i];
                if(i>=mid - 1 && sum >= s){
                    r = mid-1; 
                    break;
                }
                if(i>=mid-1) sum -= nums[i-mid+1];//减去之前的
                if(i == nums.size()-1) l = mid + 1; //到最后了，没发现解
            }
        }
        return l == nums.size()+1 ?  0: l;
    }
};


class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int res = nums.size()+1;
        vector<int> sum_from_start(nums.size() + 1);
        partial_sum(nums.begin(),nums.end(), sum_from_start.begin()+1);
        for(int i = 0; i<nums.size();i++){
            auto end_it = lower_bound(sum_from_start.begin()+i, sum_from_start.end(), sum_from_start[i]+s);
            if(end_it!= sum_from_start.end()){
                res = min(res, static_cast<int>(end_it - sum_from_start.cbegin())-i);
            }
        }
        return res == nums.size()+1 ?  0: res;
    }
};