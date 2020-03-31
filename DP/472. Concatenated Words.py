"""
472. Concatenated Words
"""
class Solution:
    def findAllConcatenatedWordsInADict(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        self.dic, self.memo, res = set(words), set(), []
        for i in words:
            if self.dfs(0,0,i):
                res.append(i)
        return res
    
    def dfs(self, beg, count, s):
        if beg == len(s) and count>1:
            return True
        for i in range(beg,len(s)):
            if s[beg:] in self.memo:
                return True
            
            if s[beg:i+1] in self.dic and self.dfs(i+1,count+1,s): 
                if i != len(s)-1:
                    self.memo |=  {s[beg:]}
                return True
        return False

"""
没有memoization 慢一点
"""

class Solution:
    def findAllConcatenatedWordsInADict(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        self.dic, res = set(words), []
        for i in words:
            if self.dfs(0,0,i):
                res.append(i)
        return res
    
    def dfs(self, beg, count, s):
        if beg == len(s) and count>1:
            return True
        for i in range(beg,len(s)):
            if s[beg:i+1] in self.dic and self.dfs(i+1,count+1,s): 
                return True
        return False

"""
最快的，从尾部向前，如果尾部不在，肯定不在，省去了先看前面，再查后面的时间
"""

class Solution:
    def findAllConcatenatedWordsInADict(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        res = []
        words_dict = set(words)
        for word in words:
            words_dict.remove(word)
            if self.check(word, words_dict) is True:
                res.append(word)
            words_dict.add(word)
        return res
    
    def check(self, word, d):
        if word in d:
            return True
        
        for i in range(len(word),0, -1):
            if word[:i] in d and self.check(word[i:], d):
                return True
        return False


