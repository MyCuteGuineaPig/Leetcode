"""
354. Russian Doll Envelopes

You have a number of envelopes with widths and heights given as a pair of integers (w, h).
 One envelope can fit into another if and only if both the width and height of one envelope is greater than the width and height of the other envelope.

What is the maximum number of envelopes can you Russian doll? (put one inside other)

Example:
Given envelopes = [[5,4],[6,4],[6,7],[2,3]], the maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).



"""

class Solution:
    def maxEnvelopes(self, envelopes):
        """
        :type envelopes: List[List[int]]
        :rtype: int
        """
        envelopes.sort(key = lambda k: (-k[0],k[1]), reverse = True)
        tail = []
        for e in envelopes:
            l, r = 0, len(tail)
            while l<r:
                mid = (l+r)>>1
                if e[1]>tail[mid]:
                    l = mid + 1
                else: r = mid
            if l == len(tail):
                tail += [e[1]]
            else: tail[l] = e[1]
        return len(tail)


class Solution:
    def maxEnvelopes(self, envelopes):
        envelopes.sort(key = lambda k: (k[0],-k[1]))
        tail = []
        for e in envelopes:
            l = bisect.bisect_left(tail, e[1])
            if l == len(tail):
                tail += [e[1]]
            else: tail[l] = e[1]
        return len(tail)