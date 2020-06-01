import collections
class Solution:
    def numberOfArithmeticSlices(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        dic, res = [collections.defaultdict(int) for _ in range(len(A))] , 0
        for i in range(1, len(A)):
            for j in range(0,i):
                res += dic[j][A[i] - A[j]]
                dic[i][A[i] - A[j]] += dic[j][A[i] - A[j]]+1 # 是加上比如[2,2,3,4] 如果不是+， return是1
        return res

"""
上面的解不efficient 
因为很有可能j 中 没有A[i] - A[j], 所以就会创建很多key，然后得到default value是0
与其创造很多key，不如先判断有没有key，
下面比上面的速度快1倍，

"""

import collections
class Solution:
    def numberOfArithmeticSlices(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        dic, res = [collections.defaultdict(int) for _ in range(len(A))] , 0
        for i in range(1, len(A)):
            for j in range(i):
                dic[i][A[i] - A[j]] += 1  
                if A[i] - A[j] in dic[j]:  # efficient
                    res += dic[j][A[i] - A[j]]
                    dic[i][A[i] - A[j]] += dic[j][A[i] - A[j]] # 是加上比如[2,2,3,4] 如果不是+， return是1
        return res




class Solution:
    def numberOfArithmeticSlices(self, A):
        """
        :type A: List[int]
        :rtype: int
        """
        dic={}
        for i in range(len(A)):
            if A[i] in dic:
                dic[A[i]].append(i)
            else:
                dic[A[i]]=[i]
        dp=[{} for _ in range(len(A))]
        for i in range(len(A)):
            for j in range(i):
                t=A[i]-A[j]
                x=A[j]-t
                if x in dic:
                    for k in dic[x]:
                        if k<j:
                            dp[i][t]=dp[i].get(t,0)+1
                if t in dp[j]:
                    dp[i][t]=dp[i].get(t,0)+dp[j][t]
        s=0
        for x in dp:
            for i in x:
                s+=x[i]
        return s