"""
767. Reorganize String


Example 1:

Input: S = "aab"
Output: "aba"
Example 2:

Input: S = "aaab"
Output: ""

"""
class Solution:
    def reorganizeString(self, S):
        """
        :type S: str
        :rtype: str
        """
        cnt = collections.Counter(S)
        most = cnt.most_common(1)[0][1]
        if most > (len(S)+1)//2:
            return ""
        h = []
        for i, v in cnt.items(): 
            heapq.heappush(h,(-v,i))
        chill = ()
        res = ""
        while h:
            count, w = heapq.heappop(h)
            if chill: 
                heapq.heappush(h,chill)
                chill = ()
            res += w
            if count+1<0: 
                chill = (count+1, w)
        return res 


class Solution:
    def reorganizeString(self, S):
        cnt = collections.Counter(S)
        most = cnt.most_common(1)[0][1]
        if most > (len(S)+1)//2:
            return ""
        h = []
        for i, v in cnt.items(): 
            heapq.heappush(h,(-v,i))
        res = ""
        while h:
            count, w = heapq.heappop(h)
            if not res or res[-1] != w:
                res+=w
                if count + 1 < 0:
                    heapq.heappush(h, (count+1,w))
            else: 
                c2, w2 = heapq.heappop(h)
                res += w2
                if c2 + 1 < 0:
                    heapq.heappush(h, (c2+1,w2))
                heapq.heappush(h,(count,w))    
        return res 
        
"""
Put the least common letters at the odd indexes and
 put the most common letters at the even indexes (both from left to right in order of frequency). 
 The task is only impossible if some letter appears too often, in which case it'll occupy all of the even indexes and at least the last odd index, 
 so I check the last two indexes.

#首先可以证明，当出现的最多的字母次数不超过 len(S)//2 + 1 时，可以得到满足条件的字符串，方法时先将出现次数最多的字母(比如‘a’)排在一起，然后把其它字符插入到aa之间

"""
class Solution:
    def reorganizeString(self, S):
        a = sorted(sorted(S), key=S.count)
        h = len(a) / 2
        a[1::2], a[::2] = a[:h], a[h:]
        return ''.join(a) * (a[-1:] != a[-2:-1])



class Solution:
    def reorganizeString(self, S):
        """
        :type S: str
        :rtype: str
        """
        table = {}
        for ch in S:
            table[ch] = table.get(ch, 0) + 1
        
        max_freq = max(list(table.values()))
        if max_freq * 2 > len(S) + 1:
            return ''
        else:
            res = [''] * max_freq
            idx = 0
            for key, value in sorted(table.items(), key=lambda x: x[1], reverse=True):
                for i in range(value):
                    res[idx] += key #['',''] -> ['a','a'] -> ['ab','a']
                    idx += 1
                    idx %= max_freq
        return ''.join(res)