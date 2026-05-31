class Solution:
    def maximumSaleItems(self, items: List[List[int]], budget: int) -> int:
        n = len(items)

        bonus = [0] * n
        for i in range(n):
            f, _ = items[i]
            count = 0
            for j in range(n):
                d, _ = items[j]
                if i == j:
                    count += 1 
                elif d % f == 0:
                    count += 1 
            bonus[i] = count 

        min_price = min(price for _, price in items)

        dp = [-1]*(budget+1)
        dp[0] = 0 

        for i in range(n):
            _, price = items[i]
            b_val = bonus[i]

            for w in range(budget, price - 1, -1):
                if dp[w-price] != -1: 
                    dp[w] = max(dp[w], dp[w-price] + b_val)

        max_total_item = 0 

        for w in range(budget+1): 
            if dp[w] != -1:
                remaining_budget = budget - w 
                extra = remaining_budget // min_price 

                total_item = dp[w] + extra
                max_total_item = max(max_total_item, total_item)

        return max_total_item

