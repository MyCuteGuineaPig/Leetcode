"""
459. Repeated Substring Pattern


Example 1:
Input: "abab"

Output: True

Explanation: It's the substring "ab" twice.
Example 2:
Input: "aba"

Output: False
Example 3:
Input: "abcabcabcabc"

Output: True

Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)

"""

class Solution:
    def repeatedSubstringPattern(self, s):
        """
        :type s: str
        :rtype: bool
        """
        prefix = [0]*len(s)
        j = 0
        for i in range(1, len(s)):
            while j>0 and s[i]!=s[j]:
                j = prefix[j-1]
            if s[i] == s[j]: j+=1
            prefix[i] = j
        return prefix[-1]> 0 and len(s) % (len(s) - prefix[-1])  == 0


class Solution:
    def repeatedSubstringPattern(self, s):
        if not s:
            return False

        ss = (s + s)[1:-1]
        return ss.find(s) != -1

class Solution:
    def repeatedSubstringPattern(self, str):
        return str in (2 * str)[1:-1]