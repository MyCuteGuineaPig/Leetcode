/*

        L 是 以i 为小点的左侧边界长度
        R 是 以i 为最小的右侧边界长度

                    |--------R-------|
       |-----L--------| 
A      i-L+1 ....   i              i+R-1
        
TotalSum = (presum[i+1] - presum[i-L+1]) + ... + (presum[i+R-1] - presum[i-L+1])
         = (presum[i+1] - presum[i-L+2]) + ... + (presum[i+R-1] - presum[i-L+2])
         ....
         = (presum[i+1] - presum[i]) + ... + (presum[i+R-1] - presum[i]) 

         = L * (presum[i+1] + presum[i+2] + ... + presum[i+R-1] 
            - R*(presum[i-L+1] + presum[i-L+2] ... + presum[i])
+
*/

class Solution {
public:
    int totalStrength(vector<int>& strength) {
        long long res = 0;
        int mod = 1e9 + 7;
        int n = strength.size();

        vector<int>right(n, n);
        vector<int>left(n, -1);
        stack<int>stk;
        for(int i = 0; i < n; ++i){
            while(!stk.empty() && strength[stk.top()] >= strength[i]){
                right[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }
        stk = stack<int>();
        for(int i = n-1; i >=0; --i){
            while(!stk.empty() && strength[stk.top()] > strength[i]){
                left[stk.top()] = i;
                stk.pop();
            }
            stk.push(i);
        }
        vector<long long >presum = {0};
        vector<long long>presum_of_presum = {0};
        long long tot = 0;
        for(int i = 0; i < n; ++i){
            tot += strength[i];
            presum.push_back(tot);
        }
        tot = 0;
        for(int i = 0; i<=n; ++i){
            tot += presum[i];
            presum_of_presum.push_back(tot);
        }
        for(int i = 0; i < n; ++i){
            int left_bound = left[i];
            int right_bound = right[i];

            int left_count = i - left_bound;
            int right_count  = right_bound - i;

            long long pos_presum = (presum_of_presum[right_bound + 1] - presum_of_presum[i+1]) % mod;
            long long neg_presum = (presum_of_presum[i + 1] - presum_of_presum[left_bound+1]) % mod;


// + mod 防止余数负数
            res = (res + strength[i] * (pos_presum * left_count %mod - neg_presum*right_count % mod + mod) % mod) % mod;
        }
        return res;
    }
};