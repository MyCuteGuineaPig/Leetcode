class Solution:
    def findPermutation(self, nums: List[int]) -> List[int]:
        dp = defaultdict(lambda: defaultdict(int))
        best = defaultdict(lambda: defaultdict(int))
        n = len(nums)
        def dfs(mask, cur):
            if mask.bit_count() == n:
                return abs(cur - nums[0])
            if cur not in dp or mask not in dp[cur]:
                 dp[cur][mask] = float('inf')
                 for nxt in range(1, n):
                    if ((1 << nxt) & mask) == 0:
                        score = abs(cur - nums[nxt]) + dfs(mask | (1<<nxt), nxt)
                        if score < dp[cur][mask]:
                            dp[cur][mask] = score 
                            best[cur][mask] = nxt
            return dp[cur][mask]

        dfs(1, 0)
        res = [0]
        mask = 1 
        while mask.bit_count() < n:
            res.append(best[res[-1]][mask])
            mask |= (1<<res[-1])
        return res