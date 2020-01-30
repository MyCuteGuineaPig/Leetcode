"""
347. Top K Frequent Elements
Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note: 
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.


"""
"""
bucket Sort
"""
class Solution:
    def topKFrequent(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        n = len(nums)
        dic = collections.Counter(nums)
        bucket = [[] for i in range(n+1)]
        for key, v in dic.items():
            bucket[v].append(key)
        res = []
        for i in range(n, 0,-1):
            for j in bucket[i]:
                res.append(j)
            if len(res)>=k:break
        return res

   
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        c = collections.Counter(nums)
        bucket = [[] for _ in range(len(nums)+1)]
        for c, v in c.items(): 
            bucket[v].append(c)
        
        res = []
        for i in range(len(nums), -1, -1):
            if bucket[i]:
                res += bucket[i][:k]
                k -= len(bucket[i])
                if k<=0: 
                    return res

    
    
"""
Heap Sort
"""

import heapq
class Solution:
    def topKFrequent(self, nums, k):
        heap = []
        n = len(nums)
        dic = collections.Counter(nums)
        bucket = [[] for i in range(n+1)]
        for key, v in dic.items():
            heapq.heappush(heap,[-v,key])
        res = []
        while len(res)<k:
            res.append(heapq.heappop(heap)[1])
        return res
    
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        mp = collections.Counter(nums)
        n = len(nums)
        pq = []
        for key, v in mp.items():
            heapq.heappush(pq,[v,key])
            if len(pq) == k+1:
                heapq.heappop(pq)
        res = []
        while pq:
            res.append(heapq.heappop(pq)[1])
        return res


import collections 
class Solution:
    def topKFrequent(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        counter = collections.Counter(nums)
        res = sorted(counter.keys(), key=lambda x: counter[x], reverse = True)
        return res[0:k]
        
class Solution:
    def topKFrequent(self, nums, k):
        c = collections.Counter(nums)
        return [v[0]for v in c.most_common(k)]


class Solution:
    def topKFrequent(self, nums, k):
        from collections import Counter
        return sorted([k for k, v in Counter(nums).most_common(k)])
