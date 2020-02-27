/*

93. Restore IP Addresses
Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)



*/

class Solution:
    def restoreIpAddresses(self, s: str) -> List[str]:
        res = []
        cur = []
        def dfs(s):
            if not s and len(cur) == 4:
                res.append('.'.join(cur))
                return 
            if s and len(cur) < 4:
                if s[0] == '0':
                    cur.append('0')
                    dfs(s[1:])
                    cur.pop()
                else:
                    for i in range(1,1+min(3,len(s))):
                        if int(s[:i]) <=255:
                            cur.append(s[:i])
                            dfs(s[i:])
                            cur.pop() 
        dfs(s)
        return res

/*
backtracking
*/

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string>res;
        vector<string>cur;
        backtracking(res,cur, s, 0);
        return res;
    }
    
    void backtracking(vector<string>&res,vector<string>&cur, const string & s, int start){ 
        if(start == s.size()){
           if(cur.size() == 4){
                string temp;
                for(int i =0; i<4; i++){
                    temp+=cur[i];
                    if(i<3) temp+=".";
                }
               res.push_back(temp);
           }
        }
        if(cur.size()>4) return;
        for(int i = start; i<s.size() && i<start+3; i++){
            string sub = s.substr(start,i-start+1);
            if(i-start+1>1 && s[start] == '0') continue; //避免比如 255.055 是不行的
            if(stoi(sub)<=255){
                cur.push_back(sub);
                backtracking(res,cur,s,i+1);
                cur.pop_back();
            }
        }
    }
};


/*
Iterative
*/

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string>res;
        string ans;
        for(int a = 1; a<=3; a++)
            for(int b = 1; b<=3; b++)
                for(int c = 1; c<=3; c++)
                    for(int d = 1; d<=3; d++)
                        if(a+b+c+d == s.length()){
                            int A = stoi(s.substr(0,a));
                            int B= stoi(s.substr(a,b));
                            int C = stoi(s.substr(a+b,c));
                            int D= stoi(s.substr(a+b+c,d));
                            if(A<=255 && B<=255 && C<=255 && D<=255 && (ans = to_string(A) +"." + to_string(B) + "." + to_string(C) + "." + to_string(D)).length() == s.length()+3)
                                res.push_back(ans);
                        }
        return res;
    }
    
};
