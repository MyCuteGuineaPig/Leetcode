class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        unordered_map<int, int> netbalances;
        for(int i = 0; i< transactions.size(); ++i) {
            netbalances[transactions[i][0]] -= transactions[i][2];
            netbalances[transactions[i][1]] += transactions[i][2];
        }

        vector<int>balances;
        for(auto nb: netbalances)
            if (nb.second!=0)
                balances.push_back(nb.second);
        auto bt = [&](this auto && bt, int index) -> int {

            while(index < balances.size() && balances[index] == 0) 
                ++index;
            if (index == balances.size() ) 
                return 0;
            int move = 1e9;
            for(int i = index+1; i<balances.size(); ++i){
                if(balances[index] * balances[i] < 0) {
                    balances[i] += balances[index];

                    move = min(move, 1 + bt(index+1));
                    //不能是i+1, 比如 1 1 -2,   index = 0, i = 2, 跳过了1

                    balances[i] -= balances[index]; 
                    //需要加回来比如
                    //-4 , 5 , -3 , 4 , -2 ,    先进行的是 index=0, i = 1,
                    //但最佳是 -4 和 4 抵消
                    
                    if(balances[i] + balances[index] == 0) {
                        break;
                    }
                }
            } 
            return move;
        };

        return bt(0);
    }
};



/**
 Let's see an example: [-2, 2, -7, 3, 4]
Say we have N = 5, M=2.
set1 = {-2, 2}, set2 = {-7,3,4}
Let n1 = len(set1) = 2, and n2 = len(set2) = 3.
Because both set1 and set2 are min_set, we have:

For set1, we need n1 - 1 = 1 transaction to settle the debt.
For set2, we need n2 - 1 = 2 transactions to settle the debt.

ans = (transactions for min_set1) + (transactions for min_set2) + ... + (transactions for min_setm)
ans = len(min_set1) - 1 + len(min_set2) - 1 + ... + len(min_setm) - 1
Note: len(min_set1) + len(min_set2) + ... + len(min_setm) = N,
and there are M (-1)'s.
So we have ans = N - M.

 */
class Solution {
public:
    int minTransfers(vector<vector<int>>& transactions) {
        unordered_map<int, int> netbalances;
        for(int i = 0; i< transactions.size(); ++i) {
            netbalances[transactions[i][0]] -= transactions[i][2];
            netbalances[transactions[i][1]] += transactions[i][2];
        }

        vector<int>balances;
        for(auto nb: netbalances)
            if (nb.second!=0)
                balances.push_back(nb.second);

        //for(auto b: balances)
        //    cout << b <<" , ";
        //cout << endl;

        int n = balances.size();
        vector<int>dp(1<<n, -1);
        dp[0] = 0;
        
        auto h = [&](this auto && h, int bit) -> int {
            if (dp[bit]!= -1) {
                return dp[bit];
            }
           
            int ans = 0;
            int balance = 0;
            for(int i = 0; i < n; ++ i) {
                int curbit = 1 << i;
                if (bit & curbit) {
                    balance += balances[i];
                    //cout<<" bit " <<(bitset<8>(bit)) <<" i "<< i << " balance "<<balance<<endl;
                    ans = max(ans, h(bit ^ curbit));
                }
            }
            dp[bit] = ans + (balance == 0);
            //cout<<" bit "<<(bitset<8>(bit))<<" dp[bit] " <<dp[bit]<<endl;
            return  dp[bit];
        };

        return n - h((1<<n)-1);
    }
};