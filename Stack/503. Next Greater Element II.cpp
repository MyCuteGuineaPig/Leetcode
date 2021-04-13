class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int>res(n, -1);
        stack<int>stk;
        for(int i = 0; i<2*n; ++i){
            while(!stk.empty() && nums[stk.top()%n] < nums[i%n]){
                res[stk.top()%n] = nums[i%n];
                stk.pop();
            }
            stk.push(i);
        }
        return res;
    }
};

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int>res(n, -1);
        stack<int>stk;
        for(int i = 2*n-1; i>=0; --i){
            while(!stk.empty() && nums[stk.top()%n] <= nums[i%n]){
                stk.pop();
            }
            if(!stk.empty())
                res[i%n] = nums[stk.top()%n];
            stk.push(i);
        }
        return res;
    }
};

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> next(n, -1);
        stack<int> s; // index stack
        for (int i = 0; i < n * 2; i++) {
            int num = nums[i % n]; 
            while (!s.empty() && nums[s.top()] < num) {
                next[s.top()] = num;
                s.pop();
            }
            if (i < n) s.push(i);
        }   
        return next;
    }
};