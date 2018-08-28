"""
208. Implement Trie (Prefix Tree)

Trie trie = new Trie();

trie.insert("apple");
trie.search("apple");   // returns true
trie.search("app");     // returns false
trie.startsWith("app"); // returns true
trie.insert("app");   
trie.search("app");     // returns true

"""
import collections
class TrieNode:
    def __init__(self):
        self.child = collections.defaultdict(lambda: TrieNode)
        self.isWord = False

class Trie:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.root = TrieNode()
        

    def insert(self, word):
        """
        Inserts a word into the trie.
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
        Returns if the word is in the trie.
        :type word: str
        :rtype: bool
        """
        t = self.root
        for w in word:
            if w not in t.child:
                return False
            t = t.child[w]
        return t.isWord  
        

    def startsWith(self, prefix):
        """
        Returns if there is any word in the trie that starts with the given prefix.
        :type prefix: str
        :rtype: bool
        """
        t = self.root
        for w in prefix:
            if w not in t.child:
                return False
            t = t.child[w]
        return True


# Your Trie object will be instantiated and called as such:
# obj = Trie()
# obj.insert(word)
# param_2 = obj.search(word)
# param_3 = obj.startsWith(prefix)



import collections
class Trie:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        Tree = lambda : collections.defaultdict(Tree)
        self.trie = Tree()


    def insert(self, word):
        """
        Inserts a word into the trie.
        :type word: str
        :rtype: void
        """
        t = self.trie
        for c in word:
            t = t[c]
        t['END'] = True


    def search(self, word):
        """
        Returns if the word is in the trie.
        :type word: str
        :rtype: bool
        """
        t = self.trie
        for c in word:
            if c in t:
                t = t[c]
            else:
                return False
        return 'END' in t


    def startsWith(self, prefix):
        """
        Returns if there is any word in the trie that starts with the given prefix.
        :type prefix: str
        :rtype: bool
        """
        t = self.trie
        for c in prefix:
            if c in t:
                t = t[c]
            else:
                return False
        return True