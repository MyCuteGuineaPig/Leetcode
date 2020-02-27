
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



#2020
class MagicDictionary:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.root = {}

        
    def buildDict(self, dict: List[str]) -> None:
        """
        Build a dictionary through a list of words
        """
        
        for word in dict:  
            node = self.root 
            for i in word: 
                node = node.setdefault(i, {})
            node[None] = True 

    def search(self, word: str) -> bool:
        """
        Returns if there is any word in the trie that equals to the given word after modifying exactly one character
        """
        def dfs(node, s, oneDiff): #always has child for node, 不用check if node is empty, 因为for loop中阻止了没有child的可能性
            if not s:
                   return oneDiff and None in node #if already oneDiff, current node is leaf, return true 
            
            if s[0] not in node and oneDiff:# current position is different, and before has one differnt
                return False
            else: 
                if s[0] in node:
                   if dfs(node[s[0]],s[1:], oneDiff): 
                        return True 
                   elif oneDiff: #above return False, and already have one difference, cannot modify current position, return False 
                        return False 
                for k,nxt in node.items():
                    if nxt != True and k != s[0] and dfs(nxt, s[1:], 1): #nxt == True means current leaf and don't have child
                        return True 
                return False 
        return dfs(self.root, word, 0)

