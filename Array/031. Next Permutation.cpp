/*
31. Next Permutation


Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be in-place and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1



*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if(nums.size()<2) return;
        int i = nums.size()-2;
        while(i>=0 && nums[i] >= nums[i+1]) i--;
        if(i==-1){
            reverse(nums.begin(), nums.end());
        }
        else{
            int j = nums.size()-1;
            while(nums[i] >= nums[j]) j--;
            swap(nums[i], nums[j]);
            cout<<i<<", "<<j<<endl;
            reverse(nums.begin()+i+1, nums.end());
        }
    }
};



class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        auto i = is_sorted_until(nums.rbegin(), nums.rend());
        if(i!=nums.rend())
            swap(*i, *upper_bound(nums.rbegin(), i, *i));
        reverse(nums.rbegin(), i);
    }
};

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i = nums.size() - 1, k = i;
        while (i > 0 && nums[i-1] >= nums[i])
            i--;
        for (int j=i; j<k; j++, k--)
            swap(nums[j], nums[k]);
        if (i > 0) {
            k = i--;
            while (nums[k] <= nums[i])
                k++;
            swap(nums[i], nums[k]);
        }
    }
};

class Solution {
public:
    void nextPermutation(vector<int> &num) 
    {
        if (num.empty()) return;
        
        // in reverse order, find the first number which is in increasing trend (we call it violated number here)
        int i;
        for (i = num.size()-2; i >= 0; --i)
        {
            if (num[i] < num[i+1]) break;
        }
        
        // reverse all the numbers after violated number
        reverse(begin(num)+i+1, end(num));
        // if violated number not found, because we have reversed the whole array, then we are done!
        if (i == -1) return;
        // else binary search find the first number larger than the violated number
        auto itr = upper_bound(begin(num)+i+1, end(num), num[i]);
        // swap them, done!
        swap(num[i], *itr);
    }
};


class Solution {
public:
    void nextPermutation(vector<int>& nums) {
    	int n = nums.size(), k, l;
    	for (k = n - 2; k >= 0; k--) {
            if (nums[k] < nums[k + 1]) {
                break;
            }
        }
    	if (k < 0) {
    	    reverse(nums.begin(), nums.end());
    	} else {
    	    for (l = n - 1; l > k; l--) {
                if (nums[l] > nums[k]) {
                    break;
                }
            } 
    	    swap(nums[k], nums[l]);
    	    reverse(nums.begin() + k + 1, nums.end());
        }
    }
}; 