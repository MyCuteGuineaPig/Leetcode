"""
761. Special Binary String

Special binary strings are binary strings with the following two properties:

The number of 0's is equal to the number of 1's.
Every prefix of the binary string has at least as many 1's as 0's.
Given a special string S, a move consists of choosing two consecutive, non-empty, special substrings of S, and swapping them. (Two strings are consecutive if the last character of the first string is exactly one index before the first character of the second string.)

At the end of any number of moves, what is the lexicographically largest resulting string possible?

Example 1:
Input: S = "11011000"
Output: "11100100"
Explanation:
The strings "10" [occuring at S[1]] and "1100" [at S[3]] are swapped.
This is the lexicographically largest string possible after some number of swaps.

"""

class Solution:
    def makeLargestSpecial(self, S):
        """
        :type S: str
        :rtype: str
        """
        def generate(s):
            count = 0
            li, beg = [],1
            for i,v in enumerate(s):
                if v == '1': count+=1
                elif v == '0': count-=1
                if count == 0:
                    li.append('1'+generate(s[beg:i])+'0')
                    count = 0
                    beg = i+2
            li.sort(reverse = True)
            return "".join(li)
        return generate(S)


class Solution:
    def makeLargestSpecial(self, S):
        count = i = 0
        res = []
        for j, v in enumerate(S):
            count = count + 1 if v=='1' else count - 1
            if count == 0:
                res.append('1' + self.makeLargestSpecial(S[i + 1:j]) + '0')
                i = j + 1
        return ''.join(sorted(res)[::-1])