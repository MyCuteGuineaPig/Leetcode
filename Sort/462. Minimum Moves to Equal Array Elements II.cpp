class Solution {
public:
    int minMoves2(vector<int>& nums) {
        nth_element(nums.begin(), nums.begin()+nums.size()/2, nums.end());
        int std = 0, median = *(nums.begin()+nums.size()/2);
        for(auto i: nums)
            std += max(i - median, median - i);
        return std;
    }
};
