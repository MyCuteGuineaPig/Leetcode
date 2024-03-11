/*
150. Evaluate Reverse Polish Notation


Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Note:

Division between two integers should truncate toward zero.
The given RPN expression is always valid. That means the expression would always evaluate to a result and there won't be any divide by zero operation.
Example 1:

Input: ["2", "1", "+", "3", "*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9
Example 2:

Input: ["4", "13", "5", "/", "+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6
Example 3:

Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
Output: 22
Explanation: 
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22


*/
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int>stk;
        for(int i = 0; i<tokens.size();i++){
            if(!is_operator(tokens[i])) stk.push(stoi(tokens[i]));
            else{
                int b = stk.top(); stk.pop();
                int a = stk.top(); stk.pop();
                stk.push(operation(a,b, tokens[i]));
            }
        }
        return stk.top();
    }


    int operation(int a, int b, string sign){
        if (sign == "+") return a+b;
        if (sign == "-") return a-b;
        if (sign == "/") return a/b;
        else return a*b;
    }
    bool is_operator(const string& op) {
        return op.length() == 1 && string("+-*/").find(op) != string::npos;
    }
};


class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int>stk; 
        for(auto& str: tokens){
            if(str == "*"){
                int s2 = stk.top(); stk.pop(); 
                int s1 = stk.top(); stk.pop();
                stk.push(s2 * s1);
            } else if(str == "-"){
                int s2 = stk.top(); stk.pop(); 
                int s1 = stk.top(); stk.pop();
                stk.push(s1 - s2);
            } else if(str == "+"){
                int s2 = stk.top(); stk.pop(); 
                int s1 = stk.top(); stk.pop();
                stk.push(s2 + s1);
            } else if(str == "/"){
                int s2 = stk.top(); stk.pop(); 
                int s1 = stk.top(); stk.pop();
                stk.push(s1 / s2);
            } else {
                stk.push(stoi(str));
            } 

        }
        return stk.top();
    }
};


class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        int n = tokens.size();
        if (n == 0) return 0;
        
        stack<int> nums;
        for (string s : tokens) {
            if (s != "+" && s != "-" && s != "*" && s != "/") nums.push(stoi(s));
            else {
                int n1 = nums.top();
                nums.pop();
                nums.top() = calculate(nums.top(), n1, s);
            }
        }
        return nums.top();
    }
private:
    int calculate(int n1, int n2, string op) {
        if (op == "+") return n1+n2;
        else if (op == "-") return n1-n2;
        else if (op == "*") return n1*n2;
        else if (op == "/") return n1/n2;
    }
};


/*
Recursive solution

*/
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        string s = tokens.back(); tokens.pop_back();
        //cout<<" s "<<s<<endl;
        if(s != "+" && s != "-" && s != "*" && s != "/") return stoi(s);
        
        int r2 = evalRPN(tokens), r1 = evalRPN(tokens); //先r2, 因为r2 靠后面，后面的先pop out
        //cout<<" r2 "<<r2<<" r1 "<<r1<<endl;
        if(s == "+") return r1 + r2;
        if(s == "-") return r1 - r2;
        if(s == "*") return r1 * r2;
        if(s == "/") return r1 / r2;
    }
};