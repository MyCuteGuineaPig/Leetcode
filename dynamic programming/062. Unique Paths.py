"""
62. Unique Paths
"""

import math
class Solution:
    def uniquePaths(self, m, n):
        return round(math.factorial(m+n-2)/math.factorial(n-1)/math.factorial(m-1))
        

  1 1 1 1 1 1 1
  1 2 3 4 5 6 7
  1 3 6 10 15 21 28

  (3+7-2)!  = 8*7*6*5*4*3*2
  2! 6!     =  2*1* 6*5*4*3*2*1

  /*
  Number of ways of arranging (m-1) down arrows, and (n-1) right arrows is combinations(m-1 + n-1, m-1)
  */
