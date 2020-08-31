/*
Let's take an example to illustrate.
Stamp = "abc", Target = "ababcbc`

1. Target = ab***bc
2. Target = ab*****
3. Target = *******


You can see in the step 1, we replace substring abc with ***. 
Then we keep doing the same thing. In the step 2, you will find we replace substring *bc to ***. 
* can match to any character because * will be override by the next stamp.

*/

 class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
        vector<int>res;
        vector<int>visited(target.size()); //如果当前可以做起点，就设为1
         //要是没有visited, 可能重复visited 某个点，
         //比如 Stamp = "abc", Target = "ababcbc`, 第二次 Target[2:4] 全是*，但canReplace 返回仍是True
        int n = target.size();
        while(n>0){
            bool find = false;
            for(int i = 0; i<=target.size() - stamp.size() && n > 0;++i){
                if(visited[i]==0 && canReplace(stamp, target,i)){
                    find = true;
                    res.push_back(i);
                    visited[i] = 1;
                    replace(stamp.size(), target, i, n);
                }
            }
            if(!find) return {};
        }
        reverse(res.begin(), res.end());
        return res;
    }

    bool canReplace(const string& stamp, string& target, int i){
        for(int j = 0; j<stamp.size() && i<target.size(); ++i, ++j)
            if( target[i]!= '*' && stamp[j] != target[i])
                return false;
        return true;
    }   

    void replace(int stampSize, string& target, int i, int & cnt){
        for(; stampSize ; ++i, stampSize--){
            if(target[i] != '*'){
                target[i] = '*';
                --cnt;
            }
        }
    }
};




/*

target = 'aabccbc', and stamp is 'abc'. 
We first try to find 'abc' and replace it with '***'. After there are no more replacements, 
we will try '*bc' and 'ab*', and so on. Now, turn by turn:

'aabccbc' ? 'abc' = [1]
'a***cbc' ? '*bc' = []
'a***cbc' ? 'ab*' = []
'a***cbc' ? 'a**' = [0]
'****cbc' ? '*b*' = []
'****cbc' ? '**c' = [2]
'*****bc' ? '*bc' = [4]

The resut is [4,2,1,0]

 */


class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
      vector<int> res;
      auto total_stamp = 0, turn_stamp = -1;
      while (turn_stamp) {
          turn_stamp = 0;
          for (int sz = stamp.size(); sz > 0; --sz) 
              for (auto i = 0; i <= stamp.size() - sz; ++i) {
                  auto new_stamp = string(i, '*') + stamp.substr(i, sz) + string(stamp.size() - sz - i, '*');
                  auto pos = target.find(new_stamp);
                  while (pos != string::npos) {
                      res.push_back(pos);
                      turn_stamp += sz;
                      fill(begin(target) + pos, begin(target) + pos + stamp.size(), '*');
                      pos = target.find(new_stamp);
                  }
              }
          total_stamp += turn_stamp;
      }
      reverse(begin(res), end(res));
      return total_stamp == target.size() ? res : vector<int>();
    }
};






class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
        vector<int> ans;
        string str = target;
        string aim(target.length(),'*');
        while(str != aim){
            int tmp = remove(str,stamp);
            if(tmp == str.length()) return {};
            ans.push_back(tmp);
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
    int remove(string& str, string stamp){
        for(int iter=0;iter<str.length();++iter){
            int jter=0,tmp=iter;
            bool flag=false; //flag 是避免 **** match abcd  返回第一个*的位置
            while(jter<stamp.length() && tmp<str.length() && (str[tmp]=='*' || str[tmp]==stamp[jter])){
                if(str[tmp]==stamp[jter]) flag=true;
                tmp++;
                jter++;
            }
            if(jter==stamp.length() && flag){
                for(int kter=0;kter<stamp.length();++kter)
                    str[iter+kter]='*';
                return iter;
            }
        }
        return str.length();
    }
};



class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
        int NS = stamp.size(), NT = target.size();
        vector<int> ans;
        bool has_match;
        do {
            has_match = false;
            for(int i=0;i<=NT-NS;i++) {
                bool ok = true;
                int num_dot = 0;
                for(int j=0;j<NS;j++) { 
                    if(target[i+j]=='.')num_dot++; // take care we don't match only matched ones
                    if(target[i+j]!='.' && stamp[j]!=target[i+j]) { // simple wildcard matching 
                        ok=false;
                        break;
                    }
                }
                if(ok && num_dot<NS) {
                    has_match = true;
                    ans.push_back(i);
                    for(int j=0;j<NS;j++) target[i+j]='.';
                }
            }

        } while(has_match);
        for(char a:target)if(a!='.')return {};
        reverse(ans.begin(),ans.end());
        return ans;
    }
};



class Solution {
public:
    vector<int> movesToStamp(string s, string t) {
        int n = t.size(), m = s.size();
        
        auto check = [&](int i) {
            for (int j = 0; j < m; j++) {
                if (t[i + j] != '?' && t[i + j] != s[j]) return false;
            }
            for (int j = 0; j < m; j++) {
                if (t[i + j] != '?') return true;
            }
            return false;
        };
        
        vector<int> moves;
        string done(n, '?');
        
        while (t != done) {
            bool move = false;
            for (int i = 0; i < n - m + 1; i++) {
                if (check(i)) {
                    fill(t.begin() + i, t.begin() + i + m, '?');
                    moves.push_back(i);
                    move = true;
                }
            }
            if (!move) return {};
        }
        
        reverse(moves.begin(), moves.end());
        return moves;
    }
};