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



class Solution:
    def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
        S = set(words)
        ans = []
        for word in words:
            if not word: 
                continue
            stack = [0]
            seen = {0}
            M = len(word)
            while stack:
                node = stack.pop()
                if node == M:
                    ans.append(word)
                    break
                for j in xrange(1, M - node + 1): # just start from 1
                    if word[node:node+j] in S and node + j not in seen \
                        and not (node==0 and node+j==M): # that is, the word must be broken but not a complete one
                        stack.append(node + j)
                        seen.add(node + j)
        return ans



class Solution:
    def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
        d = set(words)
        
        def dfs(word):
            for i in range(1, len(word)):
                prefix = word[:i]
                suffix = word[i:]
                
                if prefix in d and suffix in d:
                    return True
                if prefix in d and dfs(suffix):
                    return True
                if suffix in d and dfs(prefix):
                    return True
            
            return False
        
        res = []
        for word in words:
            if dfs(word):
                res.append(word)
        
        return res


#Suffix Trie
class Solution:
    def findAllConcatenatedWordsInADict(self, words: List[str]) -> List[str]:
        class Trie:
            def __init__(self):
                self.child = collections.defaultdict(lambda:Trie)
                self.isleaf = False 
        
        trie = Trie()
        for word in words:
            if not word:
                continue 
            t = trie 
            for w in word:
                if w not in t.child:
                    t.child[w] = Trie()
                t = t.child[w]
            t.isleaf = True 
        
        def find(t, word, index, cnt):
            while index < len(word):
                if word[index] not in t.child: 
                    return False 
                t = t.child[word[index]]
                if t.isleaf and find(trie, word, index+1, cnt+1):
                    return True
                index += 1
            
            return index == len(word) and cnt >= 1 and t.isleaf
        
        
        res = []
        for word in words:
            if find(trie, word, 0, 0):
                res += word,
        return res