class Solution {
public:
    int validSubarrays(vector<int>& nums) {
        int n = nums.size(); 
        stack<int>stk;
        vector<int>right(n, n);
        for(int i = 0; i < n;++i){
            while(!stk.empty() && nums[stk.top()] > nums[i]){
                right[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }
        int res = 0;
        for(int i = 0; i < n; ++i){
            res += right[i] - i;
        }
        return res;
    }
};


class Solution {
public:
    int validSubarrays(vector<int>& nums) {
        int ans = 0;
        
        stack<int> st;
        for (int i = 0; i < nums.size(); i++) {
            // Keep popping elements from the stack
            // until the current element becomes greater than the top element.
            while (!st.empty() && nums[i] < nums[st.top()]) {
                // The diff between the current index and the stack top would be the subarray size.
                // Which is equal to the number of subarrays.
                ans += (i - st.top());
                st.pop();
            }
            st.push(i);
        }
        
        // For all remaining elements, the last element will be considered as the right endpoint.
        while (!st.empty()) {
            ans += (nums.size() - st.top());
            st.pop();
        }
        
        return ans;
    }
};



class Solution {
public:
    int validSubarrays(vector<int>& nums, int res = 0) {
    vector<int> s;
    for (auto n : nums) {
        while (!s.empty() && n < s.back()) s.pop_back();
        s.push_back(n);
        res += s.size();
    }
    return res;
    }
};