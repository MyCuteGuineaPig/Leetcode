class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        vector<string> ans;
        for(auto i:words)
        {
            for(auto j: words)
            {
                if(i==j) continue;
                if(j.find(i)!=-1)
                {
                    ans.push_back(i);
                    break;                    
                }
            }
        }
        return ans;
    }

class Solution {
    public:
        vector<string> stringMatching(vector<string>& words) {
            vector<string> res; 
            for(int i = 0; i<words.size(); ++i){
                for(int j = 0; j<words.size(); ++j){
                    if(j == i) continue;
                    if(kmp(words[i],words[j])){
                        res.push_back(words[i]);
                        break;
                    }
                }
            }
            return res;
        }
        bool kmp(const string& a, const string& b){
            if( a.size() > b.size())
                return false;
            string s = a + "#" + b;
            vector<int>lps(s.size());
            int j = 0;
            for(int i = 1; i<s.size(); ++i){
                while(j>0 && s[i]!=s[j])
                    j = lps[j-1];
                if (s[i] == s[j])
                    ++j;
                lps[i] = j;
            }
            for(int i = a.size() + 1; i < s.size(); ++i){
                if(lps[i] == a.size())
                    return true;
            }
            return false;
        }
    };
};

class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        vector<vector<int>>lps; 
        vector<string> res; 
        for(auto s: words)
            lps.push_back(kmp(s));
        for(int i = 0; i<words.size(); ++i){
            for(int j = 0; j<words.size(); ++j){
                if(j == i) continue;
                if(checkIfAContainsB(words[j],words[i],  lps[i])){
                    res.push_back(words[i]);
                    break;
                }
            }
        }
        return res;
    }
    vector<int> kmp(const string& s){
        vector<int>lps(s.size());
        int j = 0;
        for(int i = 1; i<s.size(); ++i){
            while(j>0 && s[i]!=s[j])
                j = lps[j-1];
            if (s[i] == s[j])
                ++j;
            lps[i] = j;
        }
        return lps;
    }

    bool checkIfAContainsB(const string& a, const string& b, const vector<int>& lpsb){
        if (a.size() < b.size())
            return false;
        for(int i = 0, j = 0; i<a.size(); ++i){
            while(j > 0 && a[i]!=b[j])
                j = lpsb[j-1];
            if (a[i] == b[j])
                ++j;
            if (j == b.size())
                return true;
        }
        return false;
    }
};