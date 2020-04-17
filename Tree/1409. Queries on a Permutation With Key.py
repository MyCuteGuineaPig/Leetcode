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
 
 class Fenwick:
    def __init__(self,n):
        self.n = 2*n + 1
        self.data = [0,]*self.n
    
    def update(self, i, x):
        while i < self.n:
            self.data[i] += x
            i += i & -i
    
    def sum(self, i):
        s = 0 
        while i > 0: 
            s += self.data[i]
            i -= i & -i
        return s
            
class Solution:
    def processQueries(self, queries: List[int], m: int) -> List[int]:
        tree = Fenwick(m*2)
        indexMap = {}
        for i in range(1, m+1):
            tree.update(i + m, 1)
            indexMap[i] = i + m
        res =  []
        cur = m 
        for q in queries:
            i = indexMap.pop(q)
            rank = tree.sum(i-1) # 前面有几个数
            res.append(rank)
            
            indexMap[q] = cur 
            
            tree.update(i,-1)
            tree.update(cur,1)
            cur -=1
        return res          

"""
 
BIT TREE: 
  
  1
  |
  v
  2         
  |   3
  v  /    5
  4     /  
  |   6
  v  / 
  8  <- 7
比如一个tree 有8个节点，更新时候
更新1 ->2 ->4 ->8
更新2 ->4 -> 8
更新3(11) -> 4(11+1 = 100)->8
更新4 (100) ->8(100+100 = 1000)
更新5 -> 6 -> 8
更新6(110) ->8 (110 + 10 = 1000)
更新7->8
如果左面连续都是1，直接上最左面bit的下一位 比如110 -> 1000, 1110 -> 10000, 1100 -> 10000
原因: 左侧的1已经存了需要的sum，比如110， 100 存了前4，所以110-> 1000 保证8拥有(5,6的和)，
     比如111->1000， 因为110存了（5，6的和), 100(存了1-4的和），也因为8已经存了5和6的和，so 111 只存第7个
求sum 
求1:  1
求2:  2
求3:  3 + 2 (11, 10)
求4:  4
求5:  5 + 4 (101, 100)
求6:  6 + 4 (110, 100)
求7:  7 + 6 + 4 （111， 110， 100）
求8， 8
BIT index n只存最小bit下面的和
比如1110 有的和是1110 + 1101 
比如1100， 有和的是1001 + 1010 + 1011 + 1100
比如100 有的和是1， 10, 100,

 """ 