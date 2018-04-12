"""
188. Best Time to Buy and Sell Stock IV
"""

import functools
class Solution:
    def maxProfit(self, k, prices):
        """
        :type k: int
        :type prices: List[int]
        :rtype: int
        """
        if len(prices)<=1: return 0
        if k>=len(prices)/2 :
            return functools.reduce(lambda x,i: x+max(prices[i]-prices[i-1],0),range(1,len(prices)),0)
        profit = [0 for _ in range(len(prices))]
        for _ in range(k):
            cost= prices[0]
            for i, p in enumerate(prices[1:]):
                cost, profit[i+1] = min(p - profit[i+1],cost), max(profit[i],p-cost)
        return profit[-1]
        

import functools
class Solution:
    def maxProfit(self, k, prices):
        """
        :type k: int
        :type prices: List[int]
        :rtype: int
        """
        if len(prices)<=1 or k==0: return 0
        if k>=len(prices)/2 :
            return functools.reduce(lambda x,i: x+max(prices[i]-prices[i-1],0),range(1,len(prices)),0)
        buy = [prices[0] for _ in range(k)]
        sell = [0 for _ in range(k)]
        for _ , p in enumerate(prices[1:]):
            for i in range(k):
                buy[i] = min(p, buy[i]) if i == 0 else min(p-sell[i-1], buy[i]) 
                sell[i] = max(p-buy[i],sell[i])
            #print(buy, sell)
        return sell[-1]
        