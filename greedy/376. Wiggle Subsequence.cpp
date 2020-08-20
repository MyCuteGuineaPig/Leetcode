/*
看有几个正负转化

*/

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if(nums.size()<=1) return nums.size();
        int i = 0;
        while(i+1<nums.size() && nums[i+1] == nums[i]) i++; //跳过相等的2
        if(i>= nums.size()-1) return 1;
        bool flag = nums[i+1] - nums[i] > 0 ? true : false; //nums[i+1] - nums[i]大于的为true，小于0为false
        int count = 2;
        for(; i+1<nums.size(); i++){
            while(i+1<nums.size() && nums[i+1] == nums[i]) i++; //跳过一样的
            if(nums[i+1] - nums[i] > 0 ^ flag){ // 上一个差和现在差 正负情况不match，++count
                flag = !flag;
                count++;
            }
        }
        return count;
    }
};


//2020
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if(nums.size()<=1) return nums.size();
        int dir = nums[1]-nums[0];
        int res = dir != 0 ? 2: 1;
        for(int i = 2; i<nums.size(); ++i){
            if(dir != 0 && dir*(nums[i] - nums[i-1]) < 0 || (dir == 0 && nums[i] - nums[i-1]!=0))
                ++res;
            if(nums[i] - nums[i-1] != 0)
                dir = nums[i] - nums[i-1];
        }
        return res;
    } 
};


class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() < 2) {
            return nums.size();
        }
        
        int length = 1, up = 0;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i - 1] < nums[i] && (up == 0 || up == 1)) {
                ++length;
                up = -1;
            } else if (nums[i - 1] > nums[i] && (up == 0 || up == -1)) {
                ++length;
                up = 1;
            }
        }

        return length;
    }
};


/*
DP,现在正 看之前点fu的个数 + 1， 现在负的 看之前点 正的数+1
For every position in the array, there are only three possible statuses for it.

up position, it means nums[i] > nums[i-1]
down position, it means nums[i] < nums[i-1]
equals to position, nums[i] == nums[i-1]
So we can use two arrays up[] and down[] to record the max wiggle sequence length so far at index i.
If nums[i] > nums[i-1], that means it wiggles up. the element before it must be a down position. so up[i] = down[i-1] + 1; down[i] keeps the same with before.
If nums[i] < nums[i-1], that means it wiggles down. the element before it must be a up position. so down[i] = up[i-1] + 1; up[i] keeps the same with before.
If nums[i] == nums[i-1], that means it will not change anything becasue it didn't wiggle at all. so both down[i] and up[i] keep the same.

*/
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        int up = 1, down = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[i - 1]) down = up + 1;
            else if (nums[i] > nums[i - 1]) up = down + 1;
        }
        return max(up, down);
    }
};