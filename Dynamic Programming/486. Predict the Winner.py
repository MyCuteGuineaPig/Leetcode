
class Solution:
    def PredictTheWinner(self, nums: List[int]) -> bool:
        def find(i, j, turn, cur, prev):
            if i == j:
                return prev + nums[j] >= cur:


            if i == j - 1:
                return  nums[i] + prev >= cur + nums[j] or nums[j] + prev >= cur + nums[i]:
            
            if not find(i+1, j, turn^1, prev+nums[i],cur) or not find(i, j-1, turn^1, prev+nums[j],cur):
                return True
            return False
        
        
        return find(0, len(nums)-1, 1, 0, 0)



class Solution:
    def PredictTheWinner(self, nums):
        n = len(nums)
        memo = [[-1 for x in range(n)] for y in range(n)]      
        scoreFirst = self.PredictTheWinnerInSituation(nums, 0, n - 1, memo)
        scoreTotal = sum(nums)
        return scoreFirst >= scoreTotal - scoreFirst
    
    def PredictTheWinnerInSituation(self, nums, i, j, memo):
        # Base case.
        if i > j:
            return 0
        if i == j:
            return nums[i]
        if memo[i][j] != -1:
            return memo[i][j]
        # Recursive case.
        curScore = max(nums[i] + min(self.PredictTheWinnerInSituation(nums, i+2, j, memo), self.PredictTheWinnerInSituation(nums, i+1, j-1, memo)), 
                       nums[j] + min(self.PredictTheWinnerInSituation(nums, i, j-2, memo), self.PredictTheWinnerInSituation(nums, i+1, j-1, memo)))
        memo[i][j] = curScore        
        return curScore


class Solution:
    def PredictTheWinner(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        memo = {}
    
        def helper(_sum, nums, start, end):
            
            if (start, end) in memo:
                return memo[(start, end)]
            
            if start == end:
                memo[(start, end)] = nums[start]
                return nums[start]
            
            score1 = _sum - helper(_sum - nums[start], nums, start+1, end) 
            score2 = _sum - helper(_sum - nums[end], nums, start, end-1)
            
            res = max(score1, score2)
            memo[(start, end)] = res
            
            return res
        
        return helper(sum(nums), nums, 0, len(nums)-1) * 2 >= sum(nums)


#Bottom-up
class Solution:
    def PredictTheWinner(self, nums: List[int]) -> bool:
        n = len(nums)
        dp = [[0 for _ in range(n)] for _ in range(n)]
        for i, v in enumerate(nums):
            dp[i][i] = v
        
        for lens in range(1, n):
            for i in range(n-lens):
                j = i + lens
                dp[i][j] = max(nums[i] - dp[i+1][j], nums[j] - dp[i][j-1])
        return dp[0][n-1] >= 0


#Top-Down
class Solution(object):
    def PredictTheWinner(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        dp = {}

        def find(i, j):
            if (i, j) not in dp:
                if i == j:
                    return nums[i]
                dp[i,j] = max(nums[i]-find(i+1, j), nums[j]-find(i, j-1))
            return dp[i,j]

        return find(0, len(nums)-1) >= 0