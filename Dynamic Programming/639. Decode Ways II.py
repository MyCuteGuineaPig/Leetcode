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



#比**, dp (1,9), (9,96)
class Solution:
    def numDecodings(self, s: str) -> int:
        one = {'1': 1, '2': 1, '3': 1, '4': 1, '5': 1, '6': 1, '7': 1, '8': 1, '9': 1, '*': 9}
        two = {'10': 1, '11': 1, '12': 1, '13': 1, '14': 1, '15': 1, '16': 1, '17': 1, '18': 1, '19': 1, '20': 1, '21': 1,
       '22': 1, '23': 1, '24': 1, '25': 1, '26': 1, '*0': 2, '*1': 2, '*2': 2, '*3': 2, '*4': 2, '*5': 2, '*6': 2,
       '*7': 1, '*8': 1, '*9': 1, '1*': 9, '2*': 6, '**': 15}     
        dp = 1, one.get(s[:1], 0)  #返回tuple 比如 * => (1, 9)
        for i in range(1, len(s)):
            dp = dp[1], (one.get(s[i], 0) * dp[1] + two.get(s[i-1: i+1], 0) * dp[0]) % 1000000007
        return dp[-1]
