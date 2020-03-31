"""

639. Decode Ways II
"""

class Solution:
    def numDecodings(self, s):
        """
        :type s: str
        :rtype: int
        """
        if len(s) == 0: return 0
        endingAny, ending1, ending2 = 1, 0, 0
        M = 10**9 + 7
        for i in s:
            if i == '*':
                endingAny, ending1, ending2  = (endingAny*9 + ending1*9 + ending2*6)%M, endingAny, endingAny
            else:
                endingAny, ending1, ending2 =  (endingAny*(i!='0') + ending1 + ending2*(i<='6'))%M, (i == '1')*endingAny, (i == '2')*endingAny
            #print(endingAny, ending1, ending2,i)
        return endingAny;