"""
49. Group Anagrams

Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]

"""


class Solution:
    def groupAnagrams(self, strs):
        """
        :type strs: List[str]
        :rtype: List[List[str]]
        """
        dic = collections.defaultdict(list)
        for i in strs:
            dic["".join(sorted(i))].append(i)
        return list(dic.values())

class Solution:
    def groupAnagrams(self, strs):
        """
        :type strs: List[str]
        :rtype: List[List[str]]
        """
        dic = collections.defaultdict(list)
        for i in strs:
            dic[tuple(sorted(i))].append(i)
        return list(dic.values())