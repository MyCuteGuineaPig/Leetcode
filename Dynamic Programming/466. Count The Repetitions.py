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

"""


"acb"
4
"ab"
2
        a   c   b |  a   c   b |  a   c   b |  a   c   b |
        a       b |  a       b |

以s2 length 为base的
map = { {2,{2,1}},  }}
len1 = index1 - dp[i1].first  = 5 - 2 = 3 
len2 = index2 - dp[i1].second = 3 - 1 = 2
change2 = (n1*s1Len-1 - index1)/l1*l2 = (4* 3-1 - 5)/3*2 = 6/3*2 = 4;
changed1 = (n1*s1Len-1 - index1)/l1*l1 = (4*3-1 - 5)/3*3 = 6;
index1 += (n1*s1Len - index1)/l1*l1 = 5 + 6 = 11
index2 += (n1*s1Len - index1)/l1*l2 = 3 + 4 = 7;
index1++, index2++ 

return 8/2/2 = 1;

以s2 index 0 为base
map = { {0,{0,0}},  }}
len1 = index1 - dp[i1].first  = 3 - 0 = 3 
len2 = index2 - dp[i1].second = 2 - 0 = 2
change2 = (n1*s1Len - index1)/l1*l2 = (4*3 - 3)/3*2 = 6;
changed1 = (n1*s1Len - index1)/l1*l1 = (4*3 - 3)/3*3 = 9;
index1 += (n1*s1Len - index1)/l1*l1 = 3 + 9 = 12
index2 += (n1*s1Len - index1)/l1*l2 = 2 + 6 = 8; 

return 8/2/2 = 2;

"""