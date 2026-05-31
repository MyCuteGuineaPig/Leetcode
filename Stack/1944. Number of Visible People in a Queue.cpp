class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        stack<int> stk;
        vector<int>res; 
        int n  = heights.size();
        for(int i = n - 1; i >= 0; --i) {
            int count = 0;
            while(!stk.empty() && heights[stk.top()] <= heights[i]) {
                count++;
                stk.pop();
            }  
            if(!stk.empty()) count++;
            res.push_back(count);
            stk.push(i);
        }
        reverse(res.begin(), res.end());
        return res;

    }
};


class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& heights) {
        int n = heights.size();
        vector<int> res(n), stack;
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && heights[stack.back()] <= heights[i])
                res[stack.back()]++, stack.pop_back();
            if (!stack.empty())
                res[stack.back()]++;
            stack.push_back(i);
        }
        return res;
    }
};