"""
 like a knapsack problem.
 把每个数乘以1 或者0 或者-1, 让最后的sum of all number to 0. 


We can consider the sum as the key and positive number sum as the value.
We initally have dp[0] = 0

只keep the largest positive number sum

Let's run through a example, [1,2,3]
First we have {0:0}.
After 1, we have {0: 0, 1: 1, -1: 0}
After 2, we have {0:0, 2:2, -2:0, 1:1, 3:3,-1:1, -1:0,1:2,-3:0}
we will drop 1:1 and -1:0 since they have smaller value with the same key[1]and [-1]. That left us with {0:0, 2:2, -2:0, 3:3,-1:1,1:2,-3:0}
Number 3 is doing pretty much the same.
Then we will get the final result with dp[0]


"""

class Solution:
    def tallestBillboard(self, rods: List[int]) -> int:
        dp = dict()
        dp[0] = 0
        
        for i in rods:
            cur = collections.defaultdict(int)
            for s in dp:
                cur[s+i] = max(dp[s] + i, cur[s+i])
                cur[s] = max(dp[s], cur[s])
                cur[s-i] = max(dp[s], cur[s-i])
            dp = cur
        return dp[0]

class Solution:
    def tallestBillboard(self, rods: List[int]) -> int:
        dp = {0: 0}
        for x in rods:
            for d,y in list(dp.items()): #需要加list(), 否则error:  dictionary change size during iteration
                dp[d + x] = max(dp.get(x + d, 0), y)
                dp[abs(d - x)] = max(dp.get(abs(d - x), 0), y + min(d, x))
        return dp[0]