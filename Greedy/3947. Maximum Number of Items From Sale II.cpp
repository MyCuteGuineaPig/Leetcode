class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        unordered_map<int, int>factor_cnt;
        int max_factor = 0;
        int min_price = 1e9 + 10; 
        int n  = items.size();

        for(auto item: items) {
            factor_cnt[item[0]]++;
            max_factor = max(max_factor, item[0]);
            min_price = min(min_price, item[1]);
        }
                
        vector<vector<int>> good_deals;
        for(auto& i1: items){
            int f1 = i1[0], price = i1[1];
            if (price >= 2* min_price) 
                continue;
            int multiple_count = 0;
            for(int factor = f1; factor <= max_factor; factor += f1) {
                if (factor_cnt.count(factor)) {
                    multiple_count += factor_cnt[factor];
                }
            }

            int  max_free_limits = multiple_count - 1;
            if (max_free_limits > 0) 
                good_deals.push_back({price, max_free_limits});
        }

        sort(good_deals.begin(), good_deals.end());
        int total_item = 0;
        for(auto& deal : good_deals){
            int price = deal[0], count = deal[1];
            if(budget < price) break; 
            
            int num_copy = budget  / price;
            int max_copy = min(count, num_copy);
            total_item += max_copy * 2; 
            budget -= max_copy*price;
        }
        total_item += budget/min_price;
        return total_item;
    }
};



