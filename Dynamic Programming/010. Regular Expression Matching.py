"""
10. Regular Expression Matching
"""
class Solution:
    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        t = [[False]*(len(s)+1) for _ in range(len(p)+1)]
        t[0][0] = True
        for i in range(1,len(p)+1):
            for j in range(len(s)+1):
                if p[i-1]!='*':
                    t[i][j] = j>0 and (s[j-1] == p[i-1] or p[i-1] == '.') and t[i-1][j-1]
                else: 
                    t[i][j] = t[i-2][j] or (j>0 and (s[j-1] == p[i-2] or p[i-2] == '.') and  t[i][j-1])
                    #t[i][j] = t[i-2][j]  cover c * , t[2][0] = t[0][0] = 1
        return t[len(p)][len(s)]

"""

      a a b
    1
  c 0 0 0 0   
  * 1 0 0 0 
  a 0 1 1 0
  * 1 0
  b 0


      b a a b  说明 t[i][j-1]
    1 0 0 0 0 
  b 0 1 0 0 0 
  a 0 0 1 0 0
  * 0 1 1 1
  b 0
  
"""
