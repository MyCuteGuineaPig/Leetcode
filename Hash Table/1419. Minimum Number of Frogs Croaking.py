class Solution:
    def minNumberOfFrogs(self, croakOfFrogs: str) -> int:
        res = 0
        rank = {'c':0,'r':1,'o':2,'a':3, 'k':4}
        croakOfFrogs = list(croakOfFrogs)
        d = collections.defaultdict(int)
        d[-1] = 0
        d[0] = d[1] = d[2] = d[3] = d[4] = -1
        for c in croakOfFrogs:
            if d[rank[c]-1] >= 0:
                d[rank[c]] += 1
                res = max( d[rank[c]]+1, res)
                if rank[c] == 4:
                   for i in range(5):
                        d[i] -= 1
            else:
                return -1  
        return d[0] == d[1] == d[2] == d[3] == d[4] == -1 and res or -1 


class Solution(object):
    def minNumberOfFrogs(self, croakOfFrogs):
        """
        :type croakOfFrogs: str
        :rtype: int
        """
        S = "croak"
        lookup = [0]*len(S)
        result = 0
        for c in croakOfFrogs:
            i = S.find(c)
            lookup[i] += 1
            if lookup[i-1]:
                lookup[i-1] -= 1 #croakcroak, 第二个c把之前的k减去了
            elif i == 0:
                result += 1
            else:
                return -1
        return result if result == lookup[-1] else -1

class Solution:
    def minNumberOfFrogs(self, croakOfFrogs):
        watermark = c = r = o = a = k = 0
        for ch in croakOfFrogs:
            if ch == 'c': 
                c += 1
                watermark = max(watermark, c - k)
            elif ch == 'r': r += 1
            elif ch == 'o': o += 1
            elif ch == 'a': a += 1
            else: k += 1
            if not c >= r >= o >= a >= k:
                return -1
        return watermark if c == k else -1

class Solution:
    def minNumberOfFrogs(self, croakOfFrogs: str) -> int:
        d={'c':0, 'r':0, 'o':0, 'a':0, 'k':0}
        ans=0
        for e in croakOfFrogs:
            d[e]+=1

            if not (d['c']>=d['r']>=d['o']>=d['a']>=d['k']): #需保证是递减的才可以
                return -1

            MM=max(d['c'],d['r'],d['o'],d['a'],d['k'])
            mm=min(d['c'],d['r'],d['o'],d['a'],d['k'])
            diff=MM-mm
            ans=max(ans,diff)

        if not (d['c']==d['r']==d['o']==d['a']==d['k']):
            return -1

        return ans