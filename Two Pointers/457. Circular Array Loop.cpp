/*
457. Circular Array Loop
You are given an array of positive and negative integers. 
If a number n at an index is positive, then move forward n steps.
Conversely, if it's negative (-n), move backward n steps. 
Assume the first element of the array is forward next to the last element, 
and the last element is backward next to the first element. 
Determine if there is a loop in this array.
A loop starts and ends at a particular index with more than 1 element along the loop. 
The loop must be "forward" or "backward'.

Example 1: Given the array [2, -1, 1, 2, 2], there is a loop, from index 0 -> 2 -> 3 -> 0.

Example 2: Given the array [-1, 2], there is no loop.

Note: The given array is guaranteed to contain no element "0".

Can you do it in O(n) time complexity and O(1) space complexity?

 [-2, 1, -1, -2, -2] gives false

*/



class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        if(nums.empty()) return false;
        int slow = 0, fast = 0, n = nums.size();
        for(int i = 0; i<nums.size();i++){
            if(nums[i] == 0) 
                continue;
            slow = fast = i;
            while(nums[next(nums,slow)]*nums[i]>0 && nums[next(nums,fast)]*nums[i]>0
                 && nums[next(nums,next(nums,fast))]*nums[i]>0) { //保证同方向
                //cout<<" i "<<i<<" slow "<<slow<<" fast "<<fast<<endl;
                slow = next(nums,slow);
                fast = next(nums,next(nums,fast));
                //cout<<" endi "<<i<<" slow "<<slow<<" fast "<<fast<<endl;
                if(slow == fast ){
                    if (slow==next(nums,slow)) { cout <<" in "<<endl; break;}
                    return true;
                }
            }
            slow = i;
            int val = nums[i];
            // loop not found, set all element along the way to 0
            while(nums[slow]*val>0){
                int temp = next(nums,slow);
                nums[slow] = 0;
                slow = temp;
            }
        }
        return false;
    }
    
    int next(vector<int>&nums, int i){
        return (nums[i]+i)%nums.size();
    }
};



class Solution {
	int move(int size, int current, int steps) {
		steps %= size;
		int tmp = current + steps;
		if (tmp >= 0 && tmp < size) {
			return tmp;
		}
		if (tmp < 0) {
			return size + tmp;
		}
		return tmp - size;
	}
public:
	bool circularArrayLoop(vector<int>& nums) {
		
		for (int i = 0; i < nums.size();++i) {
			vector<bool> dp(nums.size());

			int cur = i;
			int counter = 0;
			bool sign = nums[i] < 0;

			while (!dp[cur] && (nums[cur]<0) == sign) {
				dp[cur] = true;
				counter++;
				cur = move(nums.size(), cur, nums[cur]);
			}

			if (dp[cur] && counter > 1 && cur == i) {
				return true;
			}
		}

		return false;
	}
};