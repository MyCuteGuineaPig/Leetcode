class Solution {
public:
    int minOperations(vector<int>& nums) {
        unordered_map<int,int>mp;
        for(int i = 0; i < nums.size(); ++i){
            ++mp[nums[i]];
        }
        int res = 0;
        for(auto it: mp){
            if(it.second == 1){
                return -1;
            }
            if (it.second % 3 == 0){
                res += it.second / 3;
            }
            else if(it.second % 3 == 1){
                res += 2 + (it.second - 4)/3;
            } else if (it.second % 3 == 2){
                res += 1 + it.second / 3;
            }
        }
        return res;
    }
};


class Solution {
public:
    int minOperations(vector<int>& nums) {
        unordered_map<int, int> counter;
        for (int num : nums) {
            counter[num]++;
        }
        int ans = 0;
        for (auto [_, c]: counter) {
            if (c == 1) {
                return -1;
            }
            ans += ceil((double)(c) / 3);
        }
        return ans;
    }
};


class Solution {
public:
    int minOperations(vector<int>& nums) {
        unordered_map<int, int> m;
        for (int n : nums)
            ++m[n];
        int res = 0;
        for (auto [_, cnt] : m) {
            if (cnt == 1)
                return -1;
            res += cnt / 3 + (cnt % 3 > 0);
        }
        return res;
    }
};