"""
307. Range Sum Query - Mutable

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.
Example:
Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
Note:
The array is only modifiable by the update function.
You may assume the number of calls to update and sumRange function is distributed evenly.

"""
class NumArray {
public:
    vector<int>sums;
    vector<int>nums;
    int size;
    NumArray(vector<int> nums_) {
        nums = nums_;
        size = nums.size();
        sums.resize(size+1,0);
        for(int i = 0; i<nums.size();i++){
            updateTree(i,nums[i]);
        }
    }
    
    void update(int i, int val) {
        updateTree(i,val-nums[i]);
        nums[i] = val;
    }

    int sumRange(int i, int j) {
       return getSum(j)-getSum(i-1);
    }
private:
    void updateTree(int i, int delta){
        i++;
        while (i<=size){
            sums[i] += delta;
            i += lowerbit(i);
        }
    }
    int lowerbit(int x) {return x & (-x);}

    int getSum(int i){
        int res = 0;
        i++;
        while( i>0){
            res += sums[i];
            i -= lowerbit(i);
        }
        return res;
    }
    
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */