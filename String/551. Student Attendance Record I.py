"""
551. Student Attendance Record I
"""
class Solution:
    def checkRecord(self, s):
        """
        :type s: str
        :rtype: bool
        """
        A = i = 0
        while i < len(s):
            if s[i] == 'A': A+=1
            if A>=2: return False
            if s[i] == 'L':
                j = i
                while i < len(s) and s[i] == 'L':
                    i+=1
                if i - j > 2: 
                    return False
                i-=1
            i+=1
        return True

class Solution:
    def checkRecord(self, s):
        """
        :type s: str
        :rtype: bool
        """
        if s.find('A') != s.rfind('A'):
            return False
        for i in range(len(s)-2):
            if s[i] == s[i + 1] == s[i+2] == 'L':
                return False
        return True

class Solution:
    def checkRecord(self, s):
        return not re.search('A.*A|LLL',s)