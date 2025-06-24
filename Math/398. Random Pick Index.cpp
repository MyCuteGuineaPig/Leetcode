class Solution {
private: 
    unordered_map<int, vector<int>>mp;
public:
    Solution(vector<int>& nums) {
        for(int i = 0; i < nums.size(); ++i)
            mp[nums[i]].push_back(i);
    }
    
    int pick(int target) {
        int l = mp[target].size();
        return mp[target][rand() % l];
    }
}; 

/*

从一个数组中随机选取一个元素，要求每个元素被选中的概率相同。
即是1/n, 每一步我们选择whether or not choose agvien number. the overall probability
that we choose a number is 1/n, 

如果有n个数，抽取第i个数, do not pick nuber from i+1 to n, probabilty can be represented as 

1/i * (i/(i+1)) * ((i+1)/ (i+2)) ... * (n-1)/n

 */

// Reservoir sampling
class Solution {
public:
    
    vector<int> nums;
    
    Solution(vector<int>& nums) {
        this->nums.swap(nums);
    }
    
    int pick(int target) {
        int n = nums.size();
        int count = 0;
        int idx = 0;
        for (int i = 0; i < n; ++i) {
            // if nums[i] is equal to target, i is a potential candidate
            // which needs to be chosen uniformly at random
            if (nums[i] == target) {
                // increment the count of total candidates
                // available to be chosen uniformly at random
                count++;
                // we pick the current number with probability 1 / count (reservoir sampling)
                if (rand() % count == 0) {
                    idx = i;
                }
            }
        }
        return idx;
    }
};