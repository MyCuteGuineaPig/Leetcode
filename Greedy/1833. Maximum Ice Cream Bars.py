class Solution:
    def maxIceCream(self, costs: List[int], coins: int) -> int:
        costs.sort()
        for i, a in enumerate(costs):
            coins -= a
            if coins < 0:
                return i
        return len(costs)
                