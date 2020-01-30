"""
451. Sort Characters By Frequency

Example 1:

Input:
"tree"

Output:
"eert"

Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
Example 2:

Input:
"cccaaa"

Output:
"cccaaa"

Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.

"""
"""
Bucket Sort
"""
class Solution:
    def frequencySort(self, s):
        """
        :type s: str
        :rtype: str
        """
        n = len(s)
        dic = collections.Counter(s)
        bucket = [[] for i in range(n+1)]
        for key, v in dic.items():
            bucket[v].append(key)
        res = ""
        for i in range(n,0,-1):
            for j in bucket[i]:
                res+= j*i
        return res
    
  
class Solution:
    def frequencySort(self, s: str) -> str:
        count = collections.Counter(s)
        n = len(s)
        buckets = [[] for _ in range(n+1)] 
        for k, v in count.items():
            buckets[v].append(k)
        res = ""
        for c, b in enumerate(buckets):
            res += "".join(i*c for i in b)
        return res[::-1]

"""
Heap Sort
"""
import heapq
class Solution:
    def frequencySort(self, s):
        n = len(s); heap = []
        dic = collections.Counter(s)
        bucket = [[] for i in range(n+1)]
        for key, v in dic.items():
            heapq.heappush(heap,[-v,key])
        res = ""
        while len(heap)>0:
            top = heapq.heappop(heap)
            res +=top[1]*(-top[0])
        return res


from collections import Counter
class Solution:
    def frequencySort(self, s):
        counter = Counter(s)
        return ''.join(k * v for k, v in counter.most_common(len(counter)))


class Solution(object):
    def frequencySort(self, str):
        return "".join([char * times for char, times in collections.Counter(str).most_common()])
        
