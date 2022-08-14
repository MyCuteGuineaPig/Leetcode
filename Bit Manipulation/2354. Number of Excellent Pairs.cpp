/*

The Inclusion-Exclusion Principle
bits(num1 OR num2) + bits(num1 AND num2) = bits(num1) + bits(num2)

*/

class Solution {
public:
    long long countExcellentPairs(vector<int>& nums, int k) {
        vector<long>cnt(30);
        unordered_set<int>num_st(nums.begin(), nums.end());
        for(auto n: num_st)
            cnt[__builtin_popcount(n)]++;
        long res = 0;
        for(int i = 0; i<30; ++i){
            for(int j = 0; j<30; ++j){
                if (i + j >= k ){
                    res += cnt[i]*cnt[j];
                }
                    
            }
        }
        return res;
    }
};

class Solution {
public:
    long long countExcellentPairs(vector<int>& nums, int k) {
        long long cnt[30] = {}, res = 0;
        for (int n : unordered_set<int>(begin(nums), end(nums)))
            ++cnt[__builtin_popcount(n)];
        for (int i = 1; i < 30; ++i)
            for (int j = max(i, k - i); j < 30; ++j)
                res += cnt[i] * cnt[j] * (i == j ? 1 : 2);
        return res;
    }
};


//Two pointer
class Solution {
public:
    long long countExcellentPairs(vector<int>& nums, int k) {
        long long cnt[30] = {};
        for (int n : unordered_set<int>(begin(nums), end(nums)))
            ++cnt[__builtin_popcount(n)];
        long long j = 29, count = 0, res = 0; 
        for (int i = 1; i < 30; ++i)
        {
            while(j >= 0 && (cnt[j] == 0 || i + j >= k))
            {   
                count += cnt[j--]; 
            }
        
            res += count * cnt[i];
        }
        return res;
    }
};