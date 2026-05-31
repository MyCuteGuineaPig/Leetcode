class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> bonus(n);
        int min_price = 2000;

        for(int i = 0; i < n; ++i){
            min_price = min(min_price, items[i][1]);
            for(int j = 0; j<n; ++j) 
                if(items[j][0] % items[i][0] == 0)
                    ++bonus[i];
        }

        vector<int>dp(budget+1, -1); dp[0] = 0;
        int total_item = 0;
        for(int i = 0; i < n; ++i){
            int price = items[i][1];
            for(int p = budget; p>=price; --p) { //from big to smaller
                if(dp[p-price]!=-1) {
                    dp[p] = max(dp[p], dp[p-price] + bonus[i]);

                    int remaining_budget = budget - p;
                    total_item = max(total_item, dp[p] + remaining_budget / min_price);
                    //only buy one copy, get all free copy, then use remaining budget to buy more copy with min_price
                }
            }
        }

        return total_item;
    }
};


class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size(); 
        vector<int> bonus(n); 

        
        for(int i = 0; i < n; ++i ) {
            for(int j = 0; j < n; ++j) {
                if(items[j][0] % items[i][0] == 0) bonus[i]++;
            }
        }

        vector<int>dp(budget + 1, -1); dp[0] = 0;
        for(int i = 0; i < n; ++i) {
            int price = items[i][1];

            //use the first time, get all free copy
            for(int j = budget; j >= price; --j) {
                if(dp[j-price] != -1 ) 
                    dp[j] = max(dp[j], dp[j-price] + bonus[i]);
            }

            
            //propagate the current record
            //For example, price = 2, we have 1, 
            //         then price = 4, we can have 2 
            //         then price = 6, we can have 3
            for(int j = price; j <= budget; ++j) {
                if(dp[j-price] != -1)
                    dp[j] = max(dp[j], dp[j-price] + 1);
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};


class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n=items.size();
        vector<int>facs(n,0);
        for(int i=0;i<items.size();i++){
            for(int j=0;j<items.size();j++){
                if(i!=j && items[j][0]%items[i][0]==0)facs[i]++;
            }
        }
        vector<int>dp(budget+1,INT_MIN);dp[0]=0;
        for(int i=0;i<n;i++){
            int p=items[i][1];

            //use previous record to update
            for(int c=budget;c>=p;c--){
                dp[c]=max(dp[c],dp[c-p]+facs[i]+1);
            }
            

            for(int c=p;c<=budget;c++){
                if(dp[c-p]!=INT_MIN)dp[c]=max(dp[c],dp[c-p]+1);
            }
        }
        return *max_element(dp.begin(),dp.end());
    }
};