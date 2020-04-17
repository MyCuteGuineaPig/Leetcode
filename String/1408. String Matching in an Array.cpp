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
};