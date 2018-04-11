"""
115. Distinct Subsequences

"""
class Solution:
    def numDistinct(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: int
        """ 
        if len(t)>len(s) : return 0
        table = [[1 for _ in range(len(s)+1)],[0 for _ in range(len(s)+1)]]
        for i in range(len(t)):
            k = (i+1)%2
            table[k][0] = 0
            for j in range(len(s)):
                table[k][j+1] = table[k][j] + (table[k^1][j] if j>=i and s[j] == t[i] else 0)
        return table[len(t)%2][-1]    


    a a b b
a   1 2 2 2
a   0 1 1 1
b   0 0 1 2

















"""
Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.
    
      r a b b b i t
      1 1 1 1 1 1 1
   r  1 1 1 1 1 1 1
   a  0 1 1 1 1 1 1
   b  0 0 1 2 3 3 3
   b  0 0 0 1 3 3 3
   i 
   t


"""