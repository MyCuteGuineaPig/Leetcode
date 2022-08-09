class Solution {
public:
    int arithmeticTriplets(vector<int>& nums, int diff) {
        unordered_set<int>st;
        int res = 0;
        for(auto i: nums){
            if (st.count(i -diff) && st.count(i-diff*2))
                ++res;
            st.insert(i);
        }
        return res;
    }
};

class Solution {
public:
    int arithmeticTriplets(vector<int>& nums, int diff) {
        int cnt[201] = {}, res = 0;
        for (auto n : nums) {
            if (n >= 2 * diff)
                res += cnt[n - diff] && cnt[n - 2 * diff];
            cnt[n] = true;
        }
        return res;
    }
};