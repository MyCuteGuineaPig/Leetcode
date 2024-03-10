class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> cur(length + 1);
        for(auto &u: updates){
            cur[u[0]] += u[2];
            cur[u[1] + 1] -= u[2];
        }

        int tot = 0;
        vector<int>res;
        for(int i = 0; i<length; ++i){
            tot += cur[i];
            res.push_back(tot);
        }
        return res;
    }
};