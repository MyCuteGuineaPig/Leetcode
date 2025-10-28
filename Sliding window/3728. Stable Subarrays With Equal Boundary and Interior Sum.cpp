class Solution {
public:
    long long countStableSubarrays(vector<int>& capacity) {
        unordered_map<long, unordered_map<long,int>> mp;
        long res = 0; 
        long pre = 0;
        for(int i = 0; i < capacity.size(); ++i){
            res += mp[capacity[i]][pre - capacity[i]];
            pre += capacity[i];
            mp[capacity[i]][pre]+=1;
            if (i > 0 && capacity[i] == 0 && capacity[i-1] == 0)
                res -= 1;
        } 
        return res;
    }
};