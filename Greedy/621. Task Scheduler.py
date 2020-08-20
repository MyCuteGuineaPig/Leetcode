"""
621. Task Scheduler

Example 1:
Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.

"""

#priority queue
import heapq
class Solution:
    def leastInterval(self, tasks, n):
        """
        :type tasks: List[str]
        :type n: int
        :rtype: int
        """
        dic =  collections.Counter(tasks)
        heap = []
        for i, count in dic.items():
            heapq.heappush(heap,(-count,i))
        res = 0
        chill = collections.deque() #queue
        while heap or chill:
            while chill and res - chill[0][0] > n:
                heapq.heappush(heap, chill.popleft()[1])
            if heap:
                count, t = heapq.heappop(heap)
                if count + 1 !=0:
                    chill.append([res, (count+1, t)])
            res += 1
        return res

class Solution(object):
    def _leastInterval(self, tasks, n):
        n += 1
        ans = 0
        d = collections.Counter(tasks)
        heap = [-c for c in d.values()]
        heapq.heapify(heap)
        while heap:
            stack = []
            cnt = 0
            for _ in range(n):
                if heap:
                    c = heapq.heappop(heap)
                    cnt += 1
                    if c < -1:
                        stack.append(c + 1)
            for item in stack:
                heapq.heappush(heap, item)
            ans += heap and n or cnt # == if heap then n else cnt
        return ans


#Math
class Solution:
    def leastInterval(self, tasks, n):
        """
        longestnum是最长字母长度，比如['a','b','c','a', 'b', 'c'] 最长的字母是2
        nonlongestcnt: 有几个是最长的字母, 比如['a','b','c','a', 'b', 'c'] ， 'a', 'b','c'都是最长的字母
        n+1是区间长度, longestnum-1 有几个这样的区间，longestcnt最后append的个数

        """
        tot = len(tasks)
        cnt =  collections.Counter(tasks)
        longestnum = cnt.most_common(1)[0][1]
        longestcnt = 0
        for i, count in cnt.items():
            if count == longestnum:   
                longestcnt += 1 
        return max(tot, (n+1)*(longestnum-1)+longestcnt)

class Solution:
    def leastInterval(self, tasks, n):
        d = collections.Counter(tasks)
        counts = d.values()
        longest = max(counts)
        ans = (longest - 1) * (n + 1)
        for count in counts:
            ans += count == longest and 1 or 0
        return max(len(tasks), ans)