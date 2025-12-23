class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        int max_ele = *max_element(nums.begin(), nums.end());
        vector<int>parent(max_ele+1);
        iota(parent.begin(), parent.end(), 0);

        auto f = [&](this auto&& f, int i) -> int {
            return parent[i] == i ? i : parent[i] = f(parent[i]);
        };
        for(auto num: nums) {
            for(int i = 2; i <= sqrt(num); ++i) {
                if(num % i) continue; 
                int p1 = f(num);
                int p2 = f(i);
                int p3 = f(num / i);
                parent[p2] = p1;
                parent[p3] = p1;
            }
        }
        unordered_map<int, int>mp;
        int res = 1;
        for(auto num: nums){
            res = max(res, ++mp[f(num)]);
        }

        return res;
    }
};