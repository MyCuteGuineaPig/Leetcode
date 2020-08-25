
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