"""
557. Reverse Words in a String III

Example 1:
Input: "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"
"""

class Solution:
    def reverseWords(self, s):
        """
        :type s: str
        :rtype: str
        """
        li = list(map(lambda x: x[::-1], s.split()))
        return " ".join(li)

class Solution:
    def reverseWords(self, s):
        """
        :type s: str
        :rtype: str
        """
        n=s.split(' ')
        return (' '.join (i[::-1] for i in n))

class Solution:
    def reverseWords(self, s):
        return ' '.join(s.split()[::-1])[::-1]