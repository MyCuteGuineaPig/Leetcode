class Solution:
    def distinctSubseqII(self, S: str) -> int:
        end = [0] * 26
        for c in S:
            end[ord(c) - ord('a')] = sum(end) + 1
        return sum(end) % (10**9 + 7)


class Solution:
    def distinctSubseqII(self, S: str) -> int:
        res, end = 0, collections.Counter()
        for c in S:
            res, end[c] = res * 2 + 1 - end[c], res + 1
        return res % (10**9 + 7)