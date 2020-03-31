
"""
Graph
https://leetcode.com/problems/find-all-good-strings/discuss/555591/JavaC%2B%2B-Memoization-DFS-and-KMP-with-Picture-Clean-code
"""


def getKmpNext(pattern):
    """ get KMP next arrray
    
    next[i] is the biggest k s.t. pattern[:k] == pattern[:i + 1][-k:]
    """
    nextArr = [0] * len(pattern)
    i, j = 1, 0
    while i < len(pattern):
        while j and pattern[j] != pattern[i]:
            j = nextArr[j - 1]
        if pattern[i] == pattern[j]:
            j += 1
        nextArr[i] = j
        i += 1
    return nextArr

class Solution:
    def findGoodStrings(self, n: int, s1: str, s2: str, evil: str) -> int:
        from functools import lru_cache
        
        m = len(evil)
        mod = int(1E9 + 7)
        nextArr = getKmpNext(evil)
        
        @lru_cache(None) #Need it, otherwise TLE
        def cnt(idx, pre1, pre2, preE):
            """
            we try to build target string each char.
            
            the basic idea is that we can get the count of valid string which begin with a special prefix.
            but if we use the prefix as a parameter, the DP space will be too big.
            so we just extract three params from the prefix: if it's prefix of s1 or s2 or evil.
            
            idx(int) is the index char of target to build.
            
            pre1(bool) means if the prefix of current position is a prefix of s1.
                if it is, the char we put here cannot greater than s1[idx].
            
            pre2(bool) means if the prefix of current position is a prefix of s2.
                if it is, the char we put here cannot less than s2[idx].
                
            preE(int) is the max length of commom prefix between current position and evil.
                if it is len(evil), we cannot build any string begin with current prefix.
                we use KMP algorithm to calculate it.
            """
            if preE == m: return 0
            if idx == n: return 1 #返回的是pre2
            
            total = 0
            first = ord(s1[idx]) if pre1 else ord('a')
            last = ord(s2[idx]) if pre2 else ord('z')
            
            for ci in range(first, last + 1):
                c = chr(ci)
                
                _pre1 = pre1 and ci == first
                _pre2 = pre2 and ci == last

                # using KMP to calculate _preE
                _preE = preE
                while _preE and c != evil[_preE]:
                    _preE = nextArr[_preE - 1]
                if c == evil[_preE]:
                    _preE += 1

                total += cnt(idx + 1, _pre1, _pre2, _preE)
                total %= mod
            
            return total
        
        return cnt(0, True, True, 0);



class Solution:
    def findGoodStrings(self, n: int, s1: str, s2: str, evil: str) -> int:
        def KMP(arr):
            k = [0,]*len(arr)
            j = 0
            for i in range(1, len(arr)):
                while j and arr[j] != arr[i]:
                    j = k[j-1]
                if arr[i] == arr[j]:
                    j += 1
                k[i] = j
            return k
        kmp = KMP(evil)
        m = len(evil)
        dp = collections.defaultdict()
        def dfs(ind, pre1, pre2, ind_e):
            if (ind, pre1, pre2, ind_e) in dp:
                return dp[(ind, pre1, pre2, ind_e)]
            if ind_e == m:
                return 0
            if ind == n :
                return 1 
            first = ord(s1[ind]) if pre1 else ord('a')
            last = ord(s2[ind]) if pre2 else ord('z')
            total = 0
            for i in range(first, last+1):
                c  = chr(i)
                nxtPre1 =  pre1 and i == first 
                nxtPre2 =  pre2 and i == last 
                
                nxtE = ind_e
                while nxtE and c != evil[nxtE]:
                    nxtE = kmp[nxtE-1]
                if c == evil[nxtE]:
                    nxtE += 1
                dp[(ind+1, nxtPre1, nxtPre2, nxtE)] = dfs(ind+1, nxtPre1, nxtPre2, nxtE)
                total += dp[(ind+1, nxtPre1, nxtPre2, nxtE)]
                total = total % (10**9 + 7)
            return total
        return dfs(0, True, True, 0)



#DP
class Solution(object):
    def findGoodStrings(self, n, s1, s2, evil):
        """
        :type n: int
        :type s1: str
        :type s2: str
        :type evil: str
        :rtype: int
        """
        MOD = 10**9+7
        def getPrefix(pattern):
            prefix = [0]*len(pattern)
            j = 0
            for i in range(1, len(pattern)):
                while j  and pattern[j] != pattern[i]:
                    j = prefix[j-1]
                if pattern[j] == pattern[i]:
                    j += 1
                prefix[i] = j
            return prefix
    
        prefix = getPrefix(evil)
        dp = [[[[0]*len(evil) for _ in range(2)] for _ in range(2)] for _ in range(2)] 
        dp[0][0][0][0] = 1 #第一层是n, 第二层s1是不是boundary,, 第三层是 s2是不是bounary, 第三层是 evil 的长度的
        for i in range(n):
            dp[(i+1)%2] = [[[0]*len(evil) for _ in range(2)] for _ in range(2)] #(i+1)%2 这次长度 取决于上次的长度
            for j in range(2):
                for k in range(2):
                    min_c = 'a' if j else s1[i]
                    max_c = 'z' if k else s2[i]
                    for l in range(len(evil)):
                        if not dp[i%2][j][k][l]: #比如 dp[0][1][0][0] = 0, 刚开始时候不用 boundary point ,所以就跳过
                            continue
                        for c in range(ord(min_c)-ord('a'), ord(max_c)-ord('a')+1):
                            c = chr(c+ord('a'))
                            m = l
                            while m  and evil[m] != c:
                                m = prefix[m-1]
                            if evil[m] == c:
                                m += 1
                            if m == len(evil):
                                continue
                            dp[(i+1)%2][j or (s1[i] != c)][k or (s2[i] != c)][m] = \
                                (dp[(i+1)%2][j or (s1[i] != c)][k or (s2[i] != c)][m] + dp[i%2][j][k][l]) % MOD
       
        result = 0
        for j in range(2):
            for k in range(2):
                for l in range(len(evil)):
                    result = (result + dp[n%2][j][k][l]) % MOD
        return result