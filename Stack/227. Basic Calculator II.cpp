/*
227. Basic Calculator II

Implement a basic calculator to evaluate a simple expression string.

The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.

Example 1:

Input: "3+2*2"
Output: 7
Example 2:

Input: " 3/2 "
Output: 1
Example 3:

Input: " 3+5 / 2 "
Output: 5
Note:

You may assume that the given expression is always valid.
Do not use the eval built-in library function.

*/

class Solution {
public:
    int calculate(string s) {
        stack<int>stk;
        int sign = 1;
        for(int i = 0; i<s.size();i++){
            if(s[i] >= '0' && s[i]<='9'){
                int x = 0; 
                while(i<s.size() && s[i]>='0'){
                    x = x*10 + s[i]-'0';
                    i++;
                }
                if(sign == 2 || sign == 3){
                    int a = stk.top(); stk.pop();
                    stk.push(sign == 2 ? a*x : a/x);
                }
                else stk.push(sign*x);
                i--;
            }
            else if(s[i] == '*' || s[i] == '/') sign = s[i] == '*' ? 2 : 3;
            else if(s[i] == '+' || s[i] == '-') sign = s[i] == '+' ? 1 : -1;
        }
        int res = 0;
        while(!stk.empty()){
            res += stk.top(); 
            stk.pop();
        }
        return res;
    }
};





classclass  SolutionSolution { {
 publicpublic:
    :     intint  calculatecalculate((stringstring s) s)  {
        {         stackstack<<intint> nums;
        > nums;         intint num= num=00;
        ;         charchar op =  op = '+''+';
        ;         forfor((intint i= i=00; i<s.size(); i++){
            ; i<s.size(); i++){     if (s[i]>='0' && s[i]<='9') {
                num = num*10+(s[i]-'0');
            }
            if ( (s[i] <'0' || s[i]>'9')&&(s[i]!=' ') || i==s.size()-1) {
                if (op=='+') {
                    nums.push(num);
                }
                else if(op=='-') {
                    nums.push(-num);
                }
                else if (op=='*') {
                    int tmp = nums.top() * num;
                    nums.pop();
                    nums.push(tmp);
                }
                else if (op=='/') {
                    int tmp = nums.top()/num;
                    nums.pop();
                    nums.push(tmp);
                }
                op = s[i];
                num=0;
            }
        }
        int result = 0;
        while(!nums.empty()) {
            result += nums.top();
            nums.pop();
        }
        return result;
    }
};
