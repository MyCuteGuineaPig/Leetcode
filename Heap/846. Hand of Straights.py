"""
846. Hand of Straights

Example 1:

Input: hand = [1,2,3,6,2,3,4,7,8], W = 3
Output: true
Explanation: Alice's hand can be rearranged as [1,2,3],[2,3,4],[6,7,8].
Example 2:

Input: hand = [1,2,3,4,5], W = 4
Output: false
Explanation: Alice's hand can't be rearranged into groups of 4.
"""
import heapq
class Solution:
    def isNStraightHand(self, hand, W):
        """
        :type hand: List[int]
        :type W: int
        :rtype: bool
        """
        n = len(hand)
        if n % W: return False
        count = collections.defaultdict(int)
        heap = []
        for i in hand:
            count[i]+=1
            heapq.heappush(heap,i)
        for i in range(n//W):
            while count[heap[0]] == 0:
                heapq.heappop(heap)
            start = heap[0]
            for i in range(W):
                if count[start+i] == 0:
                    return False
                count[start+i]-=1
        return True



import heapq
class Solution:
    def isNStraightHand(self, hand, W):
        c = collections.Counter(hand)
        start = collections.deque()
        last_checked, opened = -1, 0
        for i in sorted(c):
            if opened > c[i] or opened > 0 and i > last_checked + 1: return False
            start.append(c[i] - opened)
            last_checked, opened = i, c[i]
            if len(start) == W: opened -= start.popleft()
        return opened == 0


