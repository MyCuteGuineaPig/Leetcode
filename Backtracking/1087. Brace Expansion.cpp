class Solution {
public:
   vector<string> expand(string S) {
        vector<string> list(100);
        int n = 0;
        bool option = false;
        for(auto&c : S) {
            if(c == ',')
                continue;
            else if(c == '{'){
                option = true;
            }
            else if(c == '}') {
                option = false;
                ++n;
            }
            else {
                list[n] += c;
                if(!option)
                    ++n;
            }
        }
        
        for(int i = 0; i < n; ++i)
            sort(list[i].begin(), list[i].end());
        vector<string> res;
        
        dfs(list, 0, n, "", res);
        return res;
    }
    
    void dfs(vector<string>& list, int i , int n, string cur, vector<string>& res) {
        if(i == n) {
            res.push_back(cur);
            return;
        }
        
        for(auto& c : list[i])
            dfs(list, i+1, n, cur+c, res);
    } 
};