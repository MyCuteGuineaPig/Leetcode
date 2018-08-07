"""
820. Short Encoding of Words

Given a list of words, we may encode it by writing a reference string S and a list of indexes A.

For example, if the list of words is ["time", "me", "bell"], we can write it as S = "time#bell#" and indexes = [0, 2, 5].

Then for each index, we will recover the word by reading from the reference string from that index until we reach a "#" character.

What is the length of the shortest reference string S possible that encodes the given words?

Example:

Input: words = ["time", "me", "bell"]
Output: 10
Explanation: S = "time#bell#" and indexes = [0, 2, 5].
Note:

1 <= words.length <= 2000.
1 <= words[i].length <= 7.
Each word has only lowercase letters.


"""

# Trie Solution
import collections
class Trie:
    def __init__(self):
        self.child = collections.defaultdict(lambda: Trie)
        self.isLeaf = False
    
    def insert(self,words):
        for word in words:
            T = self
            for w in word[::-1]:
                if w not in T.child:
                    T.child[w] = Trie()
                T = T.child[w]
            T.isLeaf = True
    
    def isvalid(self,word):
        T = self
        for w in word[::-1]:
            T = T.child[w]
        if len(T.child) or T.isLeaf is False: return False
        T.isLeaf = False #["time", "time", "time", "time"] 防止这种情况算四回
        return True


class Solution:
    def minimumLengthEncoding(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        trie = Trie()
        trie.insert(words)
        res = 0
        for word in words:
            if trie.isvalid(word):
                res += len(word)+1
        return res
"""
Solution 2: sort
"""

class Solution:
    def minimumLengthEncoding(self, words):
        words = sorted(i[::-1] for i in words)
        print(words)
        res = 0
        for i, word in enumerate(words):
            ok = True
            if i == len(words)-1: 
                ok = False
            else:
                for j, w in enumerate(word):
                    if j == len(words[i+1]) or w!=words[i+1][j]:
                        ok = False
                        break
            if not ok:
                res += len(word)+1
        return res

class Solution:
    def minimumLengthEncoding(self, words):
        mywords = sorted([word[::-1] for word in words])
        res = 0
        for i in range(1,len(mywords)):
            if not mywords[i].startswith(mywords[i-1]):
                res += len(mywords[i-1]) +1
        return res+len(mywords[-1])+1

"""
Solution 3: set
"""

class Solution:
    def minimumLengthEncoding(self, words):
        st = set(i[::-1] for i in words)
        
        for word in words:
            for i in range(1,len(word)): #cannot remove the whole word
                st.discard(word[::-1][:i]) 
        return sum(map(len,st))+len(st)