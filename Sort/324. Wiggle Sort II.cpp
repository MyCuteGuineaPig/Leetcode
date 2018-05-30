/*
324. Wiggle Sort II

Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example 1:

Input: nums = [1, 5, 1, 1, 6, 4]
Output: One possible answer is [1, 4, 1, 5, 1, 6].
Example 2:

Input: nums = [1, 3, 2, 2, 3, 1]
Output: One possible answer is [2, 3, 1, 3, 1, 2].
Note:
You may assume all input has valid answer.

Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?

*/


/*


Mapped_idx[Left] denotes the position where the next smaller-than median element  will be inserted.
Mapped_idx[Right] denotes the position where the next larger-than median element  will be inserted.


Step 1: 
Original idx: 0    1    2    3    4    5  
Mapped idx:   1    3    5    0    2    4 
Array:        13   6    5    5    4    2 
             Left
              i
                                      Right
 nums[Mapped_idx[i]] = nums[1] = 6 > 5, so it is ok to put 6 in the first odd index 1. We increment i and left.


Step 2: 
Original idx: 0    1    2    3    4    5  
Mapped idx:   1    3    5    0    2    4 
Array:        13   6    5    5    4    2 
                  Left
                   i
                                      Right
 nums[3] = 5 = 5, so it is ok to put 6 in the index 3. We increment i.


Step 3: 
Original idx: 0    1    2    3    4    5  
Mapped idx:   1    3    5    0    2    4 
Array:        13   6    5    5    4    2 
                  Left
                        i
                                     Right
 nums[5] = 2 < 5, so we want to put it to the last even index 4 (pointed by Right). So, we swap nums[Mapped_idx[i]] with nums[Mapped_idx[Right]], i.e. nums[5] with nums[4], and decrement Right. 




Step 4: 
Original idx: 0    1    2    3    4    5  
Mapped idx:   1    3    5    0    2    4 
Array:        13   6    5    5    2    4 
                  Left
                        i
                               Right
 nums[5] = 4 < 5, so we want to put it to the second last even index 2. So, we swap nums[5] with nums[2], and decrement Right. 




Step 5: 
Original idx: 0    1    2    3    4    5  
Mapped idx:   1    3    5    0    2    4 
Array:        13   6    4    5    2    5 
                  Left
                        i
                            Right
 nums[5] = 5 < 5, it is ok to put it there, we increment i.


Step 6: 
Original idx: 0    1    2    3    4    5  
Mapped idx:   1    3    5    0    2    4 
Array:        13   6    4    5    2    5 
                  Left
                             i
                            Right
 nums[0] = 13 > 5, so, we want to put it to the next odd index which is 3 (pointed by 'Left'). So, we swap nums[0] with nums[3], and increment 'Left' and 'i'.


Step Final: 
Original idx: 0    1    2    3    4    5  
Mapped idx:   1    3    5    0    2    4 
Array:        5    6    4    13   2    5 
                      Left
                                  i
                            Right
i > Right, we get the final wiggle array 5 6 4 13 2 5 !




to get wiggle sort, you want to put the number in the following way such that

(1) elements smaller than the 'median' are put into the last even slots

(2) elements larger than the 'median' are put into the first odd slots

(3) the medians are put into the remaining slots.

This is to explain why mapped index formula is (1 + 2*index) % (n | 1)

Notice that by placing the median in it's place in the array we divided the array in 3 chunks:
 all numbers less than median are in one side, all numbers larger than median are on the other side, median is in the dead center of the array.

We want to place any a group of numbers (larger than median) in odd slots, and another group of numbers (smaller than median) in even slots. 
So all numbers on left of the median < n / 2 should be in odd slots, 
all numbers on right of the median > n / 2 should go into even slots (remember that median is its correct place at n / 2)

PS: I'm ignoring the discussion of odd/even array length for simplicity.

So let's think about the first group in the odd slots, all numbers is the left side of the array should go into these odd slots. 
What's the formula for it? Naturally it would be:
(1 + 2 x index) % n

All these indexes are less than n / 2 so multiplying by 2 and add 1 (to make them go to odd place) and then mod by n will always guarantee that they are less than n.

Original Index => Mapped Index
0 => (1 + 2 x 0) % 6 = 1 % 6 = 1
1 => (1 + 2 x 1) % 6 = 3 % 6 = 3
2 => (1 + 2 x 2) % 6 = 5 % 6 = 5

These are what's less than median, if we continue this with indexes 3, 4, 5 we will cycle again:
3 => (1 + 2 x 3) % 6 = 7 % 6 = 1
4 => (1 + 2 x 4) % 6 = 9 % 6 = 3
5 => (1 + 2 x 5) % 6 = 11 % 6 = 5

and we don't want that, so for indexes larger than n/2 we want them to be even, (n|1) does that exactly. What n|1 does it that it gets the next odd number to n if it was even
if n = 6 for example 110 | 1 = 111 = 7
if n = 7 for example 111 | 1 = 111 = 7

and this is what we want, instead of cycling the odd numbers again we want them to be even, and odd % odd number is even so updating the formula to :
(1 + 2*index) % (n | 1)

Then we have:
3 => (1 + 2 x 3) % 7 = 7 % 7 = 0
4 => (1 + 2 x 4) % 7 = 9 % 7 = 2
5 => (1 + 2 x 5) % 7 = 11 % 7 = 4

*/




class Solution {
public:
    int n;
    void wiggleSort(vector<int>& nums) {
        n = nums.size();

        // Find a median.
        auto midptr = nums.begin() + n / 2;
        nth_element(nums.begin(), midptr, nums.end());
        int mid = *midptr;

        // Index-rewiring.
        for(auto i: nums)
            cout<<i<<", ";
        cout<<endl;

        // 3-way-partition-to-wiggly in O(n) time with O(1) space.
        int i = 0, j = 0, k = n - 1;
        while (j <= k) {
            cout<<" i "<<i<<" A[i] "<<A(i)<<" n[A[i]] "<<nums[A(i)]
                <<"----- j "<<j <<" A[j] "<<A(j)<<" n[A[j ]] "<<nums[A(j)]
                <<"----- k "<<j <<" A[k] "<<A(k)<<" n[A[k ]] "<<nums[A(k)]<<endl;
            if (nums[A(j)] > mid){
                cout<< "A(i++), A(j++)"<<endl;
                swap(nums[A(i++)], nums[A(j++)]);
            }
            else if (nums[A(j)] < mid){
                cout<< "swap(nums[A(j)], nums[A(k--)])"<<endl;
                swap(nums[A(j)], nums[A(k--)]);
            }
            else
                j++;
        }
    }
    
    int A(int i) {
        return (1+2*(i)) % (n|1);
    }
};