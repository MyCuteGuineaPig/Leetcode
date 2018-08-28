"""
211. Add and Search Word - Data structure design

Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

Example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true

"""

import collections
class TrieNode:
    def __init__(self):
        self.child = collections.defaultdict(lambda: TrieNode)
        self.isWord = False


class WordDictionary:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.root = TrieNode()

    def addWord(self, word):
        """
        Adds a word into the data structure.
        :type word: str
        :rtype: void
        """
        t = self.root
        for w in word:
            if w not in t.child:
                t.child[w] = TrieNode()
            t = t.child[w]
        t.isWord = True
        

    def search(self, word):
        """
        Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter.
        :type word: str
        :rtype: bool
        """
        return self.searchutil(word, self.root)
    
    def searchutil(self, word, t):
        for i, w in enumerate(word):
            if w == ".":
                for child in t.child.values():
                    if self.searchutil(word[i+1:], child): 
                        return True
                return False
            else:
                if w not in t.child:
                    return False
                t = t.child[w]
        return t.isWord  
        


# Your WordDictionary object will be instantiated and called as such:
# obj = WordDictionary()
# obj.addWord(word)
# param_2 = obj.search(word)


class WordDictionary(object):
    def __init__(self):
        self.trie = dict()

    def addWord(self, word):
        cur = self.trie
        for c in word + "$": cur = cur.setdefault(c, {})

    def search(self, word, cur=None):
        if not cur: cur = self.trie
        return "$" in cur if not word \  #结尾$
            else self.search(word[1:], cur[word[0]]) if word[0] in cur \ #搜索不是.
            else False if 'a' <= word[0] <= 'z' \ #字母的没搜到
            else any(self.search(word[1:], cur[c]) for c in cur if c!="$") #搜索. 





class WordDictionary:

    def __init__(self):
        self.root = {}
    
    def addWord(self, word):
        node = self.root
        for char in word:
            node = node.setdefault(char, {})
        node[None] = None

    def search(self, word):
        def find(word, node):
            if not word:
                return None in node
            char, word = word[0], word[1:]
            if char != '.':
                return char in node and find(word, node[char])
            return any(find(word, kid) for kid in node.values() if kid)
        return find(word, self.root)


"""
won't work very well in the case where there are lots of added strings with the same length.

"""

class WordDictionary(object):
    def __init__(self):
        self.word_dict = collections.defaultdict(list)
        

    def addWord(self, word):
        if word:
            self.word_dict[len(word)].append(word)

    def search(self, word):
        if not word:
            return False
        if '.' not in word:
            return word in self.word_dict[len(word)]
        for v in self.word_dict[len(word)]:
            # match xx.xx.x with yyyyyyy
            for i, ch in enumerate(word):
                if ch != v[i] and ch != '.':
                    break
            else:
                return True
        return False


class WordDictionary(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.wordDict = dict()
        

    def addWord(self, word):
        """
        :type word: str
        :rtype: void
        """
        if len(word) in self.wordDict:
            self.wordDict[len(word)].add(word)
        else:
            self.wordDict[len(word)] = set([word]) # 避免重复添加，比如dad 只能添加一次
        
        
    def filter(self, wordPool, index, char = "."):
        if char == ".":
            return wordPool
        
        return [word for word in wordPool if word[index] == char] #比如char = a, index = 1, dad 保留, ppp 去掉不会在return的list中
        
    def search(self, word):
        """
        :type word: str
        :rtype: bool
        """
        if len(word) not in self.wordDict:
            return False
        elif word in self.wordDict[len(word)]:
            return True
        
        
        wordPool = list(self.wordDict[len(word)])
        
        for i, char in enumerate(word):
            if char == '.':
                    continue
            wordPool = self.filter(wordPool, i, char) #筛选，比如[dad, pad], d.d 到d时候只晒出dad; pad在第一个d就去掉了
            if wordPool == []:
                return False
            
        return True