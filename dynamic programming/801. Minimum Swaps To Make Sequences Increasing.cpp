/*
801. Minimum Swaps To Make Sequences Increasing

We have two integer sequences A and B of the same non-zero length.

We are allowed to swap elements A[i] and B[i].  Note that both elements are in the same index position in their respective sequences.

At the end of some number of swaps, A and B are both strictly increasing.  (A sequence is strictly increasing if and only if A[0] < A[1] < A[2] < ... < A[A.length - 1].)

Given A and B, return the minimum number of swaps to make both sequences strictly increasing.  It is guaranteed that the given input always makes it possible.

Example:
Input: A = [1,3,5,4], B = [1,2,3,7]
Output: 1
Explanation: 
Swap A[3] and B[3].  Then the sequences are:
A = [1, 3, 5, 7] and B = [1, 2, 3, 4]
which are both strictly increasing.
Note:

A, B are arrays with the same length, and that length will be in the range [1, 1000].
A[i], B[i] are integer values in the range [0, 2000].


*/


/*
A[i]>A[i-1] && B[i] > B[i-1】 
- i 和 i-1， 都不变
- i 和 i-1， 都变

A[i]>B[i-1] && B[i] > A[i-1]
- i-1变， i不变
- i-1不变, i变


             1,   3,      3,  8,    7,  11
             1,   2,      4,  6,    9,  13
  non_swap:  0   (0,1)    1  (1,2)  2   (2,3)   
  swap:      1   (2,1)    1  (2,2)  2   (3,3)
*/


class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int swap = 1, no_swap = 0, temp_swap = 0, temp_non_swap = 0;
        for(int i = 1; i<A.size();i++){
            temp_swap = temp_non_swap = INT_MAX;
            if(A[i]>A[i-1] && B[i] > B[i-1]){
                temp_non_swap = no_swap; //保持现状, 上一个没变，现状不变
                temp_swap = swap+1; //上一个swap了，这个继续swap， 上一个变，现状变
            }
            if(A[i]>B[i-1] && B[i] > A[i-1]){
                temp_non_swap = min(temp_non_swap,swap); //保持上一个swap， 上一个变，现在不变
                temp_swap = min(temp_swap,no_swap+1); //上一个没swap，现在swap， 上一个不变，现状变
            }
            swap = temp_swap;
            no_swap = temp_non_swap;
            //cout<<" swap "<<swap<<" no swap "<<no_swap<<endl;
        }
        return min(swap, no_swap);
    }
};