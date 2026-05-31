class Solution:
    def maximumSaleItems(self, items: List[List[int]], budget: int) -> int:
        factor_count = Counter(factor for factor, _ in items )

        max_factor = max(factor_count.keys()) if factor_count else 0 

        min_price = min(price for _, price in items )

        good_deals = []

        for factor, price in items:
            multiple_count = 0 
            for multiple in range(factor, max_factor+1, factor):
                multiple_count += factor_count[multiple]

            max_free_limits = multiple_count - 1 

            if max_free_limits > 0 and price < 2*min_price: 
                good_deals.append((price, max_free_limits))


        good_deals.sort()

        total_items = 0

        for price, limit in good_deals:
            if budget < price: 
                continue 

            max_afforable = budget // price 

            copies_to_buy = min(max_afforable, limit)

            total_items += copies_to_buy * 2 
            budget -= copies_to_buy * price 

        total_items += budget // min_price 
        return total_items

            
        