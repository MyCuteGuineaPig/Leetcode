
import heapq 
class Solution:
    def scheduleCourse(self, courses):
        """
        :type courses: List[List[int]]
        :rtype: int
        """
        courses.sort(key = lambda x: x[1])
        cur = cnt = 0
        h = [] 
        #print(courses)
        for need, end in courses: 
            if cur + need <= end:
                cur += need 
                cnt += 1
                heapq.heappush(h,-need) 
            elif h and -h[0]>need and cur+h[0]+need <= end: 
                cur += h[0] + need
                heapq.heappop(h)
                heapq.heappush(h,-need)
            #print(cur, cnt, need, h) 
        return cnt 
                         
        
import heapq 
class Solution:
    def scheduleCourse(self, courses):
        """
        :type courses: List[List[int]]
        :rtype: int
        """
        courses.sort(key = lambda x: x[1])
        cur = cnt = 0
        h = [] 
        #print(courses)
        for need, end in courses: 
            cur += need 
            heapq.heappush(h, -need)
            if cur > end:
                cur += heapq.heappop(h)
        return len(h) 
                                 

class Solution:
    def scheduleCourse(self, courses: List[List[int]]) -> int:
        pq = []
        start = 0
        for t, end in sorted(courses, key = (lambda x: x[1])):
            start += t
            heapq.heappush(pq, -t)
            while start > end:
                start += heapq.heappop(pq)
        return len(pq)