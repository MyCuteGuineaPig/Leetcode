class StockSpanner {
public:
    StockSpanner() {}
    
    vector<vector<int>>lt;
    
    int next(int price) {
        int cnt = 1;
        if(!lt.empty()){
            int index = lt.size()-1;
            while(index >=0 && price >= lt[index][0]){
                index = index - lt[index][1];
            }
            cnt = lt.size() - index;
        }
        lt.push_back({price,cnt});
        return cnt;
    }
};


/**
More Good Stack Problems
Here are some problems that impressed me.
Good luck and have fun.

1130. Minimum Cost Tree From Leaf Values
907. Sum of Subarray Minimums
901. Online Stock Span
856. Score of Parentheses
739. Daily Temperatures
503. Next Greater Element II
496. Next Greater Element I
84. Largest Rectangle in Histogram
42. Trapping Rain Water

 */

class StockSpanner {
public:
    stack<pair<int, int>> s;
    
    int next(int price) {
        int res = 1;
        while (!s.empty() && s.top().first <= price) {
            res += s.top().second;
            s.pop();
        }
        s.push({price, res});
        return res;
    }
};