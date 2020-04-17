class Solution:
    def processQueries(self, queries: List[int], m: int) -> List[int]:
        mp = [i for i in range(1, m+1)]
        res = []
        for i, v in enumerate(queries):
            j = mp.index(v)
            #print(v,j)
            res += j, 
            del mp[j]
            mp.insert(0, v)
        return res


            
 # Binary Indexed Tree Or Fenwick Tree: 
 # position 0 (index) is dummy,  need to start from 1          