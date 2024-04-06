class Solution {
public:
    long long maximumBooks(vector<int>& books) {
        /*
            比如 r = 2,  l = 0, 
            [0,3,1,5,4]
            左侧实际应该是1，如果l = 0, 拿的book 就是-1, 不可以
        */
        auto calculate = [&](int l, int r) -> long long{
            int min_cnt = min(books[r], r-l);
            return (long long)(books[r] + (books[r] - min_cnt))*(min_cnt+1)/2;
        };
        int n = books.size();
        vector<long long>dp(n);
        stack<int>stk;
        for(int i = 0; i<n; ++i){
            while(!stk.empty() && books[stk.top()] >= books[i] - (i - stk.top())){
                stk.pop();
            }
            if(stk.empty()){
                dp[i] = calculate(0, i);
            } else {
                dp[i] = dp[stk.top()] + calculate(stk.top()+1, i);
            }
            stk.push(i);
        }
        return *max_element(dp.begin(), dp.end());
    }
};