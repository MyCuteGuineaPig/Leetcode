class Solution {
public:
    int totalFruit(vector<int>& tree) {
        unordered_map<int,int>mp;
        int cnt = 0, res = 0, start = 0;
        for(int i = 0; i<tree.size(); ++i){
            if(mp[tree[i]]++ == 0) ++cnt;
            while(cnt > 2){
                if(--mp[tree[start++]] == 0) --cnt;
            }
            if(cnt <= 2)
                res = max(res, i - start + 1);
        }
        return res;
    }
};