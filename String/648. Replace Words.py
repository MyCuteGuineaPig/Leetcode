"""

648. Replace Words

Input: dict = ["cat", "bat", "rat"]
sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"
"""

class Solution:
    def replaceWords(self, dict, sentence):
        """
        :type dict: List[str]
        :type sentence: str
        :rtype: str
        """
        T = Trie()
        T.insert(dict)
        li = sentence.split()
        for i, word in enumerate(li):
            li[i] = T.find(word)
        return " ".join(li)


import collections
class Trie:
    def __init__(self,):
        self.child = collections.defaultdict(lambda: Trie)
        self.isLeaf = False
    
    def insert(self,words):
        for word in words:
            T = self
            for w in word:
                if w not in T.child:
                    T.child[w] = Trie()
                T = T.child[w]
            T.isLeaf = True
    
    def find(self,word):
        T = self
        for i, w in enumerate(word):
            if w not in T.child:
                return word
            T = T.child[w]
            if T.isLeaf: 
                return word[:i+1]
        return word


class Solution:
    def replaceWords(self, roots, sentence):
        _trie = lambda: collections.defaultdict(_trie)
        trie = _trie()
        END = True
        for root in roots:
            cur = trie
            for letter in root:
                cur = cur[letter]
            cur[END] = root

        def replace(word):
            cur = trie
            for letter in word:
                if letter not in cur: break
                cur = cur[letter]
                if END in cur:
                    return cur[END]
            return word

        return " ".join(map(replace, sentence.split()))




import collections


class Solution(object):
    def replaceWords(self, dictionary, sentence):
        """
        :type dictionary: List[str]
        :type sentence: str
        :rtype: str
        """
        _trie = lambda: collections.defaultdict(_trie)
        trie = _trie()
        for word in dictionary:
            reduce(dict.__getitem__, word, trie).setdefault("_end")

        def replace(word):
            curr = trie
            for i, c in enumerate(word):
                if c not in curr:
                    break
                curr = curr[c]
                if "_end" in curr:
                    return word[:i+1]
            return word

        return " ".join(map(replace, sentence.split()))
