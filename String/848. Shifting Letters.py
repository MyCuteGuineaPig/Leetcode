"""

848. Shifting Letters


Example 1:

Input: S = "abc", shifts = [3,5,9]
Output: "rpl"
Explanation: 
We start with "abc".
After shifting the first 1 letters of S by 3, we have "dbc".
After shifting the first 2 letters of S by 5, we have "igc".
After shifting the first 3 letters of S by 9, we have "rpl", the answer.

"""

import itertools
class Solution:
    def shiftingLetters(self, S, shifts):
        """
        :type S: str
        :type shifts: List[int]
        :rtype: str
        """
        sh = itertools.accumulate(reversed(shifts))
        sh = [*map(lambda x: x%26, sh)][::-1]
        res = ""
        for i, v in enumerate(sh):
            print(v)
            res += chr(ord('a')+(ord(S[i])-ord('a')+v)%26) #python reminder>=0
        return res

class Solution:
    def shiftingLetters(self, S, shifts):
        for i in range(len(shifts) - 1)[::-1]: shifts[i] += shifts[i + 1]
        return "".join(chr((ord(c) - 97 + s) % 26 + 97) for c, s in zip(S, shifts))

class Solution:
    def shiftingLetters(self, S, shifts):
        shifted_letters = [None for _ in S]
        current_sum = 0
        for i in range(len(shifts)-1, -1, -1):
            current_sum += shifts[i]
            shifted_letters[i] = Solution.shift_char(S[i], current_sum)
        return ''.join(shifted_letters)

    @staticmethod
    def shift_char(char, distance):
        distance %= 26
        new_ord = ord(char) + distance
        if new_ord > ord('z'):
            new_ord -= 26
        return chr(new_ord)

