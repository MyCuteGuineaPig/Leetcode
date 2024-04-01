/*

Now the number of swaps is really the distance between the indexes we found above to either ends based on the requirements. 
We should be aware that, if mini > maxi (the smallest number is on the right side of the largest number), 
we need to do one less swap operation 
because swapping one of the largest/smallest number to its destination would swap the other.

For example, [2,1] only needs one swap operation, not two.

*/


class Solution {
public:
    int minimumSwaps(vector<int>& nums) {
        int n = nums.size();
        int maxi = n-1, mini = 0;
        for(int i = 0; i < nums.size(); ++i){
            if (nums[i] >= nums[maxi]){
                maxi = i;
            } 
            if (nums[i] < nums[mini]){
                mini = i;
            }
        }
        return n - 1 - maxi + mini - (mini > maxi ? 1 : 0);
    }
};