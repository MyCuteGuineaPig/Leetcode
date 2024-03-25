class Solution {
public:
    int kBigIndices(vector<int>& nums, int k) {
        priority_queue<int>pq;
        int n = nums.size();
        vector<int>prefix(n);
        int res = 0;
        for(int i = 0; i < nums.size(); ++i){
            if(pq.size() == k && pq.top() < nums[i]) 
                prefix[i] = 1;
            pq.push(nums[i]);
            if (pq.size() > k) pq.pop();
        }
        pq = priority_queue <int>();
        for(int i = n-1; i>=0; --i){
            if (pq.size() == k && pq.top() < nums[i] && prefix[i]) ++res;
            pq.push(nums[i]);
            if (pq.size() > k) pq.pop();
        }
        return res;
    }
};