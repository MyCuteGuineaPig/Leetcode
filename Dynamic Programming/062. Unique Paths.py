"""
62. Unique Paths
"""

import math
class Solution:
    def uniquePaths(self, m, n):
        return round(math.factorial(m+n-2)/math.factorial(n-1)/math.factorial(m-1))
        
"""
  
Number of ways of arranging (m-1) down arrows, and (n-1) right arrows is combinations(m-1 + n-1, m-1)
This is a combinatorial problem and can be solved without DP. 
For mxn grid, robot has to move exactly m-1 steps down and n-1 steps right and these can be done in any order.

For the eg., given in question, 3x7 matrix, robot needs to take 2+6 = 8 steps with 2 down and 6 right in any order. 
That is nothing but a permutation problem. Denote down as 'D' and right as 'R', following is one of the path :-

D R R R D R R R


We have to tell the total number of permutations of the above given word. 
So, decrease both m & n by 1 and apply following formula:-

Total permutations = (m+n)! / (m! * n!)

比如 m = 7 n = 3, 总共向左需要走6步，向下2步，是 C 8,2 = 8 * 7 / 2

DRDDDDDR
  
 
  
"""
