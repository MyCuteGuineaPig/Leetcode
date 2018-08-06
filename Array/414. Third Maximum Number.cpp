/*
414. Third Maximum Number


Given a non-empty array of integers, return the third maximum number in this array. 
If it does not exist, return the maximum number. The time complexity must be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
Example 3:
Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.


*/

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long one = numeric_limits<long>::min(), two = one = numeric_limits<long>::min(), three = one = numeric_limits<long>::min();
        for(auto i : nums){
            if(i == one || i == two || i == three) continue;
            if(i>one) {
                three = two;
                two = one; 
                one = i;
            }else if(i>two){
                three = two;
                two = i;
            }else if(i>three){
                three = i;
            }
        }
        return three == numeric_limits<long>::min() ? one : three;
    }
};


class Solution {
public:
    int thirdMax(vector<int>& nums)
    {
        long max=LONG_MIN,second=LONG_MIN,third=LONG_MIN;
        
        for(int i=0;i<nums.size();i++){
            if(nums[i]>max){
                third=second;
                second=max;
                max=nums[i];
            }
            else if(nums[i]<max&&nums[i]>second){
                third=second;
                second=nums[i];
            }
            else if(nums[i]<second&&nums[i]>third)
                third=nums[i];
        }
         if(third==LONG_MIN)
            return max;
        return third;
    }
};


class Solution {
public:
    int thirdMax(vector<int>& nums) {
        set<int> top3;
        for (int num : nums) {
            top3.insert(num);
            if (top3.size() > 3)
                top3.erase(top3.begin());
        }
        return top3.size() == 3 ? *top3.begin() : *top3.rbegin();
    }
};

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        long long a, b, c;
        a = b = c = LLONG_MIN;
        for (auto num : nums) {
            if (num <= c || num == b || num == a) continue;
            c = num;
            if (c > b) swap(b, c);
            if (b > a) swap(a, b);
        }
        return c == LLONG_MIN ? a : c;
    }
};