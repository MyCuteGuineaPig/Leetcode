
309. Best Time to Buy and Sell Stock with Cooldown
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
        
