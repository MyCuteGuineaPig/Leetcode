class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        vector<long long>res;
        unordered_map<int, long long>counter;
        set<pair<long long, int>, greater<pair<long long, int>>> top, bottom;

        long long sum = 0;

        auto rebalance = [&](this auto && rebalance){
            while (bottom.size()  && (top.size() < x ||  (*bottom.begin()).first >  (*top.rbegin()).first || (*bottom.begin()).first ==  (*top.rbegin()).first && (*bottom.begin()).second >  (*top.rbegin()).second)) {//一定是while
                auto [big_cnt, big_cnt_num] = *bottom.begin();
                top.insert({big_cnt, big_cnt_num});
                sum += big_cnt * big_cnt_num;
                bottom.erase(bottom.begin());
            }   
            if (top.size()  > x) {
                auto [big_cnt, big_cnt_num] = *top.rbegin();
                bottom.insert({big_cnt, big_cnt_num});
                sum -= big_cnt * big_cnt_num;
                top.erase(prev(top.end()));
            }
        };
        auto remove = [&](this auto&& remove, int num) {
            long long cnt = counter[num];
            if (cnt == 0) return;
            if (auto it = top.find({cnt, num}); it != top.end()) {
                sum -= num * cnt;
                top.erase({cnt, num});
            } else {
                bottom.erase({cnt, num});
                rebalance();
            }
        };
        auto insert = [&](this auto&& insert, int num){
            int cnt = counter[num]; 
            if (cnt == 0) return;
            bottom.insert({cnt, num});
            rebalance();
        };
        for(int i = 0; i < nums.size(); ++i){
            remove(nums[i]); 
            ++counter[nums[i]];
            insert(nums[i]);
            if (i >= k - 1) {
                res.push_back(sum);
                int cnt = counter[nums[i - k + 1]];
                remove(nums[i - k + 1]);
                --counter[nums[i-k+1]];
                insert(nums[i - k + 1]);
            }
        }
        return res;
    }
};


class Solution {
public:
vector<long long> findXSum(vector<int>& nums, int k, int x) {
    vector<long long> res;
    unordered_map<int, int> cnt;
    set<pair<long long, int>, greater<pair<long long, int>>> top, bot;
    long long running_sum = 0;
    for (int i = 0; i < nums.size(); ++i) {
        long long count = cnt[nums[i]];
        if (count) {
            if (auto it = bot.find({count, nums[i]}); it != end(bot))
                bot.erase(it);
            else {
                top.erase({count, nums[i]});
                running_sum -= count * nums[i];               
            }
        }
        cnt[nums[i]] = count + 1;
        top.insert({count + 1, nums[i]});
        running_sum += (count + 1) * nums[i];  
        if (top.size() > x) {
            auto it_top = prev(end(top));
            running_sum -= it_top->first * it_top->second;
            bot.insert({it_top->first, it_top->second});
            top.erase(it_top);
        }
        if (i >= k) {
            int count = cnt[nums[i - k]];
            if (auto it = bot.find({count, nums[i - k]}); it != end(bot))
                bot.erase(it);
            else {
                it = top.find({count, nums[i - k]});
                running_sum -= it->first * it->second; 
                top.erase(it);
            }
            if (count > 1)
                bot.insert({count - 1, nums[i - k]});
            --cnt[nums[i - k]];
            if (top.size() < x)
                if (auto it = begin(bot); it != end(bot)) {
                    running_sum += it->first * it->second;
                    top.insert({it->first, it->second});
                    bot.erase(it);
                }
        }
        if (i + 1 >= k)
            res.push_back(running_sum);
    }
    return res;
}  
};