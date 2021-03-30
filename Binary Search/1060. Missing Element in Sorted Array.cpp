class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int l = 0, h = nums.size();
        while(l < h) {
            int m = l + (h - l) / 2;
            nums[m] - m - k >= nums[0] ? h = m : l = m + 1;
        }
        return nums[0] + l + k - 1;
    }
};