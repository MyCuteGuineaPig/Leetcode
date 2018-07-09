"""
822. Card Flipping Game


Example:

Input: fronts = [1,2,4,4,7], backs = [1,3,4,1,3]
Output: 2
Explanation: If we flip the second card, the fronts are [1,3,4,4,7] and the backs are [1,2,4,1,3].
We choose the second card, which has number 2 on the back, and it isn't on the front of any card, so 2 is good.
"""

class Solution:
    def flipgame(self, fronts, backs):
        """
        :type fronts: List[int]
        :type backs: List[int]
        :rtype: int
        """
        st = set()
        for i in range(len(fronts)):
            if fronts[i] == backs[i]:
                st.add(fronts[i])
        res = float('inf')
        for i in range(len(fronts)):
            if fronts[i] not in st and fronts[i] < res:
                res = fronts[i]
            if backs[i] not in st and backs[i] < res:
                res = backs[i]
        return 0 if res == float('inf') else res


class Solution:
    def flipgame(self, f, b):
        same = {x for x, y in zip(f, b) if x == y}
        return min([i for i in f + b if i not in same] or [0])

class Solution:
    def flipgame(self, fronts, backs):
        """
        :type fronts: List[int]
        :type backs: List[int]
        :rtype: int
        """
        same = set()
        for i in range(len(fronts)):
            if fronts[i] == backs[i]:
                same.add(fronts[i])
        cards = set(fronts) | set(backs)
        return min(cards - same, default=0)

