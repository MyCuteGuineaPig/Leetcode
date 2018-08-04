"""
791. Custom Sort String

Example :
Input: 
S = "cba"
T = "abcd"
Output: "cbad"
Explanation: 
"a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and "a". 
Since "d" does not appear in S, it can be at any position in T. "dcba", "cdba", "cbda" are also valid outputs.
"""

"""
custom sort
""" 
class Solution:
    def customSortString(self, S, T):
        """
        :type S: str
        :type T: str
        :rtype: str
        """
        order = dict((v,i) for i, v in enumerate(S))
        T = list(T)
        T.sort(key = lambda x: order[x] if x in order else 27)
        return "".join(T)

class Solution:
    def customSortString(self, S, T):
        order = dict((v,i) for i, v in enumerate(S))
        return "".join(sorted(list(T),key = lambda x: order[x] if x in order else 27))

"""
bucket sort
""" 
class Solution(object):
    def customSortString(self, S, T):
        counter, s = collections.Counter(T), set(S)
        result = [c*counter[c] for c in S]
        result.extend([c*counter for c, counter in counter.iteritems() if c not in s])
        return "".join(result)

class Solution:
    def customSortString(self, S, T):
        l = []
        for i in S:
                l.append(i*T.count(i))
        for i in T:
            if i not in S:
                l.append(i)
        return ''.join(l)

class Solution:
    def customSortString(self, S, T):
        """
        :type S: str
        :type T: str
        :rtype: str
        """
        m = {c: idx for idx, c in enumerate(S)}
        queue = []
        for c in T:
            heapq.heappush(queue, (m.get(c, sys.maxint), c))
        ret = ''
        while queue:
            _, v = heapq.heappop(queue)
            ret += v
        return ret