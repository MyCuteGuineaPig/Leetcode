class Solution {
public:
    int top_down(const string& s, unordered_map<long long, int>& dp, int index, long long bit_distincts, int can_change, int k){
        if (index >= s.size()){
            return 0;
        }
        long long key = ((long long )index<<27) | (bit_distincts << 1) | can_change;
        if (dp.count(key)){
            return dp[key];
        }
        int chr = s[index] - 'a';
        long long  cur_distinct = bit_distincts | (1 << chr);
        int num_unique = __builtin_popcount(cur_distinct);
        int cur_max = 0;

        if (num_unique > k){
            cur_max = 1 + top_down(s, dp, index + 1, (1 << chr), can_change, k);//new_start
        } else {
            cur_max =  top_down(s, dp, index + 1, cur_distinct, can_change, k);
        }
        if (can_change){
            for(int i = 0; i<26; ++i){
                int chr = i;
                long long cur_distinct = bit_distincts | (1 << chr);
                int num_unique = __builtin_popcount(cur_distinct);
                if (num_unique > k){
                    cur_max = max(cur_max, 1 + top_down(s, dp, index + 1, (1 << chr), 0, k));//new_start
                } else {
                    cur_max = max(cur_max, top_down(s, dp, index + 1, cur_distinct, 0, k));
                }
            }
        }
        return dp[key] = cur_max;
    }
    int maxPartitionsAfterOperations(string s, int k) {
        unordered_map<long long, int> dp;
        return 1+top_down(s, dp, 0, 0, 1, k);
    }
};


class Solution {
public:
    void change_bits_and_update(const string& s, unordered_map<int, unordered_map<bool, unordered_map<long long, int>>>& mp, int index, long long prev_cumulative_bits, int prev_count, int k){
        for(int j = 0; j<26; ++j){
            if (j == (s[index] -'a')){
                continue;
            }
            long long new_bit = 1 << j; //change current s[index] = 'a'+j;
            long long cur_cumulative_bits =  prev_cumulative_bits | new_bit;
            int bits_count = __builtin_popcount(cur_cumulative_bits);
            if(bits_count <= k){
                mp[index][false][cur_cumulative_bits] = max(mp[index][false][cur_cumulative_bits], prev_count); 
            } else{
                mp[index][false][new_bit] = max(mp[index][false][new_bit], prev_count + 1); 
            }
        }
    }
    //bottom up
    int maxPartitionsAfterOperations(string s, int k) {
        if (s.empty()){
            return 0;
        }
        unordered_map<int, unordered_map<bool, unordered_map<long long, int>>> mp;
        //first key index, second key can change, third key is current bitsets 
        long long bits = 1 << ((long long)(s[0] - 'a'));
        mp[0][true][bits] = 1;
        change_bits_and_update(s, mp, 0, 0, 1, k);

        for(int i = 1; i<s.size(); ++i){
            //if can change
            for(const auto cond: {true, false}){
                for(const auto & [prev_cumulative_bits, prev_count]: mp[i-1][cond]){
                    
                
                    long long new_bit = 1 << ((long long)(s[i] - 'a'));
                    long long cur_cumulative_bits =  prev_cumulative_bits | new_bit;
                    int bits_count = __builtin_popcount(cur_cumulative_bits);
                    if (bits_count <= k)
                        mp[i][cond][cur_cumulative_bits] = max(mp[i][cond][cur_cumulative_bits], prev_count);
                    else
                        mp[i][cond][new_bit] = max(mp[i][cond][new_bit], 1+prev_count);
                        //or if we can change the current s[i]
                    if (cond == true)
                        change_bits_and_update(s, mp, i, prev_cumulative_bits, prev_count, k);
                }   
            }
        }
        int res = 0, n = s.size()-1;
        for(const auto cond: {true, false}){
            for(const auto & [cumulative_bits, total_count]: mp[n][cond]){
                res = max(res, total_count);
            }   
        }
        return res;
    }
};