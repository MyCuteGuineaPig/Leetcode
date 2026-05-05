class Solution {
public:
    vector<int> minCost(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int>left_cost(n);
        vector<int>right_cost(n);

        for(int i = 0; i < n-1; ++i) {
            if(i == 0 || nums[i+1] - nums[i] < nums[i] - nums[i-1])
                left_cost[i+1] = left_cost[i] + 1; 
            else 
                left_cost[i+1] = left_cost[i] + nums[i+1] - nums[i];
        }

        for(int i = n - 1; i >=1 ; --i) {
            if(i == n-1 || nums[i+1] - nums[i] >= nums[i] - nums[i-1]) 
            // if equal, choose the smaller index.
                right_cost[i-1] = right_cost[i] + 1; 
            else 
                right_cost[i-1] = right_cost[i] + nums[i] - nums[i-1];
        }

        vector<int> res;
        for(auto query: queries) {
            if(query[0] < query[1]) 
                res.push_back(left_cost[query[1]] - left_cost[query[0]]);
            else 
                res.push_back(right_cost[query[1]] - right_cost[query[0]]);
        }
        return res;
    }
};