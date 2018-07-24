"""
165. Compare Version Numbers


Example 1:

Input: version1 = "0.1", version2 = "1.1"
Output: -1
Example 2:

Input: version1 = "1.0.1", version2 = "1"
Output: 1
Example 3:

Input: version1 = "7.5.2.4", version2 = "7.5.3"
Output: -1

"""

class Solution(object):
    def compareVersion(self, version1, version2):
        """
        :type version1: str
        :type version2: str
        :rtype: int
        """
        i = j = 0
        n, m = len(version1), len(version2)
        while i < n or i<m:
            v1, v2 = 0, 0
            while i < n and version1[i]!='.':
                v1 = v1*10 + ord(version1[i]) - ord('0')
                i+=1
            while j < m and version2[j]!='.':
                v2 = v2*10 + ord(version2[j]) - ord('0')
                j+=1
            if v1 != v2: return 1 if v1 > v2 else -1
            i += 1 
            j += 1
        return 0

#python2
import itertools
class Solution(object):
    def compareVersion3(self, version1, version2):
        splits = (map(int, v.split('.')) for v in (version1, version2))
        return cmp(*zip(*itertools.izip_longest(*splits, fillvalue=0)))