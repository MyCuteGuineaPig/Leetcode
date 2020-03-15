/*
75. Sort Colors

Given an array with n objects colored red, white or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note: You are not suppose to use the library's sort function for this problem.

Example:

Input: [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
Follow up:

A rather straight forward solution is a two-pass algorithm using counting sort.
First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.
Could you come up with a one-pass algorithm using only constant space?

*/

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int c0 = 0, c1 = 0;
        for(int i = 0; i<nums.size();i++){
            if(nums[i]==0) {
                swap(nums[i],nums[c0]);
                if(c0!=c1) swap(nums[i],nums[c1]);
                //如果现在有1的话，c0!=c1, swap(nums[i],nums[c0]);nums[c0]是1，1换到后面去了，所以要把1再换回来，
                c0++; c1++;
            }
            else if(nums[i]==1){
                swap(nums[i],nums[c1]);
                c1++;
            }
            //cout<<"  i "<<i<<" c0 "<<c0<<" c1 "<<c1<<"  ";
            //print(nums); 
        }
    }
    
    void print(vector<int>& nums){
        for(auto i: nums)
            cout<<i<<"  ";
        cout<<endl;
    }
};


//2020
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int i1 = 0, i2 = 0;
        for(int i = 0; i<nums.size(); ++i){
            if (nums[i] == 0){
                if(i1 == i2){
                    swap(nums[i], nums[i2++]);
                    i1++;
                }
                else{
                    swap(nums[i], nums[i1++]);
                    swap(nums[i], nums[i2++]);
                }
            }else if(nums[i] == 1){
                swap(nums[i], nums[i2++]);
            }
        }
    }
};


/*
count 
*/

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n0 = -1, n1 = -1, n2=-1;
        for(auto i: nums){
            if(i==0) nums[++n2] = 2, nums[++n1] = 1, nums[++n0] = 0;
            else if(i==1) nums[++n2] = 2, nums[++n1] = 1;
            else nums[++n2] = 2;
        }
    }
};


/*
inplace swap
*/
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int c0 = 0, c2 = nums.size()-1;//c0 是下一个插入0的位置，nums[c0]可能是0 或1，
        //c2 是下一个插入2的位置，nums[c2]可能是0 或1，
        for(int i = 0; i<=c2; i++){  
            /**
             * 
             * i==c2的原因是比如nums = [2,0,1] 
             * 1. i = 0, c0 = 0, c2 = 2;  swap(nums[0],nums[2]), c2--, i--; 变成[1,0,2]
             * 2. i = 0, c0 = 0, c2 = 1,  nums[i] = 1继续
             * 如果i<c2 就没有接下来的步骤了，原因是c2是下一个2插入的位置，有可能nums[c2]!=2
             * 3. i = 1, c0 = 0, c2 = 1,  swap(nums[0],nums[1]), c0++.  变成[0,1,2]
             * 4. i = 2, c0 = 1, c2 = 1,
            */
            if(nums[i]==0)
                swap(nums[c0++],nums[i]);
            else if(nums[i]==2)
                swap(nums[c2--],nums[i--]);
        }
    }
};


// Tri-Partition solution.
class Solution {
public:
    void sortColors(vector<int>& nums) {
        const int target = 1;
        for (int i = 0, j = 0, n = nums.size() - 1; j <= n;) {
            if (nums[j] < target) {
                swap(nums[i++], nums[j++]);
            } else if (nums[j] > target) {
                swap(nums[j], nums[n--]);
            } else {
                ++j;
            }
        }
    }
};
