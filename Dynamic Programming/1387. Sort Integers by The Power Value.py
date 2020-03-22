class Solution:
    def getKth(self, lo: int, hi: int, k: int) -> int:
        li = sorted([i for i in range(lo, hi+1)], key = order_str)
        return li[k-1]

def cmp(x):
    cnt = 0
    while x != 1:
        if x & 1: 
            x = 3*x + 1
        else:
            x = x//2
        cnt += 1
    return cnt

class order_str(int):
    def __lt__(x, y):
        return cmp(x) < cmp(y)