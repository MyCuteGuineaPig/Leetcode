/*
228. Summary Ranges

Given a sorted integer array without duplicates, return the summary of its ranges.

Example 1:

Input:  [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]
Explanation: 0,1,2 form a continuous range; 4,5 form a continuous range.
Example 2:

Input:  [0,2,3,4,6,8,9]
Output: ["0","2->4","6","8->9"]
Explanation: 2,3,4 form a continuous range; 8,9 form a continuous range.

*/


class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string>res;
        for(int start = 0, i = 1; i<=nums.size();i++){
            if(i==nums.size() || nums[i]!=nums[i-1]+1){
                if(i-start==1) res.push_back(to_string(nums[start]));
                else res.push_back(to_string(nums[start]) + "->"+to_string(nums[i-1]));
                start = i;
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> result;
        int i = 0;
        while (i < nums.size()) {
            int val = nums[i];
            while ((i + 1 < nums.size()) && nums[i + 1] == nums[i] + 1) ++i;
            if (nums[i] != val) {
                string tmp;
                tmp = std::to_string(val) + "->" + std::to_string(nums[i]);
                result.push_back(tmp);
            } else result.push_back(std::to_string(nums[i]));
            ++i;
        }
        return result;
    }
};