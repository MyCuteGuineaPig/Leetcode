class Solution {
public:
    
    int picklowestK(vector<int>&choice, int k){
        for(int i = 0; i<choice.size(); ++i)
        {
            if ( choice[i] == 0) --k;
            if (k == 0){
                choice[i] = 1;
                return i+1;
            }
        }
        return -1;
    }
    
    string smallestNumber(string pattern) {
        vector<int>D(pattern.size(), 0);
        for(int i = pattern.size()-1; i>=0; --i){
            if(pattern[i] == 'D'){
                if (i == pattern.size() - 1) D[i] = 1;
                else D[i] = D[i+1]+1;
            }
        }
        vector<int>choice(9, 0);
        string cur = "";
        for(int i = 0; i <D.size(); ++i){
            if (D[i] == 0)
                cur += to_string(picklowestK(choice, 1));
            else 
                cur += to_string(picklowestK(choice, D[i]+1));
        }
        return cur + to_string(picklowestK(choice, 1));
    }
};


/*
1 2 3 4 5 6 7 8 9
D D I D D I D D

Match the input string and the sequence 1,2,3,4,5,6,7,8,9.
Reverse all numbers between "I".

For example:
first 'I' at 3, then reverse 1,2,3, we have 3,2,1
second 'I' at 6, then reverse 4,5,6, we have 6,5,4
Reverse the last group 7,8,9, we have 9,8,7

Final result for D D I D D I D D,
is 3,2,1,6,5,4,9,8,7

*/

class Solution {
public:
   string smallestNumber(string s) {
        string res, stack;
        for (int i = 0; i <= s.length(); i++) {
            stack.push_back('1' + i);
            if (i == s.length() || s[i] == 'I') {
                while (!stack.empty()) {
                    res.push_back(stack.back());
                    stack.pop_back();
                }
            }
        }
        return res;
    }
};

class Solution {
public:
   string smallestNumber(string s) {
        string res;
        int n = s.size(), j = 0;
        for (int i = 0; i <= s.size(); ++i) {
            res.push_back('1' + i);
            if (i == n || s[i] == 'I') {
                reverse(res.begin() + j, res.end());
                j = i + 1;
            }
        }
        return res;
    }
};

//stack
class Solution {
public:
    string smallestNumber(string pattern) {
        stack<int>stk;
        string res;
        for(int i = 0; i<=pattern.size(); ++i){
            if (i>0 && pattern[i-1] == 'I'){
                while(!stk.empty()) {
                    res += to_string(stk.top());
                    stk.pop();
                }
            }
            stk.push(i+1);
        }
        while(!stk.empty()){
            res += to_string(stk.top());
            stk.pop();
        }
        return res;
    }
};

class Solution {
public:
    string smallestNumber(string pattern) {
        stack<int> s;
        string ans = "";
        if(pattern[0] == 'I') ans += '1';
        else s.push('1');
        for(int i = 1; i <= pattern.size(); i++){
            if(pattern[i-1] == 'I'){
                while(!s.empty()){  ans += s.top(); s.pop(); }
            }
            s.push('0' + i+1);
        }
        while(!s.empty()){ ans += s.top(); s.pop();  }
        return ans;
    }
};


//DFS
class Solution {
public:
    int dfs(string& p, int i, int n, int mask) {
        if (i > p.size())
            return n;
        int res = INT_MAX, last = n % 10, increment = i == 0 || p[i - 1] == 'I';
        for (int d = 1; d <= 9; ++d)
            if ((mask & (1 << d)) == 0 && d > last == increment)
                res = min(res, dfs(p, i + 1, n * 10 + d, mask + (1 << d)));               
        return res;
    }
    string smallestNumber(string pattern) {
        return to_string(dfs(pattern, 0, 0, 0));
    }
};