/*
816. Ambiguous Coordinates

We had some 2-dimensional coordinates, like "(1, 3)" or "(2, 0.5)". 
Then, we removed all commas, decimal points, and spaces, and ended up with the string S.  
Return a list of strings representing all possibilities for what our original coordinates could have been.

Our original representation never had extraneous zeroes, 
so we never started with numbers like "00", "0.0", "0.00", "1.0", "001", "00.01", 
or any other number that can be represented with less digits.  
Also, a decimal point within a number never occurs without at least one digit occuring before it, 
so we never started with numbers like ".1".

The final answer list can be returned in any order.  
Also note that all coordinates in the final answer have exactly one space between them (occurring after the comma.)

Example 1:
Input: "(123)"
Output: ["(1, 23)", "(12, 3)", "(1.2, 3)", "(1, 2.3)"]
Example 2:
Input: "(00011)"
Output:  ["(0.001, 1)", "(0, 0.011)"]
Explanation: 
0.0, 00, 0001 or 00.01 are not allowed.
Example 3:
Input: "(0123)"
Output: ["(0, 123)", "(0, 12.3)", "(0, 1.23)", "(0.1, 23)", "(0.1, 2.3)", "(0.12, 3)"]
Example 4:
Input: "(100)"
Output: [(10, 0)]
Explanation: 
1.0 is not allowed.
 

Note:

4 <= S.length <= 12.
S[0] = "(", S[S.length - 1] = ")", and the other elements in S are digits.
 

*/



/*

选择小数点的关键是 不能左面位0， 右面结束也是0，比如00.1230不可以，但是即使左面等于0， 右面最后也不可以是0
*/
class Solution {
public:
    vector<string> ambiguousCoordinates(string S) {
        vector<string>res;
        for(int i = 1; i<S.size()-1; i++){
            vector<string>left = make(S, 1, i);
            vector<string>right = make(S, i+1, S.size()-2);
            for(auto l: left){
                for(auto r: right){
                    string cur = "(";
                    cur = cur + l + ", " + r+")";
                    res.push_back(move(cur));
                }
            }
        }
        return res;   
    }
    
    vector<string> make(const string& s, int start, int end){
        vector<string>res;
        for(int i = start ; i <=end; i++){
            string left = s.substr(start, i-start+1);
            string right = s.substr(i+1, end-i);
            if( (left.front()!='0' || left == "0") && (right.empty() || right.back() != '0')){
                if(!right.empty()) left += ".";
                left += right;
                //cout<<" left "<<left<<" right "<<right<<endl;
                res.push_back(left);
            }
        }
        return res;
    }
};


/*
In sub functon f(S)
if S == "": return []
if S == "0": return [S]
if S == "0XXX0": return []
if S == "0XXX": return ["0.XXX"]
if S == "XXX0": return [S]
return [S, "X.XXX", "XX.XX", "XXX.X"...]



*/

class Solution {
public:
    vector<string> ambiguousCoordinates(string S) {
        vector<string>res;
        for(int i = 1; i<S.size()-1; i++){
            vector<string>left = make(S.substr(1,i-1+1));
            vector<string>right = make(S.substr(i+1,S.size()-i-2));
            for(auto l: left){
                for(auto r: right){
                    string cur = "(";
                    cur = cur + l + ", " + r+")";
                    res.push_back(move(cur));
                }
            }
        }
        return res;   
    }
    
    vector<string> make(string s){
        //cout<<"in "<<s<<endl;
        int n = s.size();
        if (n  == 0 || n > 1 && s.front() == '0' && s.back() == '0') return {};
        if (n == 1 || s.back() == '0') return {s};
        if (s.front() == '0') return { "0."+s.substr(1)};
        vector<string>res = {s};
        for(int i = 0; i<s.size()-1; i++){
            res.push_back(s.substr(0, i+1)+"."+s.substr(i+1));
        }
        return res;
    }
};