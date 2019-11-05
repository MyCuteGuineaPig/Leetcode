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
