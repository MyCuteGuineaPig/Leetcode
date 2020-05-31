class Solution:
    def maxProfit(self, prices):
        buy, sell, prev_sell = 10**10, 0, 0,
        for cur in prices:
            buy, sell, prev_sell = min(buy, cur-prev_sell), max(cur - buy, sell), sell
        return sell


from functools import reduce
class Solution:
    def maxProfit(self, prices):
        return reduce(lambda attr, cur: [min(attr[0], cur-attr[2]), max(cur - attr[0], attr[1]), attr[1]], prices, [10**10, 0, 0])[1]
        
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        if n == 0:
            return 0
        buy = [0 for _ in range(n+1)]
        sell = [0 for _ in range(n+1)]
        buy[1] = prices[0]
        for i, p in enumerate(prices[1:],1):
            buy[i+1] = min(buy[i], p - sell[i-1] )
            sell[i+1] = max(sell[i], p - buy[i+1])
        return sell[-1]