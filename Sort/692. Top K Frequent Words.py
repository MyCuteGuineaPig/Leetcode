"""
692. Top K Frequent Words

Example 1:
Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
    Note that "i" comes before "love" due to a lower alphabetical order.
Example 2:
Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
Output: ["the", "is", "sunny", "day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
    with the number of occurrence being 4, 3, 2 and 1 respectively.
Note:
You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
Input words contain only lowercase letters.
Follow up:
Try to solve it in O(n log k) time and O(n) extra space.

"""

#bucket sort
class Solution:
    def topKFrequent(self, words, k):
        """
        :type words: List[str]
        :type k: int
        :rtype: List[str]
        """
        n = len(words)
        dic = collections.Counter(words)
        bucket = [[] for i in range(n+1)]
        for i, v in dic.items():
            bucket[v].append(i)
        res = []
        for i in range(n,0,-1):
            bucket[i].sort()
            for j in bucket[i]:
                res.append(j)
                k-=1
                if k == 0: return res
        return res

#heap sort
import heapq
class Solution:
    def topKFrequent(self, words, k):
        n = len(words)
        dic = collections.Counter(words)
        heap = []
        for i, v in dic.items():
            heapq.heappush(heap,[v,i])
        return [h[1] for h in sorted(heap, key = lambda x: (-x[0],x[1]))[:k]]



class Solution(object):
    def topKFrequent(self, words, k):
        wordCounts = collections.Counter(words)
        candidates = list(wordCounts.keys())
        candidates.sort(key = lambda word: (-wordCounts[word], word))
        return candidates[:k]
    
class Solution:
    def topKFrequent(self, words, k):
        c = collections.Counter(words)
        return sorted(c.keys(), key = lambda x: (-c[x], x))[:k]    
    
class Solution:
    def topKFrequent(self, words, k):
        wDict=collections.Counter(words)
        res=[]
        maxHeap=[]
        for key,cnt in wDict.items():
            heapq.heappush(maxHeap,(-cnt,key))
        for i in range(k):
            freq,word=heapq.heappop(maxHeap)
            res.append(word)
        return res
        
        
# Time:  O(nlogk)
# Space: O(n)
# Heap Solution
class Solution2(object):
    def topKFrequent(self, words, k):
        """
        :type words: List[str]
        :type k: int
        :rtype: List[str]
        """
        class MinHeapObj(object):
            def __init__(self,val):
                self.val = val
            def __lt__(self,other):
                return self.val[1] > other.val[1] if self.val[0] == other.val[0] else \
                       self.val < other.val
            def __eq__(self,other):
                return self.val == other.val
            def __str__(self):
                return str(self.val)

        counts = collections.Counter(words)
        min_heap = []
        for word, count in counts.iteritems():
            heapq.heappush(min_heap, MinHeapObj((count, word)))
            if len(min_heap) == k+1:
                heapq.heappop(min_heap)
        result = []
        while min_heap:
            result.append(heapq.heappop(min_heap).val[1])
        return result[::-1]


class Solution:
    def topKFrequent(self, words, k):
        """
        :type words: List[str]
        :type k: int
        :rtype: List[str]
        """
        c = collections.Counter(words).most_common()
        
        res = []
        
        while len(res) < k:
            temp = []
            node = c.pop(0)
            temp.append(node[0])
            while c and c[0][1] == node[1]:
                node = c.pop(0)
                temp.append(node[0])
            
            res.extend(sorted(temp))
            # print(res)
        
        return res[:k]


