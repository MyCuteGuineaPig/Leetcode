/*
739. Daily Temperatures

Given a list of daily temperatures, produce a list that, for each day in the input, 
tells you how many days you would have to wait until a warmer temperature. 
If there is no future day for which this is possible, put 0 instead.

For example, given the list temperatures = [73, 74, 75, 71, 69, 72, 76, 73], 
your output should be [1, 1, 4, 2, 1, 1, 0, 0].

Note: The length of temperatures will be in the range [1, 30000]. 
Each temperature will be an integer in the range [30, 100].


*/


/*
Ascending stack, 从后往前loop，遇到t[i] > stack.top(), stack.pop(), 如果stack不为空,则概数为第一个比t[i]大的


[89,62,70,58,47,47,46,76,100,70]

70:  stack {},
100: stack{70}, 
76, stack {100},  res = 1
46, stack {76, 100}, res = 1
47, stack {46, 76, 100}, res = 2
47, stack {47, 76, 100}, res = 3
58, stack {47, 76, 100}, res =  4
70, stack {58,76,100}, res = 5
62, stack {70,76,100}, res = 1
89, stack {62,70,76,100}, res = 8
end: stack {89,100}
*/
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<pair<int,int>>stk;//first is value, second is index
        int n = temperatures.size();
        vector<int>res(n);
        for(int i = n-1; i>=0; i--){
            while(!stk.empty() && temperatures[i] >= stk.top().first)
                stk.pop();
            if(!stk.empty()) res[i] = stk.top().second - i;
            stk.push({temperatures[i],i});
        }
        return res;
    }
};



class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result(temperatures.size());
        stack<int> stk;
        for (int i = 0; i < temperatures.size(); ++i) {
            while (!stk.empty() &&
                   temperatures[stk.top()] < temperatures[i]) {
                const auto idx = stk.top(); stk.pop();
                result[idx] = i - idx;
            }
            stk.emplace(i);
        }
        return result; 
    }
};