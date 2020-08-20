"""
455. Assign Cookies

Input: [1,2,3], [1,1]

Output: 1

Explanation: You have 3 children and 2 cookies. The greed factors of 3 children are 1, 2, 3. 
And even though you have 2 cookies, since their size is both 1, you could only make the child whose greed factor is 1 content.
You need to output 1.
Example 2:
Input: [1,2], [1,2,3]

Output: 2

Explanation: You have 2 children and 3 cookies. The greed factors of 2 children are 1, 2. 
You have 3 cookies and their sizes are big enough to gratify all of the children, 
You need to output 2.

"""

class Solution:
    def findContentChildren(self, g, s):
        """
        :type g: List[int]
        :type s: List[int]
        :rtype: int
        """
        g.sort(); s.sort()
        i = j = 0
        cookie = 0
        while i<len(g) and j < len(s):
            if s[j] >= g[i]: 
                cookie += 1 
                i+=1; j+=1 
            else: 
                j += 1
        return cookie

class Solution:
    def findContentChildren(self, g, s):
        """
        :type g: List[int]
        :type s: List[int]
        :rtype: int
        """
        g.sort(); s.sort()
        i = j = 0
        cookie = 0
        while i<len(g) and j < len(s):
            if s[j] >= g[i]: 
                i+=1
            j += 1
        return i


class Solution:
    def findContentChildren(self, g, s):
        """
        :type g: List[int]
        :type s: List[int]
        :rtype: int
        """
        if len(s) == 0:return 0
        g.sort()
        s.sort()
        gg = iter(g)
        ss = iter(s)
        count = 0
        i = next(ss)
        j = next(gg)
        try:
            while True:
                if i >= j:
                    count += 1
                    j = next(gg)
                i = next(ss)
        except StopIteration:
            return count