"""
514. Freedom Trail
"""

"""
       g o d d i n g
    
    g  2 3 4 5 5 4 3 
 
    d  2 1 0 0 1 2 3              

    dp[i][j] 代表当ring[j] == key[i] 从i到j的距离
"""

class Solution:
    def findRotateSteps(self, ring, key):
        """
        :type ring: str
        :type key: str
        :rtype: int
        """
        n , m = len(ring), len(key)
        dp = [[100000000 for _ in range(n)] for _ in range(m)]
        for i in range(m-1, -1, -1):
            for j in range(n):
                if ring[j] == key[i]:
                    for k in range(n):
                        if i == m-1: 
                            dp[i][k] = min(dp[i][k], abs(k-j),n-abs(k-j))
                        else: 
                            dp[i][k] = min(dp[i][k], dp[i+1][j] + min(abs(k-j),n-abs(k-j)))
        #print(dp)
        return dp[0][0] + m

"""

       g o d d i n g
    
    g  0           1 
 
    d      2 3      

    i         4    
"""


import collections
class Solution:
    def findRotateSteps(self, ring, key):
        """
        :type ring: str
        :type key: str
        :rtype: int
        """
        n , m = len(ring), len(key)
        dic = collections.defaultdict(list)
        for i,r in enumerate(ring):
            dic[r] += [i]
        start, dp = [0], [10**10 for _ in range(n)]
        dp[0] = 0
        for i in key: 
            newdp =[10**10 for _ in range(n)]
            for j in dic[i]:
                for k in start:
                    newdp[j] =  min(newdp[j],abs(j-k)+dp[k], dp[k]+(n-abs(j-k)))
            start = dic[i]    
            dp = newdp
            #print(dp)
        return m + min(dp)



import collections
class Solution:
    def findRotateSteps(self, ring, key):
        """
        :type ring: str
        :type key: str
        :rtype: int
        """
        n , m = len(ring), len(key)
        dic = collections.defaultdict(list)
        for i,r in enumerate(ring):
            dic[r] += [i]
        start, dp = [0], collections.defaultdict(lambda:10**10)
        dp[0] = 0
        for i in key: 
            newdp = collections.defaultdict(lambda:10**10)
            for j in dic[i]:
                for k in start:
                    newdp[j] =  min(newdp[j],abs(j-k)+dp[k], dp[k]+(n-abs(j-k)))
            start = dic[i]    
            dp = newdp
            #print(dp)
    
        return m + min(v for _, v in dp.items())


import collections
class Solution:
    def findRotateSteps(self, ring, key):
        """
        :type ring: str
        :type key: str
        :rtype: int
        """
        n , m = len(ring), len(key)
        dic = collections.defaultdict(list)
        for i,r in enumerate(ring):
            dic[r] += [i]
            
        dp = [(0,0)]
        for i in key: 
            dp = [(cur_index, min(prev_dis + min(abs(prev_index-cur_index), n- abs(prev_index-cur_index)) for prev_index, prev_dis in dp)) for cur_index in dic[i]]
        return m + min(v for _, v in dp)


