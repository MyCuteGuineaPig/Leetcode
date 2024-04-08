class Solution {
public:
    int countOrders(int n) {
        int mod = 1e9 + 7;
        long  ans = 1;
        for(int i = 2; i<=n; ++i){
            int num_pos = (i-1)*2 + 1; //number of position before i
            //For example, i = 2,  当 i = 1时, [P1, D1], num_pos= 2
            // i = 3,   当 i = 2时, [P1, D1, P2, D2], num_pos= 4
            ans = (((1+num_pos)*num_pos/2 %mod) * ans % mod);
        }
        return ans;
    }
};