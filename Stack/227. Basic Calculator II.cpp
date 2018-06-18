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


/*

整体方法是把数push进stack，有乘除，先pop，进行operation，再push进
最后结果是stack每个数的和
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



class Solution {
public:
    int calculate(string s) {
        stack<int>stk;
        char operators='+';
        int x = 0;
        for(int i = 0; i<s.size();i++){
            if(s[i] >= '0' && s[i]<='9'){
                x = 0; 
                while(i<s.size() && s[i]>='0'){
                    x = x*10 + s[i]-'0';
                    i++;
                }
                i--;
                if(operators == '+') stk.push(x); 
                else if(operators == '-') stk.push(-x); 
                else if(operators == '*') {
                    int tmp = stk.top() * x;
                    stk.pop();
                    stk.push(tmp);
                }else{
                    int tmp = stk.top() / x;
                    stk.pop();
                    stk.push(tmp);
                }
                operators = s[i];
            }
            else if(s[i] == ' ') continue;
            else operators = s[i];
        }
        int res = 0;
        while(!stk.empty()){
            res += stk.top(); 
            stk.pop();
        }
        return res;
    }
};


//省去stack,把之前的数存在res里面，pre是上一个数，或者是第一个开始乘或除的数，遇到* or /，对pre进行操作
class Solution {
public:
    int calculate(string s) {
        istringstream ss("+" + s + "+");
        long pre = 0, num, res = 0;
        char c;
        while(ss >> c){
            if(c == '+' || c == '-'){
                res += pre;
                ss >> pre;
                if(c == '-')    pre = -pre; //or use pre = pre*(44-op)
            }
            else{
                ss >> num;
                if(c == '*')
                    pre *= num;
                else
                    pre /= num;
            }
        }
        return res;
    }
};