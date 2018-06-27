/*
473. Matchsticks to Square

Remember the story of Little Match Girl? By now, you know exactly what matchsticks the little match girl has, 
please find out a way you can make one square by using up all those matchsticks. You should not break any stick, 
but you can link them up, and each matchstick must be used exactly one time.

Your input will be several matchsticks the girl has, represented with their stick length. Your output will either be true or false, 
to represent whether you could make one square using all the matchsticks the little match girl has.

Example 1:
Input: [1,1,2,2,2]
Output: true

Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
Example 2:
Input: [3,3,3,3,4]
Output: false

Explanation: You cannot find a way to form a square with all the matchsticks.
Note:
The length sum of the given matchsticks is in the range of 0 to 10^9.
The length of the given matchstick array will not exceed 15.

*/

class Solution {
public:
    bool makesquare(vector<int>& nums) {
        if(nums.empty()) return false;
        int sum = accumulate(nums.begin(), nums.end(),0);
        if(sum % 4)  return false;
        sort(nums.begin(),nums.end(),[](int a, int b){return a>b;});
        const int target = sum / 4;
        vector<int>used(4);
        return helper(used, nums, target, 0);
    }
    
    bool helper(vector<int>& used, const vector<int>& nums, const int& target, int ind){
        if(ind == nums.size()) {
            return used[0] == used[1] && used[1] == used[2] && used[2] == used[3];
        }
        for(int i = 0; i<4; i++){
            if(used[i] + nums[ind] <= target){
                int j = i-1;
                while(j>=0){
                    if (used[j] == used[i]) break;
                    j--;
                }
                if(j == -1){
                    used[i] += nums[ind];
                    if(helper(used, nums, target, ind+1))
                        return true;
                    used[i] -= nums[ind];
                }
            }
        }
        return false;
    }
};