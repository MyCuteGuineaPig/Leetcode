/*

301. Remove Invalid Parentheses

Time	    Space	Difficulty
O(C(n, c))	O(c)	Hard

Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results.

Note: The input string may contain letters other than the parentheses ( and ).

Examples:
"()())()" -> ["()()()", "(())()"]
"(a)())()" -> ["(a)()()", "(a())()"]
")(" -> [""]

*/


/**
 * , we generate all possible states by removing one ( or ), check if they are valid, if found valid ones on the current level, put them to the final result list and we are done,
 *  otherwise, add them to a queue and carry on to the next level.
 * The good thing of using BFS is that we can guarantee the number of parentheses that need to be removed is minimal, also no recursion call is needed in BFS.
 * 
 * In BFS we handle the states level by level, in the worst case, we need to handle all the levels, 
 * we can analyze the time complexity level by level and add them up to get the final complexity.

On the first level, there’s only one string which is the input string s, let’s say the length of it is n, to check whether it’s valid, 
we need O(n) time. On the second level, we remove one ( or ) from the first level, so there are C(n, n-1) new strings, 
each of them has n-1 characters, and for each string, we need to check whether it’s valid or not, 
thus the total time complexity on this level is (n-1) x C(n, n-1). 
Come to the third level, total time complexity is (n-2) x C(n, n-2), so on and so forth…

Finally we have this formula:

T(n) = n x C(n, n) + (n-1) x C(n, n-1) + … + 1 x C(n, 1) = n x 2^(n-1).
*/
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        unordered_set<string>visited = {s};
        vector<string>res;
        queue<string>q;
        int step = 0;
        if(s.size()!=0 ){
            if(isValid(s)) return {s};
            else q.push(s);
        }
        while(q.size() && res.empty()){
            int cursize = q.size();
            for(int i = 0; i<cursize; i++){
                string top = q.front();
                q.pop();
                for(int j = 0; j<top.size(); j++){
                    if(top[j]!='(' && top[j]!=')') continue;
                    string substr = top.substr(0,j)+top.substr(j+1,s.size()-j-1);
                    if(visited.find(substr)!=visited.end()) continue;
                    visited.insert(substr);
                    //cout<<endl<<"substr "<<substr<<endl;
                    if(isValid(substr)) res.push_back(substr);
                    else q.push(substr);
                }
            }
        }
        if(res.size()==0) res.push_back("");
        return res;
    }
    
    bool isValid(const string & s){
        stack<char>stk;
        int count = 0;
        for(int k = 0; k<s.size(); k++)
            if(s[k]=='(' || s[k] == ')') stk.push(s[k]);
        while(stk.size() && count >= 0){
            if(stk.top() == ')') count++;
            else if(count==0) count = -1;
            else count--;
            stk.pop();
        }
        if (count == 0) return true;
        else return false;
    }
};




//simplifed bfs

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        unordered_set<string>visited = {s};
        vector<string>res;
        queue<string>q;
        int step = 0;
        q.push(s);
        bool found = false;
        while(q.size()){
            string top = q.front();
            q.pop();
            if(isValid(top)) 
            {
                res.push_back(top);
                found = true;
            }
            if(found) continue; //让它loop through 所有的 solution
            for(int j = 0; j<top.size(); j++){
                if(top[j]!='(' && top[j]!=')') continue;
                string substr = top.substr(0,j)+top.substr(j+1,s.size()-j-1);
                if(visited.find(substr)!=visited.end()) continue;
                visited.insert(substr);
                //cout<<endl<<"substr "<<substr<<endl;
                q.push(substr);
            }
        }
        if(res.size()==0) res.push_back("");
        return res;
    }
    
    bool isValid(const string & s){
      int count = 0;
      for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c == '(') count++;
        if (c == ')' && count-- == 0) return false;
      }
    
      return count == 0;
    }
};



class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int left_removed = 0;
        int right_removed = 0;
        for(int i = 0; i<s.size();i++){
            if(s[i]!='(' && s[i]!=')') continue;
            if(s[i]== ')'){
                if(left_removed>0) left_removed--;
                else right_removed++;
            }else{
                left_removed++;
            }
        }
        if(left_removed == 0 && right_removed == 0) return {s}; 
        unordered_set<string> res;
        dfs(s,res,"",0,left_removed,right_removed,0);
        return vector<string>(res.begin(),res.end());
    }
    
    void dfs(const string & s, unordered_set<string>& res, string cur, int index, int left_removed, int right_removed, int pair){
        if(index == s.size()){
            if(left_removed == 0 && right_removed == 0)
                res.insert(cur);
            return;
        }
        if(s[index] != '(' && s[index] != ')'){
            dfs(s,res,cur+s[index],index+1,left_removed,right_removed, pair);
        }
        if(s[index]=='('){
            if(left_removed>0)
                dfs(s,res,cur,index+1,left_removed-1,right_removed, pair);
            dfs(s,res,cur+s[index],index+1,left_removed,right_removed, pair+1);
        }
        else if(s[index]==')'){
            if(right_removed>0)
                dfs(s,res,cur,index+1,left_removed,right_removed-1, pair);
            if(pair>0) //需要pair的原因：比如 ")(" 这样的话，在)的话，就会进行下个DFS
                dfs(s,res,cur+s[index],index+1,left_removed,right_removed, pair-1);
        }

    }
};



//smart idea

/*
process redundant ")" from left to right, process redundant "(" from right to left
*/

class Solution {
    private:
        vector<string> res;
        string p={'(',')'};
    
        void helper(string& s, int si, int sj, int rev){
            //cout<<endl<<"s "<<s<<" si "<<si<<" sj "<<sj<<" rev  "<<rev<<endl;
            int stn=0;
            for(int i=si;i<s.size();i++){
                if(s[i]==p[rev]) stn++;
                else if(s[i]==p[1-rev]) stn--;
                //cout<<"i "<<i <<" s[i] "<<s[i]<<" stk " <<stn<<endl;
                if(stn<0){
                    for(int j=sj;j<=i;j++){
                        //cout<<"j "<<j<<" s[j] "<<s[j]<<"rev  "<<rev<<" p[1-rev ] "<<p[1-rev]<<" si "<<si<<" sj "<<sj<<endl;
                        if(s[j]==p[1-rev] && (j==sj || s[j-1]!=p[1-rev])){
                            
                            string t=s.substr(0,j)+s.substr(j+1);
                            //cout<<" t "<< t <<endl;
                            helper(t, i, j, rev);
                        }
                    }
                    return ;
                }
            }
            string rs=s;
            reverse(rs.begin(), rs.end());
            //cout<<"reversed "<<rs<<endl;
            if(p[rev]=='('){
                //cout<<"go into another "<<endl;
                helper(rs, 0, 0, 1-rev);
            }else{
                //cout<<"push back s "<<rs<<endl;
                res.push_back(rs);
            }
        }    
    public:
        vector<string> removeInvalidParentheses(string s) {
            res.clear();
            helper(s, 0, 0, 0);
            return res;
        }
    };
