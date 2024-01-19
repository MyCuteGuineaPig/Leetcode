/*
32. Longest Valid Parentheses

Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"
Example 2:

Input: ")()())" 
Output: 4
Explanation: The longest valid parentheses substring is "()()"

Input: "()(())"
Output: 6

Input: "())())"
Output: 6




*/

/*
DP解： 
1.  s[i] = '(', s[i-1] = '(', 这两个必能组成(), so dp[i] = dp[i-2] + 2
2.  s[i] = ')', s[i-1] = ')'  => if s[i-dp[i-1]-1] then
    dp[i] = dp[i-1] + dp[i - dp[i - 1] - 2] + 2
    
    定义'起始点' 为与现在')' 组成valid substring的'('的点
    s[i] 可能是large valid string的一部分，如果是一部分，必须有相对应的起始的'(', 起始点的'(' 和现在的')' 相距dp[i-1]个距离
    比如： (()), 最后一个'(' 和最初的'(' 相距两个距离,
    如果起始点是'(', 起始点加上现在的点可以组成新的substring(+2),起始点前面可能还有的valid，还需要加上起始点前一点

*/


class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size(), maxres = 0;
        vector<int>dp(n+1); //dp[i+1]表示以S[i]结束时最大的valid的长度
        for(int i = 1; i< n; i++){
            if(s[i]==')' && s[i-1] == '('){ 
                dp[i+1] = dp[i-1]+2;
            }
            else if(s[i]==')' && s[i-1] == ')'){  
                int start = i - dp[i] - 1;
                if(s[start] == '(')
                    dp[i+1] = dp[start]+dp[i]+2;
                /*
                s[i] = ')', s[i-1] == ')' start代表与s[i]对应的起点
                比如 "( ) ( ( ) )"  当i在最后一位,dp[i]表示以倒数第二位结束的最大长度为2,所以5-2-1 = 2 " () ("到与i对应的起点
                如果起点是'(' 表示当前是valid的 (dp[i]+2) 因为现在valid 还要加上起点前valid的长度
                
                */
            }
            maxres = max(maxres, dp[i+1]);
        }
        return maxres;
    }
};

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        vector<int>dp(n+1);
        for(int i = 1; i<n; ++i){
            if(s[i] == ')' && s[i-1] == '('){
                dp[i+1] = 2 + dp[i-1];
            } else if (s[i] == ')' && s[i-1] == ')'){
                int start =  i - dp[i] - 1;
                if(start >= 0 && s[start] == '('){
                    dp[i+1] = 2 + dp[i]+(start >= 0 ? dp[start]: 0);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};


/*

Stack 的解: stk用来push index,  stk最里面的（最后pop的）是现在substring最开始的位置，其他位置是上个'('

遇到'(', stk push 进去

遇到')', stk 先pop 一个，接下来top的就是上一个'('的起始位置,（是起始位置的上一位, 现在）
-  如果pop 时候, stk为空，代表从起始位置开始，跟'('比, 有更多的')', 无法组成valid substring了
   所以一旦为空，无法组成新的substring，需要重新push新的起点（current index）

    


对于每个"(", push
*/

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size(), maxres = 0;
        stack<int>stk;
        stk.push(-1);
        for(int i = 0; i<n; i++){
            if(s[i]=='(') stk.push(i);
            else{
                stk.pop();
                if(stk.empty()){
                    stk.push(i);
                }else{
                    maxres = max(maxres, i-stk.top());
                }
            }
        }
        return maxres;
    }
};