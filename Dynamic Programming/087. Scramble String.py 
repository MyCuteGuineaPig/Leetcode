"""
DP: 详细解释见C++ version
"""

class Solution:
    def isScramble(self, s1: str, s2: str) -> bool:
        if len(s1) != len(s2):
           return False
        n = len(s1)
        F = [[[False for _ in range(n+1)] for _ in range(n) ] for _ in range(n)]
        for k in range(1, n+1):
            for i in range(0, n-k+1):
                for j in range(0, n-k+1):
                    if k == 1:
                        F[i][j][k] = s1[i] == s2[j]
                    else:
                        for q in range(1, k):
                            if F[i][j][k]:
                                break
                            F[i][j][k] = F[i][j][q] and F[i+q][j+q][k-q] or F[i][j+k-q][q] and F[i+q][j][k-q]
        return F[0][0][n]