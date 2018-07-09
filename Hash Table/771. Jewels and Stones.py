"""
771. Jewels and Stones

Example 1:

Input: J = "aA", S = "aAAbbbb"
Output: 3
Example 2:

Input: J = "z", S = "ZZ"
Output: 0
"""


class Solution:
    def numJewelsInStones(self, J, S):
        """
        :type J: str
        :type S: str
        :rtype: int
        """
        st = set(J)
        return sum(map(lambda x: x in st, S))

class Solution:
    def numJewelsInStones(self, J, S):
        return sum(map(J.count, S))
class Solution:   
    def numJewelsInStones(self, J, S):
        return sum(map(S.count, J))     