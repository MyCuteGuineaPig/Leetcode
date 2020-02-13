/*
394. Decode String


Given an encoded string, return it's decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. 
Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. 
For example, there won't be input like 3a or 2[4].

Examples:

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
*/


/*
遇到num, push num 进num stack, 遇到'[',push “”进pat stack, 遇到string，如果pat stack不为空，append top, 如果为空，append res, 遇到"]",
*/
class Solution {
public:
    string decodeString(string s) {
        stack<string>pat;
        stack<int>cnt;
        string res, temp;
        for(int i = 0; i<s.size();i++){
            if(isdigit(s[i])){
                int x = 0;
                while(i<s.size() && isdigit(s[i])){
                    x = x*10 + s[i++] - '0';
                }
                i--; cnt.push(x);
            }
            else if(s[i]=='['){
                pat.push("");
            }
            else if(isalpha(s[i])){ 
                if (!pat.empty()) pat.top() += s[i];// avoid this, "3[a2[c]ee]" accee
                else res += s[i]; // "2[abc]3[cd]ef" 结尾的ef 可以添加上去
            }
            else if(s[i] == ']'){
                int n = cnt.top(); cnt.pop();
                string topstr = pat.top(); pat.pop();
                string temp;
                for(int j = 0; j<n;j++){
                    temp += topstr;
                }
                if(pat.empty()) res += temp;
                else pat.top() += temp;
            }
        }
        return res;
    }
};


//Good Solution,
//遇到']' assume always have something inside strs stack
class Solution {
public:
    string decodeString(string s) {
        string curr;
        stack<int> nums; //存的是在[ 之前已经有的string
        stack<string> strs; //存的是[ 之后的string 重复多少回
        int n = 0;
        for (const auto& c: s) {
            if (isdigit(c)) {
                n = n * 10 + c - '0';
            } else if (c == '[') {
                nums.emplace(n); //把num 弄进去
                n = 0;
                strs.emplace(curr); //push之前的string，
                curr.clear();
            } else if (c == ']') {
                for (; nums.top() > 0; --nums.top()) {
                    strs.top() += curr; //把之前stk的string append 现在k个string
                }
                nums.pop();
                curr = strs.top();//把append之后的string作为现在的string
                strs.pop();
            } else {
                curr += c;
            }
        }
        return curr;
    }
};

/*
recursive
*/
class Solution {
public:
    string decodeString(const string& s, int& i) {
        string res;
        
        while (i < s.length() && s[i] != ']') {
            if (!isdigit(s[i]))
                res += s[i++];
            else {
                int n = 0;
                while (i < s.length() && isdigit(s[i]))
                    n = n * 10 + s[i++] - '0';
                    
                i++; // '['
                string t = decodeString(s, i);
                i++; // ']'
                
                while (n-- > 0)
                    res += t;
            }
        }
        
        return res;
    }

    string decodeString(string s) {
        int i = 0;
        return decodeString(s, i);
    }
};


/*

Every time we meet a '[', we treat it as a subproblem so call our recursive function to 
get the content in that '[' and ']'. After that, repeat that content for 'num' times.

Every time we meet a ']', we know a subproblem finished and just return the 'word' we got in this subproblem.
Please notice that the 'pos' is passed by reference, use it to record the position of the original string 
we are looking at.


*/


class Solution {
public:
    string decodeString(string s) {
        int pos = 0;
        return helper(pos, s);
    }
    
    string helper(int& pos, string s) {
        int num=0;
        string word = "";
        for(;pos<s.size(); pos++) {
            char cur = s[pos];
            if(cur == '[') {
                string curStr = helper(++pos, s);
                for(;num>0;num--) word += curStr;
            } else if (cur >= '0' && cur <='9') {
                num = num*10 + cur - '0';
            } else if (cur == ']') {
                return word;
            } else {    // Normal characters
                word += cur;
            }
        }
        return word;
    }
};

