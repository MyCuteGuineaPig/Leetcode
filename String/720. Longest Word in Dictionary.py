"""
720. Longest Word in Dictionary

Example 1:
Input: 
words = ["w","wo","wor","worl", "world"]
Output: "world"
Explanation: 
The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
Example 2:
Input: 
words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
Output: "apple"
Explanation: 
Both "apply" and "apple" can be built from other words in the dictionary. However, "apple" is lexicographi

"""

class Solution:
    def longestWord(self, words):
        """
        :type words: List[str]
        :rtype: str
        """
        trie = Trie()
        trie.build(words)
        ans = ""
        for word in words:
            if trie.isAns(word) and (not ans or len(ans)<len(word) or (len(ans) == len(word) and word < ans)):
                ans = word
        return ans
        
import collections
class Trie:
    def __init__(self):
        self.child = collections.defaultdict(lambda: Trie)
        self.isLeaf = False

    def build(self,words):
        for word in words:
            T = self
            for w in word:
                if w not in T.child: 
                    T.child[w] = Trie()
                T = T.child[w]
            T.isLeaf = True
    
    def isAns(self,word):
        T = self
        for w in word:
            T = T.child[w]
            if not T.isLeaf: return False
        return True



class Solution:
    def longestWord(self, words):
        """
        :type words: List[str]
        :rtype: str
        """
        words = set(words)
        
        def isBuilt(w):
            for i in range(1, len(w)):
                if w[:i] not in words:
                    return False
            return True
        
        ans = ''
        for w in words:
            if (len(w) > len(ans) or len(w) == len(ans) and w < ans) and isBuilt(w):
                ans = w
        return ans
        
"""
Firstly sort the words to ensure that we iterate in a lexicographical fashion. 
Also, maintain a set of seen words to check whether there is a "path" to the current word we are iterating through.
We can lengthen the path when we see that there is a previous word that meets the criteria. 
Lastly, in every iteration where there is a path lengthening, check to see if we can update the longest_word.
"""

class Solution(object):
    def longestWord(self, words):
        words.sort()
        words_set, longest_word = set(['']), ''
        for word in words:
            if word[:-1] in words_set:
                words_set.add(word)
                if len(word) > len(longest_word):
                    longest_word = word
        return longest_word


class Solution(object):
    def longestWord(self, words):
        return min((set(itertools.accumulate(w)) - set(words), -len(w), w)  #itertools.accumulate(w) 是把逐一把string 加起来， 变成一个str list，比如"word" 变成 ['w', 'wo', 'wor', 'word']
                for w in words + [''])[2]  #set 做减法是把相同的删去，这样空的set 做min 拍最前面
