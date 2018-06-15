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
        stack<char>stk;
        stack<int>stkint;
        n = s.size();
        int i = 0, res = 0, start = 0;
        char sign;
        while(i<n){
            //cout<<i<<endl;
            next(s,i);
            //cout<<" a "<<i<<endl;
            if(isdigit(s[i])){
                start = i;
                while(i<n && isdigit(s[i])) i++;
                //cout<<" subst "<<s.substr(start, i-start)<<endl;
                stkint.push(stoi(s.substr(start, i-start)));
            }
            else if(s[i] == '(' || s[i] == '+' || s[i] == '-' ){
                stk.push(s[i++]);
                //cout<<" b "<<i<<" sign "<<s[i-1]<<endl;
            }
            else if(s[i]  == '*' || s[i]  == '/' ){
                //cout<<" c "<<i<<endl;
                sign = s[i++];
                next(s,i);
                if (s[i]!='('){
                    int start = i;
                    while(i<n && isdigit(s[i]))i++;
                    int a = stkint.top();
                    stkint.push(operation(a,stoi(s.substr(start, i-start)), sign));
                }else{
                    stk.push(sign);
                    stk.push('(');
                }
                i++;
            }
            else{
                while(!stk.empty()){
                    int b = stkint.top();stkint.pop();
                    sign = stk.top(); stk.pop();
                    int a = stkint.top(); stkint.pop();
                    //cout<<" else "<<a<<" b "<<b<<"  sign "<<sign<<endl;
                    if(stk.top()=='('){
                        stk.pop();
                        int temp = operation(a,b,sign);
                        while(!stk.empty() && (stk.top()=='*' || stk.top()=='/')){
                            sign = stk.top(); stk.pop();
                            a = stkint.top(); stkint.pop();
                            //cout<<" a "<<a<<" tempb "<<temp<<" sign "<<sign; 
                            temp = operation(a, temp,sign);
                            //cout<<" tempres "<<temp<<endl;
                        }
                        //cout<<" push temp "<<temp<<endl;
                        stkint.push(temp);
                        break;
                    }
                    else{
                        stkint.push(operation(a,b,sign));
                    }
                }
                i++;
            }
            next(s,i);
        }
        cout<<" after "<<endl;
        while(!stkint.empty()){
            int b = stkint.top(); stkint.pop();
            if(!stk.empty()){
                char sign = stk.top(); stk.pop();
                int a = stkint.top(); stkint.pop();
                cout<<" a"<<a<<"b"<<b;
                cout<<"sign"<<sign<<"|"<<endl;
                res += operation(a,b,sign);
            }else{
                res+=b;
            }
        }
        return res;
    }

    void next(const string& s, int& i){
        while(i<n && s[i]==' ') i++; 
    }

    int operation(int a, int b, char sign){
        if(sign == '+') return a+b;
        if(sign == '-') return a-b;
        if(sign == '*') return a*b;
        return a/b;
    }
};