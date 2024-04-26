class Solution {
public:
    int helper(vector<NestedInteger>& nestedList, int level){
        if(nestedList.empty()){
            return 0;
        }
        int res = 0;
        for(int i = 0; i < nestedList.size(); ++i){
            if(nestedList[i].isInteger()){
                res += nestedList[i].getInteger() * level;
            }
            else {
                res += helper(nestedList[i].getList(), level+1);
            }
        }
        return res;
    } 

    int depthSum(vector<NestedInteger>& nestedList) {
        return helper(nestedList, 1);
    }
};


class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        int res = 0; 
        queue<pair<vector<NestedInteger>, int>>q;
        q.push({nestedList, 1});
        while(!q.empty()){
            int size = q.size();
            for(int j = 0; j < size; ++j){
                auto [cur, level] = q.front(); q.pop();
                for(int i = 0; i < cur.size(); ++i){
                    if(cur[i].isInteger()){
                        res += cur[i].getInteger() * level;           
                    }
                    else {
                        q.push({cur[i].getList(), level+1});
                    }
                }
            }
        }
        return res;
    }
};