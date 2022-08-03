class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        unordered_set<int> cnt(nums.begin(), nums.end());
        for(auto i: nums)
            if (i != 0)
                cnt.insert(i);
        return cnt.size();
    }
};