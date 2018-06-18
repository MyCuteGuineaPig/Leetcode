/*
385. Mini Parser

Given a nested list of integers represented as a string, implement a parser to deserialize it.

Each element is either an integer, or a list -- whose elements may also be integers or other lists.

Note: You may assume that the string is well-formed:

String is non-empty.
String does not contain white spaces.
String contains only digits 0-9, [, - ,, ].
Example 1:

Given s = "324",

You should return a NestedInteger object which contains a single integer 324.
Example 2:

Given s = "[123,[456,[789]]]",

Return a NestedInteger object containing a nested list with 2 elements:

1. An integer containing value 123.
2. A nested list containing two elements:
    i.  An integer containing value 456.
    ii. A nested list with one element:
         a. An integer containing value 789.

*/


/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */


/*
遇到, ] 把之前的integer add，  比如[-1],  [123,456]
遇到],把现在这个nested list加入上个nested list
*/
class Solution {
public:
    NestedInteger deserialize(string s) {
        if(s[0]!='['){
            return NestedInteger(stoi(s));
        }
        stack<NestedInteger>stk;
        int start;
        for(int i = 0; i<s.size();i++){
            if(s[i] == '[') stk.push(NestedInteger());
            else if(s[i]=='-' || isdigit(s[i])){
                start = i;
                while(s[i]=='-' || isdigit(s[i])) i++;
                i--;
            }
            else if(s[i] == ',' || s[i] == ']'){ //maybe [-1], or [-1,[123]]
                if(isdigit(s[i-1]))  stk.top().add(NestedInteger(stoi(s.substr(start, i -start )))); 
                if(s[i] == ']' && stk.size()>1){//】代表这个nested list的结尾
                    NestedInteger top = stk.top();stk.pop();
                    stk.top().add(top);
                }
            }
        }
        return stk.top();
    }
};


//recursive solution
class Solution {
public:
    NestedInteger deserialize(string s) {
        if (s.empty()) {
            return NestedInteger();
        }
        int i = 0;
        return deserializeHelper(s, &i);
    }

private:
    NestedInteger deserializeHelper(const string& s, int *i) {
        NestedInteger result;
        if (s[*i] != '[') {
            int j = *i;
            while (j < s.length() && (s[j] == '-' || isdigit(s[j]))) {
                ++j;
            }
            result.setInteger(stoi(s.substr(*i, j - *i + 1)));
            *i = j;
        } else {
            ++(*i);
            while (*i < s.length() && s[*i] != ']') {
                result.add(deserializeHelper(s, i));
                if (*i < s.length() && s[*i] == ',') {
                    ++(*i);
                }
            }
            ++(*i);
        }
        return result;
    }
};

class Solution {
public:
    NestedInteger deserialize(string s) {
        if (s.empty()) {
            return NestedInteger();
        }
        istringstream in(s);  // copy string: extra O(n) space
        return deserializeHelper(in);
    }

private:
    NestedInteger deserializeHelper(istringstream &in) {
        NestedInteger result;
        int num = 0;
        if (in >> num) {
            result.setInteger(num);
        } else {
            in.clear();
            in.get();
            while (in.peek() != ']') {
                result.add(deserializeHelper(in));
                if (in.peek() == ',') {
                    in.get();
                }
            }
            in.get();
        }
        return result;
    }
};