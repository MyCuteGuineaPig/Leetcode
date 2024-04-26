class Solution {
public:
    vector<int> findBuildings(vector<int>& heights) {
        vector<int>stk;
        for(int i = 0; i < heights.size(); ++i){
            while(!stk.empty() && heights[stk.back()] <= heights[i]){
                stk.pop_back();
            }
            stk.push_back(i);
        }
        return stk;
    }
};