"""
714. Best Time to Buy and Sell Stock with Transaction Fee
"""
class Solution:
    def maxProfit(self, prices, fee):
        """
        :type prices: List[int]
        :type fee: int
        :rtype: int
        """
        buy, sell = 10**10, 0
        for i in prices:
            buy = min(buy, i-sell+fee)
            sell = max(sell, i-buy)
        return sell

class Solution(object):
    def maxProfit(self, prices, fee):
        state = profit = 0 
        last_price = prices[0] 
        for price in prices[1:]:                  
            state += price - last_price
            if state > fee:
                profit += state - fee
                state = fee
            else:
                if state < 0: state = 0 #当遇到低的价格时候
            last_price = price
        return profit