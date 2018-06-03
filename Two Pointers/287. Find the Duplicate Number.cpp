/*
287. Find the Duplicate Number

Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive),
 prove that at least one duplicate number must exist. Assume that there is only one duplicate number, 
 find the duplicate one.

Example 1:

Input: [1,3,4,2,2]
Output: 2
Example 2:

Input: [3,1,3,4,2]
Output: 3
Note:

You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n2).
There is only one duplicate number in the array, but it could be repeated more than once.



*/


/*

index: 0 1 2 3 4 5
value: 2 5 1 1 4 3
value: 1 4 0 0 3 2

    5 -> 2 -> 0 <-3
              |   ^
              v   |    
              1   ^
              |  /
              v
              4 


肯定会有cycle，因为加入 i = 2, i = 3 同时指向0，因为如果把整个list当做一条链看，必须有头有尾，
假如把i=2 以前看做头, 那么从i=2 -> i=0, 必须会loop 到3 (0->3->0 形成loop)
假如把i=3 以前看做头, 那么从i=3 -> i=0, 必须会loop 到2 (0->2->0 形成loop)


*/


/*
Two pointer
O(n)
总共n+1个数
slow, fast 只能从n或者nums[n]开始，因为所有数都在1和n之间，因为是看index,每个数都要减1，
从i=n(实际上是第n+1个数)开始，i=n最大数是n, nums[i=n]-1是下一个index（最大是n-1！=n）,所以可以保证不会自己循环

*/
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size(); //这的n实际上是n+1
        int slow =n-1;
        int fast = n-1;
        do{
            //cout<<" slow "<<slow<<" fast "<<fast<<endl;
            slow = nums[slow]-1;
            fast = nums[nums[fast]-1]-1;
        }while(slow != fast);
        slow = n-1;
        while(slow != fast){
            //cout<<" aaaslow "<<slow<<" fast "<<fast<<endl;
            slow = nums[slow]-1;
            fast = nums[fast]-1;
        }
        return slow+1;
    }
};


class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size()-1;
        int slow = nums[n]-1;
        int fast = nums[nums[n]-1]-1;
        while(slow!=fast){
            slow = nums[slow]-1;
            fast = nums[nums[fast]-1]-1;
        }
        slow = n;
        while(slow!=fast){
            slow = nums[slow]-1;
            fast = nums[fast]-1;
        }
        return slow+1;
    }
};

/*
所有数不减去1,所有数都是在【1,n】 不减去1从i=0开始就不会回到0，

*/
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = nums[0];
        int fast = nums[nums[0]];
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }

        fast = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};



/*
Binary Search O(nlogn)

*/
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size()-1;
        int left = 0, right = n;
        while(left<right){
            int mid = (left + right)>>1;
            int count = 0;
            for(auto i: nums)
                if(i<=mid) count++;
            if(count>mid) right = mid;
            else left = mid+1;
        }
        return left;
    }
};