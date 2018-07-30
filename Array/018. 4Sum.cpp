/*
18. 4Sum

Given an array nums of n integers and an integer target, are there elements a, b, c, 
and d in nums such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

Note:

The solution set must not contain duplicate quadruplets.

Example:

Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]


*/

//先比后跳
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if(nums.size()<4) return {};
        vector<vector<int>>res;
        sort(nums.begin(), nums.end());
        for(int i = 0; i<nums.size()-3; i++){
            if(nums[i]+nums[i+1]+nums[i+2]+nums[i+3]>target) break;
            for(int j = i+1; j<nums.size()-2; j++){
                for(int k = j+1, m = nums.size()-1; k<m; ){
                    int temp = nums[i] + nums[j] + nums[k] + nums[m];
                    if(temp == target){
                        res.push_back({nums[i],nums[j],nums[k],nums[m]});
                        while(k<m && nums[k+1] == nums[k]) k++;
                        while(k<m && nums[m-1] == nums[m]) m--;
                        k++; m--;
                    }else if(temp < target){
                        while(k<m && nums[k+1] == nums[k]) k++;
                        k++;
                    }else{
                        while(k<m && nums[m-1] == nums[m]) m--;
                        m--;
                    }
                }
                while(j<nums.size()-3 && nums[j] == nums[j+1]) j++;
            }
            while(i<nums.size()-4 && nums[i+1] == nums[i]) i++;
        }
        return res;
    }
};


//先跳后比（指的是逻辑顺序，而不是实际顺序）
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if(nums.size()<4) return {};
        vector<vector<int>>res;
        sort(nums.begin(), nums.end());
        for(int i = 0; i<nums.size()-3; i++){
            if(nums[i]+nums[i+1]+nums[i+2]+nums[i+3]>target) break;
            if(i>0 && nums[i] == nums[i-1]) continue;
            for(int j = i+1; j<nums.size()-2; j++){
                if(j>i+1 && nums[j] == nums[j-1]) continue;
                for(int k = j+1, m = nums.size()-1; k<m; ){
                    int temp = nums[i] + nums[j] + nums[k] + nums[m];
                    if(k > j+1 && nums[k] == nums[k-1])  k++;
                    else if(m < nums.size()-1 && nums[m] == nums[m+1]) m--;
                    else if(temp == target){
                        res.push_back({nums[i],nums[j],nums[k],nums[m]});
                        k++; m--;
                    }else if(temp < target){
                        k++;
                    }else{
                        m--;
                    }
                }
            }
        }
        return res;
    }
};


// Time:  O(n^4)
// Space: O(n^2)
class Solution2 {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
        vector<vector<int>> ans;
        if (num.size() < 4)  {
            return ans;
        }
        sort(num.begin(), num.end());
        unordered_multimap<int, pair<int, int>> cache;

        for (int i = 0; i < num.size(); ++i) {
            for (int j = i + 1; j < num.size(); ++j) {
                cache.emplace(num[i] + num[j], make_pair(i, j));
            }
        }

        for (auto i = cache.begin(); i != cache.end(); ++i) {
            auto a = i->second.first;
            auto b = i->second.second;
            auto range = cache.equal_range(target - i->first);
            for (auto j = range.first; j != range.second; ++j) {
                auto c = j->second.first;
                auto d = j->second.second;
                if (b < c) {
                    ans.push_back({num[a], num[b], num[c], num[d]});
                }
            }
        }
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        return ans;
    }
};