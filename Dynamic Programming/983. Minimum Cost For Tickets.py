#Method 1. Track calendar days
class Solution:
    def mincostTickets(self, days: List[int], costs: List[int]) -> int:
        dp=[0 for i in range(days[-1]+1)]
        for i in range(days[-1]+1):
             if i not in days:
                dp[i]=dp[i-1]
             else:
                dp[i]=min(dp[max(0,i-7)]+costs[1],dp[max(0,i-1)]+costs[0],dp[max(0,i-30)]+costs[2])
        return dp[-1]

# Method 2: Track Travel Days
class Solution:
    def mincostTickets(self, days: List[int], costs: List[int]) -> int:
        cost = 0
        last7 = deque()
        last30 = deque()
        for day in days:
            while last7 and last7[0][0] + 7 <= day:
                last7.popleft()
            while last30 and last30[0][0] + 30 <= day:
                last30.popleft()
            last7.append((day, cost + costs[1]))
            last30.append((day, cost + costs[2]))
            cost = min(cost + costs[0],
                      last7[0][1],
                      last30[0][1])
        return cost