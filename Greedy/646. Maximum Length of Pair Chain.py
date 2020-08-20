"""
646. Maximum Length of Pair Chain

You are given n pairs of numbers. 
In every pair, the first number is always smaller than the second number.

Now, we define a pair (c, d) can follow another pair (a, b) if and only if b < c. Chain of pairs can be formed in this fashion.

Given a set of pairs, find the length longest chain which can be formed. 
You needn't use up all the given pairs. You can select pairs in any order.

Example 1:
Input: [[1,2], [2,3], [3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4]


"""
class Solution:
    def findLongestChain(self, pairs):
        """
        :type pairs: List[List[int]]
        :rtype: int
        """
        cur, res = float('-inf'), 0
        
        for p in sorted(pairs, key=lambda x: x[1]):
            if cur < p[0]:cur, res = p[1], res+1
        return res


class Solution:
    def findLongestChain(self, pairs):
        """
        :type pairs: List[List[int]]
        :rtype: int
        """
        pairs.sort(key = lambda x: x[1])
        cnt = 1
        _ , e = pairs[0]
        for curs, cure in pairs[1:]:
            if curs > e:
                cnt += 1
                e = cure        
        return cnt


class Solution:
    def findLongestChain(self, pairs):
        pairs.sort(key = lambda x: x[1])
        cnt = 1; it = iter(pairs)
        _ , e = next(it)
        for curs, cure in it:
            if curs > e:
                cnt += 1
                e = cure        
        return cnt


class Solution:
    def findLongestChain(self, pairs):
        pairs.sort(key = lambda x: x[0])
        cnt = 1; it = iter(pairs)
        _ , e = next(it)
        for curs, cure in it:
            if curs > e:
                cnt += 1
                e = cure
            else: e = min(e, cure)        
        return cnt

def findLongestChain(self, pairs):
    """
    :type pairs: List[List[int]]
    :rtype: int
    """
    # sort by x for pairs (x1, y1), (x2, y2), (x3, y3)...
    pairs.sort()
        
    # min_end_y[i] is the ending tuple minimum y of length=i chain
    min_end_y = [float('inf')] * len(pairs)
    for x, y in pairs:
        # since (a, b) can chain (c, d) iff b < c, use bisect_left
        i = bisect.bisect_left(min_end_y, x)
        # greedy method, for the same length chain, the smaller y the better
        min_end_y[i] = min(min_end_y[i], y)  
    
    return bisect.bisect_left(min_end_y, float('inf'))