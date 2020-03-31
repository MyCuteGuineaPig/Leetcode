class Solution:
    def getKth(self, lo: int, hi: int, k: int) -> int:
        li = sorted([i for i in range(lo, hi+1)], key = order_str)
        return li[k-1]

def cmp(x):
    cnt = 0
    while x != 1:
        if x & 1: 
            x = 3*x + 1
        else:
            x = x//2
        cnt += 1
    return cnt

class order_str(int):
    def __lt__(x, y):
        return cmp(x) < cmp(y)

class Solution(object):
    dp = {}

    def getKth(self, lo, hi, k):
        """
        :type lo: int
        :type hi: int
        :type k: int
        :rtype: int
        """
        def power_value(x):
            y, result = x, 0
            while x > 1 and x not in Solution2.dp:
                result += 1
                if x%2:
                    x = 3*x + 1
                else:
                    x //= 2
            Solution2.dp[y] = result + (Solution2.dp[x] if x > 1 else 0)
            return Solution2.dp[y], y
        
        return sorted(range(lo, hi+1), key=power_value)[k-1]