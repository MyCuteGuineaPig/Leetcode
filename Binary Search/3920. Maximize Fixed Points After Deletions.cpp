/*

1. Handling Two Constraints SimultaneouslyTo pick two elements to be fixed points, 
they must satisfy two rules:

Rule A (Relative Order): The values must be strictly increasing ($val_i < val_j$).
 If they weren't, the one with the smaller value would have to appear after the one with the larger value, 
 which is impossible since we only delete elements and never swap them.
 
Rule B (Available Deletions): The number of deletions required for the second element
 ($d_j$) must be at least the number of deletions required for the first ($d_i$). 
 You can't "un-delete" an element as you move from left to right.

*/

class Solution {
public:
    int maxFixedPoints(vector<int>& nums) {
        vector<pair<int,int>>candidates;
        for(int i = 0; i < nums.size(); ++i) {
            if(i>= nums[i]) {
                candidates.push_back({i - nums[i], nums[i]});
            }
        }
        sort(candidates.begin(), candidates.end());
        vector<int>l;
        for(int i = 0; i <candidates.size(); ++i ){
            auto [_, val] = candidates[i];
            auto it = lower_bound(l.begin(), l.end(), val);
            if (it == l.end()) {
                l.push_back(val);
            } else {
                *it = val;
            }
        }

        return l.size();
    }
};