/*
665. Non-decreasing Array

Given an array with n integers, your task is to check if it could become non-decreasing by modifying at most 1 element.

We define an array is non-decreasing if array[i] <= array[i + 1] holds for every i (1 <= i < n).

Example 1:
Input: [4,2,3]
Output: True
Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
Example 2:
Input: [4,2,1]
Output: False
Explanation: You can't get a non-decreasing array by modify at most one element.
Note: The n belongs to [1, 10,000].
*/


/*
思路:  
当nums[i] < nums[i-1] 有两种modify的方法
1. 让 nums[i-1] = nums[i] 降: 当nums[i-2] <= nums[i] 就可以, 比如case1: 3<7,但是1<3 所以让7 = 3
2. 让 nums[i] = nums[i-1] 升:  case2 不能让 7=3, 因为nums[i-2] > nums[i], 只能提升nums[i]

顺序先1后2, 因为提升是有风险的, 下降是没有风险的，比如case1: 假如让3 = 7, 但是后面4<7

Case 1:
     7
     /\    4
    /  \  /
   /    \/
  /      3
 1
 
Case 2:
          9
         /
   7    /
   /\  /
  4  \/
      3


*/

class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int cnt = 0;                                                                    //the number of changes
        for(int i = 1; i < nums.size() && cnt<=1 ; i++){
            if(nums[i-1] > nums[i]){
                cnt++;
                if(i-2<0 || nums[i-2] <= nums[i])nums[i-1] = nums[i];                    //modify nums[i-1] of a priority
                else nums[i] = nums[i-1];                                                //have to modify nums[i]
            }
        }
        return cnt<=1;
    } 
};


class Solution {
    public boolean checkPossibility(int[] nums) {
        boolean modified = false;
        for (int i = 1; i < nums.length; i++) {
            if (nums[i] < nums[i - 1]) {
                if (modified) {
                    return false;
                } else {
                    modified = true;
                    if (i - 2 >= 0 && nums[i] < nums[i - 2]) {
                        nums[i] = nums[i - 1];
                    }
                }
            }
        }
        return true;
    }
}

/*
思路:
找break点: nums[i] > nums[i+1] 

如果break的点数大于1, return false
如果break点在边界, 我们改变边界就可以了, return true

如果break 是下面的case    9
                    7   /
                     \ /
                      4
            (4是break的点) 保证上一个和下一个点是一个non-decreasing的数列, 可以改break的值(4变为7), 满足non-decreasing的数列


如果break 是下面的case 
                        
                   9
                 /  \    7
                /    \ /
               /      4
              1 

            (4是break的点) 保证可以改break-2和可以改break是一个non-decreasing的数列, 可以改break-1的值(9变为4), 满足non-decreasing的数列
            不会 break + 1 < break 因为这样子break就是下一点了, cnt>1, return false
    


If we cannot, similarly we check with break_index-2 and break_index, and if they are non-decreasing, we can change nums[break_index-1] to make it non-decreasing.

If nothing is possible, we just check with cnt value and return accordingly.

*/

class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int cnt = 0;    
        int len = nums.size();
        int break_index = -1;
        
        for(int i=0;i<len-1 && cnt < 2;++i){           
            if(nums[i] > nums[i+1]){
                cnt += 1;
                break_index = i+1;
            }            
        }
        
        if(cnt > 1) return false;     
        if(break_index == len-1 || break_index == 1) return true;
        if(cnt == 1 && nums[break_index-1] <= nums[break_index+1]) return true;
        if(cnt == 1 && nums[break_index-2] <= nums[break_index]) return true;
        
        return cnt == 0;
    }
};


//C++ - Without Modifying Input

class Solution {
public:
    bool checkPossibility(vector<int>& a) {
        bool modified = false;
        for (int i = 1, prev = a[0]; i < a.size(); i++) {
            if (a[i] < prev && modified++) return false;
            if (a[i] < prev && i - 2 >= 0 && a[i - 2] > a[i]) continue;
            prev = a[i];
        }
        return true;
    }
};

/*      

       i     i+1    i+2
        9   
       /  \    8 
      7    \ /
            6  
    
        因为 nums[i] > nums[i+1]， 只能调整nums[i] 变成Nums[i] (让9变成6), 但是同时nums[i+1] < nums[i-1], 更改后的nums[i] = nums[i+1] < nums[i-1]矛盾


*/
class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int count = 0;
        for (int i = 0; i < nums.size() - 1; i++)
            if (!(nums[i] <= nums[i + 1])) {
                if (count > 0)
                    return false;
                if (i - 1 >= 0 && i + 2 < nums.size() && (nums[i] > nums[i + 2] && nums[i + 1] < nums[i - 1]))
                    return false;
                count++;
            }
        return true;
    }
};

class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        for (int i=1; i < nums.size(); i++){
            if (nums[i-1]<=nums[i]) continue;
            int temp=nums[i-1];
            nums[i-1]=nums[i];
            if (is_sorted(nums.begin(),nums.end())) return true;
            nums[i-1]=nums[i]=temp;
            return is_sorted(nums.begin(),nums.end());
        }
        return true;
    }
};