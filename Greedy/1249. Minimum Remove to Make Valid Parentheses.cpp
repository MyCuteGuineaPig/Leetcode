class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<int>left_remaining;
        stack<int>right_remaining;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == '(') left_remaining.push(i);
            else if (s[i] == ')'){
                if(!left_remaining.empty()) left_remaining.pop();
                else right_remaining.push(i);
            }
        }
        string res = "";
        for(int i = s.size()-1; i>=0; --i){
            if(!left_remaining.empty() && left_remaining.top() == i){
                left_remaining.pop();
            } else if(!right_remaining.empty() && right_remaining.top() == i){
                right_remaining.pop();
            } else {
                res += s[i];
            }
        }
        return string(res.rbegin(), res.rend());
    }
};

//beat 95.49%
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        vector<int>left(s.size());
        vector<int>right(s.size());
        stack<int>cur;
        for(int i = 0; i<s.size(); i++){    
            if(s[i]!='(' && s[i] !=')') continue; 
            if(s[i] == '(') cur.push(i);
            else if(!cur.empty()){
                left[cur.top()] = 1;
                cur.pop();
                right[i] = 1;
            }
        }
        string res;
        for(int i = 0; i<s.size(); i++)
            if(s[i]!='(' && s[i] !=')' || left[i] ||right[i])
                res += s[i];
        return res;
    }
};


//beat 99.12%
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<int>cur, bad;
        for(int i = 0; i<s.size(); i++){    
            if(s[i]!='(' && s[i] !=')') continue; 
            if(s[i] == '(') 
                cur.push(i);
            else if(!cur.empty()) cur.pop();
            else bad.push(i);
        }
        string res;
        for(int i = s.size()-1; i>=0; i--){
            if(!cur.empty() && i == cur.top()){
                cur.pop();
                continue;
            }
            if(!bad.empty() && i == bad.top()){
                bad.pop();
                continue;
            }
            res += s[i];
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

//From Forum
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<int> sk; 
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] == '(') {
                sk.push(i);
            } else if(s[i] == ')') {
                if(sk.empty()) {
                    s[i] = '*';
                } else {
                    sk.pop();
                }
            }
        }
        
        while(!sk.empty()) {
            s[sk.top()] = '*';
            sk.pop();
        }
        
        s.erase(remove(s.begin(), s.end(), '*'), s.end());
        return s;
    }
};

//from https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/discuss/419445/C%2B%2B-stack-and-unordered_set
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<int> mstack;
        unordered_set<int> mset;
        for (int i=0; i<s.size(); i++) {
            if (s[i] == '(')
                mstack.push(i);
            else if (s[i] == ')') {
                if (!mstack.empty())
                    mstack.pop();
                else
                    mset.insert(i);
            }
        }
        while (!mstack.empty()) {
            mset.insert(mstack.top());
            mstack.pop();
        }
        string ans;
        for (int i=0; i<s.size(); i++) {
            if (mset.find(i) == mset.end())
                ans.push_back(s[i]);
        }
        return ans;
    }
};
