"""
466. Count The Repetitions
"""

#以0位base
class Solution:
    def getMaxRepetitions(self, s1, n1, s2, n2):
        """
        :type s1: str
        :type n1: int
        :type s2: str
        :type n2: int
        :rtype: int
        """
        index1, index2, s1Len, s2Len, dp = 0, 0, len(s1), len(s2), collections.defaultdict(list)
        while index1<s1Len*n1 : 
            i, j  = index1%s1Len, index2%s2Len
            if s1[i] == s2[j] :
                if j == 0:
                    if i not in dp:
                        dp[i] = [index1, index2]
                    else:
                        repeatLen1, repeatLen2 = index1 - dp[i][0], index2 - dp[i][1]
                        len2 = int((n1*s1Len-1 - index1)/repeatLen1)*repeatLen2
                        len1 =  int((n1*s1Len-1 - index1)/repeatLen1)*repeatLen1
                        index1 += len1
                        index2 += len2
                if index1<s1Len*n1:
                    index2 += 1
            index1+=1
        return int(index2 / s2Len / n2)



#以s2Len 为base
class Solution:
    def getMaxRepetitions(self, s1, n1, s2, n2):
        """
        :type s1: str
        :type n1: int
        :type s2: str
        :type n2: int
        :rtype: int
        """
        index1, index2, s1Len, s2Len, dp = 0, 0, len(s1), len(s2), collections.defaultdict(list)
        while index1<s1Len*n1 : 
            i, j  = index1%s1Len, index2%s2Len
            if s1[i] == s2[j] :
                if j == s2Len-1:
                    if i not in dp:
                        dp[i] = [index1, index2]
                    else:
                        repeatLen1, repeatLen2 = index1 - dp[i][0], index2 - dp[i][1]
                        len2 = int((n1*s1Len-1 - index1)/repeatLen1)*repeatLen2  #减去1 是因为, 最后一位减去现在index1，是最后一位距离现在index的距离
                        len1 =  int((n1*s1Len-1 - index1)/repeatLen1)*repeatLen1
                        index1 += len1
                        index2 += len2
                if index1<s1Len*n1:
                    index2 += 1
            index1+=1
        return int(index2 / s2Len / n2)
