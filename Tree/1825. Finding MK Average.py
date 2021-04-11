class BITTree:
    def __init__(self, n):
        self.sums = [0,]*(n+1)
        self.n = n
    
    def add(self, index, val):
        while index <= self.n:
            self.sums[index] += val
            index += index & (-index)
        
    def sum(self, index):
        tot = 0
        while index:
            tot += self.sums[index]
            index -=  index & (-index)
        return tot
        
class MKAverage:

    def __init__(self, m: int, k: int):
        self.m = m
        self.k = k
        self.value = BITTree(100001)
        self.index = BITTree(100001)
        self.q = collections.deque()

    def addElement(self, num: int) -> None:
        self.q.append(num)
        if len(self.q) == self.m+1:
            last = self.q.popleft()
            self.value.add(last, -last)
            self.index.add(last, -1)
        self.value.add(num, num)
        self.index.add(num, 1)    
        
    def calculateMKAverage(self) -> int:
        if len(self.q) < self.m:
            return -1
        def getIndex(k):
            l, r = 1, 100000
            while l < r:
                mid = (l+r) // 2
                if self.index.sum(mid) < k:
                    l = mid + 1
                else: 
                    r = mid 
            return l
        #print(self.index.sums[:11])
        lo, hi = getIndex(self.k), getIndex(self.m-self.k)
        #print(lo, hi)
        res = self.value.sum(hi) - self.value.sum(lo)
        res += (self.index.sum(lo) - self.k) * lo #好几个数在 lo index上，可能少算了
        res -= (self.index.sum(hi)- (self.m - self.k))*hi#好几个数在 hi index上，可能少算了
        
        return res // (self.m - self.k*2)
            
            
            
            