import math

class Solution:
    def leastOpsExpressTarget(self, x, target):
        """
        :type x: int
        :type target: int
        :rtype: int
        """
        cache = dict()
        ret = self.helper(x, target, math.ceil(math.log(target, x)), cache)
        return ret

    def helper(self, x, target, index, cache):
        if index == 0 or target == 1:
            return target * 2 - 1
        if (index, target) in cache:
            return cache[(index, target)]
        power = x**index
        count = target // power
        if target % power == 0:
            return index * count - 1
        low = index * count + \
            self.helper(x, target - power * count, index - 1, cache)
        high = index * (count + 1) + \
            self.helper(x, power * (count + 1) - target, index - 1, cache)
        cache[(index, target)] = min(low, high)
        return cache[(index, target)]



class Solution:
    def leastOpsExpressTarget(self, x: int, target: int) -> int:
        pos = neg = k = 0
        while y:
            y, cur = divmod(y, x)
            if k:
                pos, neg = min(cur * k + pos, (cur + 1) * k + neg), min((x - cur) * k + pos, (x - cur - 1) * k + neg)
            else:
                pos, neg = cur * 2, (x - cur) * 2
            k += 1
        return min(pos, k + neg) - 1




"""
The number of operators is the number of xs minus one. So the question asks about how many x are used.

If we use the x-sum of x*x, then it should be x*x*x instead, because,
 for example, when x=3, x*x+x*x+x*x used more x then x*x*x* does. 
 Therefore, we use the term x^k at most x-1 times for any given k.


We start with target and try to decomposite it as the sum of terms x^k. Specially, 
for a given k, we can try add or minus i=0, 1, 2,...,x-1 times of the term x^k. 
The cost, i.e. the extra number of x involved, is equal to i*k.

Reduction rule:
dp[target] = min(dp[target + i * x^k] + i * k, dp[target - i * x^k] + i * k ) for i = 0,1,2,...,x-1

 dp[target] = min(dp[target + i * x^k] + i * k, dp[target - i * x^k] + i * k ) for i = 0,1,2,...,x-1


"""

class Solution:
    def leastOpsExpressTarget(self, x: int, target: int) -> int:
        f = [1]
        cost = [2]
        cnt = 1
        while f[-1] <= target:
            f.append(f[-1] * x)
            cost.append(cnt)
            cnt += 1
        # get the value and cost of x^k, for k = 1,2,....
		# bigger value first to speed up the decomposition
        f = f[::-1]
        cost = cost[::-1]
  
        if target == 0: return 1
        if target == 1: return 1
        
        dp = {0:0}
        def dfs(target, s):
            if target in dp: return dp[target]
            if s == len(f): return float('inf')
            if s > 0 and abs(target) >= f[s - 1]: return float('inf')
            
			# every recursion tries to add/minus all possible number of x^s, 
			# so the next iteration tries x^(s+1).
            tmp = dfs(target, s + 1)
            for i in range(1, x):
                tmp = min(tmp, i * cost[s] + dfs(target + i * f[s], s + 1))
                tmp = min(tmp, i * cost[s] + dfs(target - i * f[s], s + 1))
            dp[target] = tmp
            return tmp
        
        return dfs(target, 0) - 1