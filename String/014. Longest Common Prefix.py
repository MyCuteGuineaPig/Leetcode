"""
14. Longest Common Prefix

Example 1:

Input: ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
Note:

All given inputs are in lowercase letters a-z.

"""
#一位一位的比
class Solution:
    def longestCommonPrefix(self, strs):
        """
        :type strs: List[str]
        :rtype: str
        """
        if not strs:return ""
        res = strs[0]
        for i, v in enumerate(res):
            for s in strs[1:]:
                if i >= len(s) or s[i]!= v:
                    return res[0:i]
        return res

#一个一个的比
class Solution:
    def longestCommonPrefix(self, strs):
        """
        :type strs: List[str]
        :rtype: str
        """
        if not strs:return ""
        res = strs[0]
        for s in strs[1:]:
            for i,v in enumerate(res):
                if i>=len(s) or s[i]!= v:
                    res = res[:i]
                    break
        return res


class Solution:
    # @return a string
    def longestCommonPrefix(self, strs):
        if not strs:
            return ""
            
        for i, letter_group in enumerate(zip(*strs)):
            if len(set(letter_group)) > 1:
                return strs[0][:i]
        else:
            return min(strs)