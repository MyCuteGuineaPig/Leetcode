class Trie:
    def __init__(self,):
        self.dic =  [ None for i in range(26)]
        self.isLeave = False
        self.word = None
    
    def insert(self, word):
        t = self 
        for w in word: 
            w = ord(w) - ord('a')
            if t.dic[w] is None:
                t.dic[w] = Trie()
            t = t.dic[w]
        t.isLeave = True
        t.word = word

    def search(self, word):
        t = self
        res = []
        for i, w in enumerate(word):
            org = w 
            w = ord(w) - ord('a')
            if t.dic[w]: 
                tmp = []
                self.__find(t.dic[w], tmp)
                res.append(tmp)
                t = t.dic[w]
            else:
                res += [[] for j in range(i, len(word))]

                break
        return res
            
    
    def __find(self, t, res):
        if len(res) == 3:
            return
        if t.isLeave:
            res.append(t.word)
        for i in range(26):
            if t.dic[i]:
                self.__find(t.dic[i], res)
            



class Solution:
    def suggestedProducts(self, products: List[str], searchWord: str) -> List[List[str]]:
        t = Trie()
        for product in products:
            t.insert(product)
        return t.search(searchWord)


class Solution:
    def suggestedProducts(self, A: List[str], searchWord: str) -> List[List[str]]:
        A.sort()
        res, prefix, i = [], '', 0
        for c in searchWord:
            prefix += c
            i = bisect.bisect_left(A, prefix, i)
            res.append([w for w in A[i:i + 3] if w.startswith(prefix)])
        return res
"""
Time O(NlogN) for sorting
Time O(logN) for each query
"""