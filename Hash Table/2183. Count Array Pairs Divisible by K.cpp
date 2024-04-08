class Solution {
public:
    long long countPairs(vector<int>& nums, int k) {
        unordered_map<long,long long>mp;
        for(auto & i: nums){
            ++mp[gcd(i, k)];
        }

        long long res = 0;
        for(auto& [a, c1]: mp){
            for(auto & [b, c2]: mp){
                if ( a <= b && a * b % k == 0){
                    res += a < b? c1 * c2 : c1 * (c1-1)/2;
                }
            }
        }
        return res;
    }
};


class Solution {
public:
    long long countPairs(vector<int>& nums, int k) {
        unordered_map<long long, long long> gcdCount;
        long long ans = 0;
        for (long long i = 0; i < nums.size(); ++i)
        {
            long long currgcd = gcd(nums[i], k);
            for (auto &[gc_d, count] : gcdCount)
                if ((currgcd * gc_d) % k == 0)
                    ans += count;
            gcdCount[currgcd]++;
        }
        return ans;
    }
};
