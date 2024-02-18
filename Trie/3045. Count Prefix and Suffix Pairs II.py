class Solution:
    def countPrefixSuffixPairs(self, words: List[str]) -> int:
        root = (T :=lambda: defaultdict(T))() #class type, 定义了collections.defaultdict
        root1 = (T :=lambda: defaultdict(T)) #function type
        print(type(root), type(root1))
        res = 0
        for w in words:
            x = root 
            for k in zip(w,reversed(w)):
                res += (x := x[k]).get(0,0)
            #print(root)     
            x[0] = x.get(0,0) + 1 
        return res