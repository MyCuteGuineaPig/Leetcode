/*
611. Valid Triangle Number

Given an array consists of non-negative integers, your task is to count the number of triplets chosen from the array
 that can make triangles if we take them as side lengths of a triangle.
Example 1:
Input: [2,2,3,4]
Output: 3
Explanation:
Valid combinations are: 
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3
Note:
The length of the given array won't exceed 1000.
The integers in the given array are in the range of [0, 1000].

*/


/*
先sort 然后看nums 2 5 6 7 9
如果当j<<k时， nums[i]+nums[j]<nums[k]成立时,但是 nums[i]+nums[j]<nums[k+1] 不能成立时，
所有j 满足【i+1，j]在k+1时都不满足
*/
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        if(nums.size()<3) return 0;
        sort(nums.begin(),nums.end());
        int count = 0;
        for(int i = 0; i<nums.size()-2;i++){
            //cout<<i<<endl;
            for(int j = i+1, k = i+2; j<nums.size()-1 && nums[i]!=0; j++){
                while(k<nums.size() && nums[i]+nums[j]>nums[k]) k++;
                count += k-j-1;
            }
        }
        return count;
    }
};


class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        if(nums.size()<3) return 0;
        sort(nums.begin(),nums.end());
        int count = 0, n = nums.size();
        for (int i=n-1;i>=2;i--) {
            int l = 0, r = i-1;
            while (l < r) {
                if (nums[l] + nums[r] > nums[i]) { //nums[l]+nums[r]>nums[i] 所有l在[l,r-1] 区间内的数都满足
                    count += r-l;
                    r--;
                }
                else l++;
            }
        }
        return count;
    }
};



//binary search
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        if(nums.size()<3) return 0;
        sort(nums.begin(),nums.end());
        int count = 0;
        for(int i = 0; i<nums.size()-2;i++){
            //cout<<i<<endl;
            if(nums[i] == 0) continue;
            for(int j = i+1, k = i+2; j<nums.size()-1; j++){
                auto it = lower_bound(nums.begin()+k, nums.end(),nums[i]+nums[j]);//找大于等于nums[i]+nums[j] 的第一个点，这个点之后是于nums[i],nums[j]构不成三角形的
                auto index = it-nums.begin();
                count += index-j-1;
            }
        }
        return count;
    }
};