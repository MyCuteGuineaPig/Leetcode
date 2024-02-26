/*
注: 1 <= changeIndices[i] <= n
所以
nums = [2,2,0] 
changeIndices = [4,5,6,6,5,4,3,6] 
不是valid test case 

需要last_index, 而不是first_index 因为
每次decrement value只能是1，所以尽可能的延后mark

*/

class Solution {
public:
    bool possible(vector<int>& nums, vector<int>& changeIndices, int bound){
        unordered_map<int, int>last_index;
        for(int i = 0; i < changeIndices.size() && i < bound; ++i){
            last_index[changeIndices[i]] = i;
        }
        cout<<" last_index.size() "<<last_index.size()<<endl;
        if (last_index.size() != nums.size()) return false; 
        int cnt = 0; 
        for(int i = 0; i < bound; ++i){
            if(i == last_index[changeIndices[i]]){
                int val = nums[changeIndices[i]-1];
                if (cnt < val) {
                    return false;
                }
                cnt -= val;
            }
            else 
                ++cnt;
        }
        return true;
    }

    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        int l = 0, r = changeIndices.size() + 1; 
        while ( l < r){
            int mid = (l + r)/2; 
            if (possible(nums, changeIndices, mid)){
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l > changeIndices.size()? -1 : l;
    }
};