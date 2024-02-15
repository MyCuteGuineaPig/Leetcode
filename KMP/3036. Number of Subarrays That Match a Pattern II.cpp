class Solution {
public:
    vector<int>kmp(vector<int>&pattern){
        int j = 0;
        vector<int>res(pattern.size()); 
        for(int i = 1; i<pattern.size(); ++i){
            while (j && pattern[i]!=pattern[j]){
                j = res[j-1];
            }
            res[i] = (j += pattern[i] == pattern[j]);
        }
        return res;
    }

    bool satisfy(vector<int>& nums, vector<int>& pattern, int i, int j){
        return  pattern[j] == 0 && nums[i] == nums[i+1] || 
                pattern[j] == 1 && nums[i] < nums[i+1] ||
                pattern[j] == -1 && nums[i] > nums[i+1];
    }

    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        int k = pattern.size()+1;
        int res = 0;
        vector<int>prefix = kmp(pattern);
        for(int i = 0, j = 0; i<nums.size()-1;++i){
            while(j > 0 && !satisfy(nums, pattern, i, j)){
                j = prefix[j-1];
            } 
            j += satisfy(nums, pattern, i, j);
            if ( j == pattern.size()){
                res+=1;

                j = prefix[j-1];
            }
        }
        return res;
    }
};