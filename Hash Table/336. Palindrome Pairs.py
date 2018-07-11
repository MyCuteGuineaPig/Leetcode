"""
336. Palindrome Pairs

Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, 
so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

Example 1:
Given words = ["bat", "tab", "cat"]
Return [[0, 1], [1, 0]]
The palindromes are ["battab", "tabbat"]
Example 2:
Given words = ["abcd", "dcba", "lls", "s", "sssll"]
Return [[0, 1], [1, 0], [3, 2], [2, 4]]
The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]
"""

class Solution:
    def palindromePairs(self, words):
        """
        :type words: List[str]
        :rtype: List[List[int]]
        """
        dic = collections.defaultdict(int)
        for i, word in enumerate(words):
            dic[word[::-1]] = i
        res = []
        for i, word in enumerate(words):
            if word == "":
                for j, v in dic.items():
                    if j == j[::-1] and j!="":
                        res.append([v,i])
            for j in range(1,len(word)+1):
                preffix = word[:j]
                suffix = word[j:]
                if preffix in dic and suffix == suffix[::-1] and i != dic[preffix]:
                    res.append([i,dic[preffix]])
                if suffix in dic and preffix == preffix[::-1] and i != dic[suffix] :#suffix 可以是“”
                    res.append([dic[suffix],i])
        return res

#Trie
class Trie:
    def __init__(self):
        self.child = collections.defaultdict(Trie)
        self.leaves = -1
        self.palList = []
    
    def insert(self,word, index):
        T = self
        i = len(word)-1
        while i>=0:
            l = word[:i+1]#对比现在的cur是不是pal，比如abba，因为是i+1, 对比可以是abba,也可以是abb
            if l and l == l[::-1]:
                T.palList.append(index)
            if word[i] not in T.child:
                T.child[word[i]] = Trie()
            T = T.child[word[i]]
            i-=1
        T.leaves = index#每一个是unique的，所以leave只有一个,

    def comp(self, word, index,res):
        T = self
        for i, w in enumerate(word):
            r = word[i:]
            if T.leaves!=-1 and index != T.leaves and r == r[::-1]:#leaves可以是“”的leaves,比如
                res.append([index,T.leaves])
            if w not in T.child: 
                return
            T = T.child[w]
        if T.leaves!=-1:  #比如现在是abcd, t是dcba, append to res, 
            if T.leaves != index:
                res.append([index,T.leaves])
        
        for leave in T.palList:#trie 是reverse的, 比如现在是ab， t是ccba, 但是trie中是abcc
            if leave != index:
                res.append([index, leave])
        


class Solution:
    def palindromePairs(self, words):
        """
        :type words: List[str]
        :rtype: List[List[int]]
        """
        res = []
        trie = Trie()
        for i, w in enumerate(words):
            trie.insert(w,i)
        for i, w in enumerate(words):
            trie.comp(w,i, res)
        return res