"""
696. Count Binary Substrings

Example 1:
Input: "00110011"
Output: 6
Explanation: There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".

Notice that some of these substrings repeat and are counted the number of times they occur.

Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.
Example 2:
Input: "10101"
Output: 4
Explanation: There are 4 substrings: "10", "01", "10", "01" that

"""
class Solution:
    def countBinarySubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        i = res = 0
        while i < len(s):
            j = 0
            while i+j < len(s) and i - j - 1>=0 and s[i-1] != s[i] and s[i+j] == s[i] and s[i-1-j] == s[i-1]:
                j+=1
            res += j
            i += j if j> 0 else 1
        return res

class Solution:
    def countBinarySubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        res = prev = 0
        i = cur = 1 
        for i in range(1,len(s)):
            if s[i]!=s[i-1]:
                res += min(prev, cur)
                prev, cur = cur, 1
            else:
                cur += 1
        res += min(prev, cur)
        return res 


class Solution:
    def countBinarySubstrings(self, s):
        s =[*map(len, s.replace('01','0 1').replace('10', '1 0').split())]
        return sum(min(a,b) for a, b in zip(s,s[1:]))

class Solution:
    def countBinarySubstrings(self, s):
        s =[*map(len, re.findall('0+|1+',s))]
        return sum(map(min, s[:-1], s[1:]))