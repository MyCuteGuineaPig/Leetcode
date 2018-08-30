"""
677. Map Sum Pairs

Input: insert("apple", 3), Output: Null
Input: sum("ap"), Output: 3
Input: insert("app", 2), Output: Null
Input: sum("ap"), Output: 5

"""
"""
有可能insert 两次一样的
"""

class TrieNode:
    def __init__(self,):
        self.children = collections.defaultdict(TrieNode)
        self.count = 0
        self.val = 0

class MapSum:
    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.trie = TrieNode()

    def insert(self, key, val):
        """
        :type key: str
        :type val: int
        :rtype: void
        """
        t = self.trie
        replace = True
        for w in key:
            if w not in t.children: 
                replace = False
                break
            t = t.children[w]
            
        if replace and t.val  > 0:
            diff =   val - t.val
            t = self.trie
            for w in key:
                t = t.children[w]
                t.count += diff
            t.val = val
        else:
            t = self.trie
            for w in key:
                if w not in t.children: 
                    t.children[w] = TrieNode()
                t = t.children[w]
                t.count += val
            t.val = val

    def sum(self, prefix):
        """
        :type prefix: str
        :rtype: int
        """
        t = self.trie
        cur = 0
        for w in prefix:
            if w not in t.children: 
                return 0
            t = t.children[w]
            cur = t.count
        return cur


class MapSum(object):

    def __init__(self): 
        self.d = {}

    def insert(self, key, val): 
        self.d[key] = val

    def sum(self, prefix):
        return sum(self.d[i] for i in self.d if i.startswith(prefix))



class TrieNode():
    def __init__(self, count = 0):
        self.count = count
        self.children = {}
                
class MapSum(object):

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.root = TrieNode()
        self.keys = {}

    def insert(self, key, val):
        """
        :type key: str
        :type val: int
        :rtype: void
        """
        # Time: O(k)
        curr = self.root
        delta = val - self.keys.get(key, 0)
        self.keys[key] = val
        
        curr = self.root
        curr.count += delta
        for char in key:
            if char not in curr.children:
                curr.children[char] = TrieNode()
            curr = curr.children[char]
            curr.count += delta
        
    def sum(self, prefix):
        """
        :type prefix: str
        :rtype: int
        """
        # Time: O(k)
        curr = self.root
        for char in prefix:
            if char not in curr.children:
                return 0
            curr = curr.children[char]
        return curr.count