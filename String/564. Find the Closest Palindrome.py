"""
564. Find the Closest Palindrome

Example 1:
Input: "123"
Output: "121"
"""
class Solution:
    def nearestPalindromic(self, n):
        """
        :type n: str
        :rtype: str
        """
        num = int(n)
        length = len(n)
        st = set([10**length+1, 10**(length-1)-1])
        half1 = int(n[:(length+1)//2])
        for i in [-1,0,1]:
            half = half1 + i
            if length & 1:
                st |= {int(str(half)+str(half)[:-1][::-1])}
            else:
                st |= {int(str(half)+str(half)[::-1])}
        st.discard(num)
        return str(min((abs(v-num),v) for v in st)[1])


class Solution(object):
    def nearestPalindromic(self, n):
        """
        :type n: str
        :rtype: str
        """
        l = len(n)
        candidates = set((str(10**l + 1), str(10**(l - 1) - 1)))
        prefix = int(n[:(l + 1)/2])
        for i in map(str, (prefix-1, prefix, prefix+1)):
            candidates.add(i + [i, i[:-1]][l%2][::-1])
        candidates.discard(n)
        return min(candidates, key=lambda x: (abs(int(x) - int(n)), int(x)))