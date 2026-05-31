class Solution {
public:
    int maxProfit(vector<int>& inventory, int orders) {
        priority_queue<int> pq;
        for(auto i: inventory) 
            pq.push(i);

        long res = 0;
        long mod = 1e9 + 7;
        while(orders--) {
            long top = pq.top(); pq.pop();
            res = (res + top) % mod; 
            pq.push(top - 1);
        }
        return res;
    }
};