/*
224. Basic Calculator
Example 1:

Input: "1 + 1"
Output: 2
Example 2:

Input: " 2-1 + 2 "
Output: 3
Example 3:

Input: "(1+(4+5+2)-3)+(6+8)"
Output: 23
*/

class Solution {
public:
    int n;
    int calculate(string s) {
        stack<char>signstk;
        stack<int>intstk;
        n = s.size();
        int i = 0, res = 0, start = 0;
        char sign;
        next(s,i); //get rid of space before " 2-1 + 2 "
        while(i<n){
            //cout<<s[i]<<"  cur "<<endl;
            if(isdigit(s[i])){
                intstk.push(nextInt(s,i));
                if(!signstk.empty() && signstk.top()!= '(')  calculate(intstk,signstk);
                else if(!signstk.empty() && signstk.top()== '(') //pop the ( before, so in the end ) can do operation before(
                    signstk.pop();
            }
            else if(s[i] == ')' && !signstk.empty() && signstk.top()!='(') calculate(intstk,signstk);
                /* 
                    有可能( 是起始位置，这样signstk为空
                    比如 ((2+3)+5) 到3后的)不往前算，但是5+(2+3) 这个到3后的)往前算一个
                */
            else signstk.push(s[i]);
            next(s,++i);
        }
        return intstk.top();
    }

    void calculate(stack<int>&intstk, stack<char>& signstk){
        int b = intstk.top(); intstk.pop();
        char sign = signstk.top(); signstk.pop();
        int a = intstk.top();intstk.pop();
        if(sign == '+') intstk.push(a+b);
        else intstk.push(a-b);
    }
    
    void next(const string& s, int& i){
        while(i<n && s[i]==' ') i++; 
    }
    
    int nextInt(const string&s, int& i){
        int start = i;
        while(i<n && isdigit(s[i])) {
            i++; 
        }
        i--;
        return stoi(s.substr(start,i-start+1));
    }
};




class Solution { //从后往前
public:
    int calculate(string s) {
        stack<int> operands;
        stack<char> operators;
        string operand;
        for (int i = s.length() - 1; i >= 0; --i) {
            if (isdigit(s[i])) {
                operand.push_back(s[i]);
                if (i == 0 || !isdigit(s[i - 1])) {
                    reverse(operand.begin(), operand.end());
                    operands.emplace(stoi(operand));
                    operand.clear();
                }
            } else if (s[i] == ')' || s[i] == '+' || s[i] == '-') {
                operators.emplace(s[i]);
            } else if (s[i] == '(') {
                while (operators.top() != ')') {
                    compute(operands, operators);
                }
                operators.pop();
            }
        }
        while (!operators.empty()) {
            compute(operands, operators);
        }
        return operands.top();
    }

    void compute(stack<int>& operands, stack<char>& operators) {
        const int left = operands.top();
        operands.pop();
        const int right = operands.top();
        operands.pop();
        const char op = operators.top();
        operators.pop();
        if (op == '+') {
            operands.emplace(left + right);
        } else if (op == '-') {
            operands.emplace(left - right);
        }
    } 
};

class Solution {
public:
    int calculate(string s) {
        stack<int> stk;
        int res=0;
        int sign=1;
        int n=s.size();
        for(int i=0;i<n;i++){
            char c=s[i];
            if(c>='0'&&c<='9'){
                int num=0;
                while(i<n&&s[i]>='0'){
                    num=num*10+s[i++]-'0';
                }
                res+=sign*num;
                i--;
            }else if(c=='+'){
                sign=1;
            }else if(c=='-'){
                sign=-1;
            }else if(c=='('){
                stk.push(res);
                stk.push(sign);
                res=0;
                sign=1;   
            }else if(c==')'){
                res*=stk.top();stk.pop();
                res+=stk.top();stk.pop();
            }
        }
        return res;
    }
};




int calculate(string s) {
    int total = 0;
    vector<int> signs(2, 1); //需要push进两个， 比如(1+2), 遇到） 如果push一个，）pop之后stack为空，下一个sign找sign top 会报错了
    for (int i=0; i<s.size(); i++) {
        char c = s[i];
        if (c >= '0') {
            int number = 0;
            while (i < s.size()  &&  s[i] >= '0')
                number = 10 * number + s[i++] - '0';
            total += signs.back() * number;
            signs.pop_back(); 
            i--;
        }
        else if (c == ')')
            signs.pop_back();//因为遇到这个，前面sign是'(' 所以要pop back
        else if (c != ' ') 
            signs.push_back(signs.back() * (c == '-' ? -1 : 1)); //这样子比如 -(1+2+3), 前面是-，那么1*（-1） 加变减, 相当于把括号打开了
    }
    return total;
}




//recursive
class Solution {
public:
    int calculate(string s) {
        int pos=0;
        return evaluate(s,pos);
    }
    
    int evaluate(string& s, int& i) {
        int res = 0;
        bool negFlag=false;
        while(i<s.size()&&s[i]!=')') {
            if(s[i]=='+'||s[i]==' ') 
                i++;
            else if(s[i]=='-') {
                i++;
                negFlag=true;
            }
            else if(s[i]=='(') {
                i++;
                res+=negFlag?-evaluate(s,i):evaluate(s,i);
                negFlag=false;
            }
            else {// numeric chars
                int num=0;
                while(i<s.size()&&isdigit(s[i]))
                    num = num*10 + s[i++]-'0';
                res+=negFlag?-num:num;
                negFlag=false;
            }
        }
        i++; // skip the current ')'
        return res;
    }
};