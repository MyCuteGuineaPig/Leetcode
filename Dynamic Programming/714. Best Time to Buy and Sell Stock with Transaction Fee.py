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