"""
793. Preimage Size of Factorial Zeroes Function

"""

class Solution:
    def preimageSizeFZF(self, K):
        """
        :type K: int
        :rtype: int
        """
        def count_zeros(val):
            cnt = 0
            while val:
                val = val//5
                cnt += val
            return cnt
        
        l, r = 0, 5*K
        while l<r:
            mid = (l+r)>>1
            cnt = count_zeros(mid)
            if cnt>=K:
                r = mid
            else: l = mid+1
        return 5 if count_zeros(l)==K else 0



class Solution:
    def preimageSizeFZF(self, K):
        li = [1]
        for _ in range(13):
            li.append(li[-1]*5+1)
        for i in range(12,-1,-1):
            if K/li[i]==5: return 0
            K = K%li[i]
        return 5