class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        map<int,int>mp;
        for(auto i: nums)
            mp[i]++;
        int cnt = 0;
        for(auto &i: mp){
            int tmp = i.second;
            i.second = cnt;
            cnt += tmp;
        }
        vector<int>res;
        for(int i = 0; i<nums.size(); ++i){
            res.push_back(mp[nums[i]]);
        }
        return res;
    }
};

class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
            vector<int> sorted(nums);
            sort(sorted.begin(), sorted.end());
            int n = nums.size();
            vector<int> res(n);
            for(int i = 0; i < n; ++i) {
                int x = nums[i];
                auto it = lower_bound(sorted.begin(), sorted.end(), x);
                res[i] = it-sorted.begin();
            }
            return res;
        }
};


class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        const auto& m = *max_element(cbegin(nums), cend(nums));
        auto count = counter(nums);
        for (int i = 0; i <= m; ++i) {
            count[i] += count[i - 1];
        }
        vector<int> result;
        for (const auto& i : nums) {
            result.emplace_back(count[i - 1]);
        }
        return result;
    }

private:
    unordered_map<int, int> counter(const vector<int>& nums) const {
        unordered_map<int, int> count;
        for (const auto& num : nums) {
            ++count[num];
        }
        return count;
    }
};