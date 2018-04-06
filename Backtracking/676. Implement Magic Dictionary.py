
"""
676. Implement Magic Dictionary
"""

import collections
class MagicDictionary:

    def __init__(self):
        """
        Initialize your data structure here.
        """
    def _genneighbours(self):
        for word in self.dict:
            for i in range(len(word)):
                yield word[:i]+"*"+word[i+1:]

    def buildDict(self, dict):
        """
        Build a dictionary through a list of words
        :type dict: List[str]
        :rtype: void
        """
        self.dict = set(dict)
        self.map = collections.Counter(x for x in self._genneighbours())
        

    def search(self, word):
        """
        Returns if there is any word in the trie that equals to the given word after modifying exactly one character
        :type word: str
        :rtype: bool
        """
        return any(self.map[word[:i]+"*"+word[i+1:]] > 1 or 
                  self.map[word[:i]+"*"+word[i+1:]] == 1 and word not in self.dict 
                  for i in range(len(word)) )

        


# Your MagicDictionary object will be instantiated and called as such:
# obj = MagicDictionary()
# obj.buildDict(dict)
# param_2 = obj.search(word)
        


# Your MagicDictionary object will be instantiated and called as such:
# obj = MagicDictionary()
# obj.buildDict(dict)
# param_2 = obj.search(word)