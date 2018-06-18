/*
736. Parse Lisp Expression

You are given a string expression representing a Lisp-like expression to return the integer value of.

The syntax for these expressions is given as follows.

An expression is either an integer, a let-expression, an add-expression, a mult-expression, or an assigned variable. 
Expressions always evaluate to a single integer.

(An integer could be positive or negative.)
A let-expression takes the form (let v1 e1 v2 e2 ... vn en expr), where let is always the string "let",
then there are 1 or more pairs of alternating variables and expressions, meaning that the first variable v1 is assigned the value of the expression e1, 
the second variable v2 is assigned the value of the expression e2, and so on sequentially; 
and then the value of this let-expression is the value of the expression expr.

An add-expression takes the form (add e1 e2) where add is always the string "add", there are always two expressions e1, e2, 
and this expression evaluates to the addition of the evaluation of e1 and the evaluation of e2.

A mult-expression takes the form (mult e1 e2) where mult is always the string "mult", there are always two expressions e1, e2, 
and this expression evaluates to the multiplication of the evaluation of e1 and the evaluation of e2.

For the purposes of this question, we will use a smaller subset of variable names. A variable starts with a lowercase letter,
then zero or more lowercase letters or digits. Additionally for your convenience, 
the names "add", "let", or "mult" are protected and will never be used as variable names.
Finally, there is the concept of scope. When an expression of a variable name is evaluated, within the context of that evaluation,
the innermost scope (in terms of parentheses) is checked first for the value of that variable, and then outer scopes are checked sequentially. 
It is guaranteed that every expression is legal. Please see the examples for more details on scope.

Evaluation Examples:
Input: (add 1 2)
Output: 3

Input: (mult 3 (add 2 3))
Output: 15

Input: (let x 2 (mult x 5))
Output: 10

Input: (let x 2 (mult x (let x 3 y 4 (add x y))))
Output: 14
Explanation: In the expression (add x y), when checking for the value of the variable x,
we check from the innermost scope to the outermost in the context of the variable we are trying to evaluate.
Since x = 3 is found first, the value of x is 3.

Input: (let x 3 x 2 x)
Output: 2
Explanation: Assignment in let statements is processed sequentially.

Input: (let x 1 y 2 x (add x y) (add x y))
Output: 5
Explanation: The first (add x y) evaluates as 3, and is assigned to x.
The second (add x y) evaluates as 3+2 = 5.

Input: (let x 2 (add (let x 3 (let x 4 x)) x))
Output: 6
Explanation: Even though (let x 4 x) has a deeper scope, it is outside the context
of the final x in the add-expression.  That final x will equal 2.

Input: (let a1 3 b2 (add a1 1) b2) 
Output 4
Explanation: Variable names can contain digits after the first character.

Note:

The given string expression is well formatted: There are no leading or trailing spaces, there is only a single space separating different components of the string, 
and no space between adjacent parentheses. The expression is guaranteed to be legal and evaluate to an integer.
The length of expression is at most 2000. (It is also non-empty, as that would not be a legal expression.)
The answer and all intermediate calculations of that answer are guaranteed to fit in a 32-bit integer.


*/


/*
遇到'(', 如果之前是let，先把之前的数存成字典，
遇到')', 算当前token的运算, 把算好的结果append 到上个string vector的后面， 比如(mult 3 (add 2 3))， append后成(mult 3 5)
        -- 把token = stkstring.top();
        -- 把字典 == stkdict.top(); 把字典还原成原来的字典, 否则前面赋值的数，可能变成后面赋值的数 比如(let x 2 (mult x (let x 3 y 4 (add x y))))"
其他的情况，push 当前element 进token

算当前运算，
        -- 如果token[0] 是add, 就+，
        -- 如果token[0] 是mult, 就乘
        -- 如果token[0] 是let， 就进行赋值
        进行每个运算时，先看curdict,有没有这个数，有的话，用字典的数，没有的话，转化成integer，再进行运算，
        原因是 比如： "(let x -2 y x y)"  x = -1, 第二个 y = x = -1, 如果不看字典，直接转换stoi(x)， 会报错
*/

class Solution {
public:
    int evaluate(string expression) {
        vector<string>tokens;
        unordered_map<string,int>cur_dict;
        stack<unordered_map<string,int>>stkdict;
        stack<vector<string>>stkstring;
        string res;
        for(int i = 0; i<expression.size();i++){
            if(expression[i] == ' ') continue;
            else if(expression[i] == '('){
                if(!tokens.empty() && tokens[0][0] == 'l')
                {
                    operations(tokens, cur_dict);
                }
                stkdict.push(cur_dict);
                stkstring.push(move(tokens));
                tokens = {};
            }
            else if(expression[i] == ')'){
                res = operations(tokens,cur_dict);
                tokens = stkstring.top();  stkstring.pop();
                cur_dict = stkdict.top(); stkdict.pop(); //需要上个的字典，比如"(let x 2 (mult x (let x 3 y 4 (add x y))))", result =14,  mult x 需要字典 x =2, 否则x用后面赋值的x = 3
                tokens.push_back(res);
            }
            else{
                int j = i;
                while(i<expression.size() && (isalpha(expression[i]) || isdigit(expression[i])) || expression[i] == '-' ) i++;
                tokens.push_back(expression.substr(j, i-j));
                i--;
            }
        }
        //cout<<"tokens "<<tokens.back()<<endl;
        return stoi(res);
    }

    string operations(vector<string>&tokens, unordered_map<string,int>&cur_dict){
        if(tokens[0][0] == 'a' || tokens[0][0] == 'm'){
            int a = cur_dict.count(tokens[1]) ? cur_dict[tokens[1]] : stoi(tokens[1]);
            int b = cur_dict.count(tokens[2]) ? cur_dict[tokens[2]] : stoi(tokens[2]);
            return to_string(tokens[0][0] == 'a' ?  a+b : a*b);
        }
        for(int i = 1; i<tokens.size()-1;i+=2){
            cur_dict[tokens[i]] = cur_dict.count(tokens[i+1]) ? cur_dict[tokens[i+1]] : stoi(tokens[i+1]); //"(let x -2 y x y)" 可能是相互赋值运算
        }
        return  cur_dict.count(tokens.back()) ? to_string(cur_dict[tokens.back()]) :tokens.back();  //(let a1 3 b2 (add a1 1) b2) 有可能返回第一个b2
    }

};



class Solution {
public:
    int evaluate(string expression) {
        vector<string> tokens{""};
        unordered_map<string, string> lookup;
        vector<pair<vector<string>, unordered_map<string, string>>> stk;
        for (const auto& c : expression) {
            if (c == '(') {
                if (tokens[0] == "let") {
                    evaluate(tokens, &lookup);
                }
                stk.emplace_back(move(tokens), lookup);
                tokens = {""};
            } else if (c == ' ') {
                tokens.emplace_back();
            } else if (c == ')') {
                const auto& val = evaluate(tokens, &lookup);
                tie(tokens, lookup) = move(stk.back());
                stk.pop_back();
                tokens.back() += val;
            } else {
                tokens.back().push_back(c);
            }
        }
        return stoi(tokens[0]);
    }

private:
    string evaluate(const vector<string>& tokens, unordered_map<string, string>* lookup) {
        static const unordered_set<string> operators{"add", "mult"};
        if (operators.count(tokens[0])) {
            const auto& a = stoi(getval(*lookup, tokens[1]));
            const auto& b = stoi(getval(*lookup, tokens[2]));
            return to_string(tokens[0] == "add" ? a + b : a * b);
        } 
        for (int i = 1; i < tokens.size() - 1; i += 2) {
            if (!tokens[i + 1].empty()) {
                (*lookup)[tokens[i]] = getval(*lookup, tokens[i + 1]);
            }
        }
        return getval(*lookup, tokens.back());
    }
    
    string getval(const unordered_map<string, string>& lookup, const string& x) {
        return lookup.count(x) ? lookup.at(x) : x;
    }
};



class Solution {
public:
    int evaluate(string expression) {
        unordered_map<string,int> myMap;
        return help(expression,myMap);
    }
    
    int help(string expression,unordered_map<string,int> myMap) {
        if ((expression[0] == '-') || (expression[0] >= '0' && expression[0] <= '9'))
            return stoi(expression);
        else if (expression[0] != '(')
            return myMap[expression];
        //to get rid of the first '(' and the last ')'
        string s = expression.substr(1,expression.size()-2);
        int start = 0;
        string word = parse(s,start);
        if (word == "let") {
            while (true) {
                string variable = parse(s,start);
                //if there is no more expression, simply evaluate the variable
                if (start > s.size())
                    return help(variable,myMap);
                string temp = parse(s,start);
                myMap[variable] = help(temp,myMap);                    
            }
        }
        else if (word == "add") 
            return help(parse(s,start),myMap) + help(parse(s,start),myMap);
        else if (word == "mult") 
            return help(parse(s,start),myMap) * help(parse(s,start),myMap);
    }
    
    //function to seperate each expression
    string parse(string &s,int &start) {
        int end = start+1, temp = start, count = 1;
        if (s[start] == '(') {
            while (count != 0) {
                if (s[end] == '(')
                    count++;
                else if (s[end] == ')')
                    count--;
                end++;
            }
        }
        else {
            while (end < s.size() && s[end] != ' ')
                end++;
        }
        start = end+1;
        return s.substr(temp,end-temp);
    }
};