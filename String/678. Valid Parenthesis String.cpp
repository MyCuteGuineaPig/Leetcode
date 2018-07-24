/*
678. Valid Parenthesis String

Given a string containing only three types of characters: '(', ')' and '*', 
write a function to check whether this string is valid. We define the validity of a string by these rules:

Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string.
An empty string is also valid.
Example 1:
Input: "()"
Output: True
Example 2:
Input: "(*)"
Output: True
Example 3:
Input: "(*))"
Output: True
Note:
The string size will be in the range [1, 100].

*/


/*


"(*)(" return false 因为最一个l的 后面没有*, 前面有不行
用两个stack 分别记录 '(' 和 '*'的位置
如果当前是')', 先pop'(' 再pop'*'; 如果先pop '*', 会给出错误答案(因为 * 可以当做empty)，比如"(*)"， 先pop*，最后剩个'('

最后看'(' 有没有对应的'*'可以pop掉, 

*/

class Solution {
public:
    bool checkValidString(string s) {
        stack<int>l, star;
        for(int i = 0; i<s.size(); i++){
            if(s[i]=='*') star.push(i);
            else if(s[i] == '(') l.push(i);
            else{
                if(l.empty() && star.empty()) return false;
                if(!l.empty()) l.pop();
                else star.pop();
            }
        }
        while(!l.empty() && !star.empty() && l.top() <star.top()){ //因为比如 (*)( 这个是不行的
            l.pop();
            star.pop();
        }
        return l.empty();
    }
};

/*

用low 和high 考虑：


low 表示把* 当成), 如果low小于0，表示可能有过多的 * 变成）, 
high: 表示把 * 当成(, 如果high小于0，表示有太多的')', 因为我们把 '(' + '*' = high

(不会出现比如 low < 0, 是因为过多) 造成的，因为如果是这样, high 会先小于0, 因为'*' + '（' < ')' )

当high大于0， low小于0，表示我们把过多的 * 变成(, 所以把low revert back 到0; 因为'*' 可以被treat成empty

如果loop结束了，low 大于0，表示有过多的（, 因为当( 时， low ++ ，当*),low--

*/


class Solution {
public:
    bool checkValidString(string s) {
        int low = 0, high = 0;
        for(auto i: s){
            low += i == '(' ? 1 : -1;
            high += i == ')'? -1 : 1;
            if(high < 0) return false;
            low = max(0, low);
        }
        return low == 0;
    }
};



/*
Two pass solution 从左向右看是不是所有的')' 都有对应的'(' 和'*'
                  再从右向左看是不是所有的'(', 都有对应的')' 和'*'
*/
class Solution {
public:
    bool checkValidString(string s) {
        for (int i = 0, cnt = 0, star = 0; i < n; i++) {
            if (s[i] == '(') 
                cnt++;
            else if (s[i] == '*') 
                star++;
            else {
                if (cnt == 0 && star == 0) return false;
                if (cnt) 
                    cnt--;
                else 
                    star--;
            }
        }
        for (int i = n-1, cnt = 0, star = 0; i >= 0; i--) {
            if (s[i] == ')') 
                cnt++;
            else if (s[i] == '*') 
                star++;
            else {
                if (cnt == 0 && star == 0) return false;
                if (cnt) 
                    cnt--;
                else 
                    star--;
            }
        }
        return true;
    }
};