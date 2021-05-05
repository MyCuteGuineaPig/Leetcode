class Solution:
    def minInterval(self, intervals: List[List[int]], queries: List[int]) -> List[int]:
        mp = collections.defaultdict(int)
        intervals.sort()
        h = []
        i = 0
        for q in sorted([i for i in queries]):
            while i < len(intervals) and intervals[i][0] <= q:
                heapq.heappush(h, [intervals[i][1]-intervals[i][0] + 1, intervals[i][1]])
                i+=1
            
            while h and h[0][1] < q:
                heapq.heappop(h)
            
            mp[q] = -1 if not h else h[0][0]
        
        return [mp[q] for q in queries]



"""
Union Find
Time complexity: O(n log n + (n+q) log q)

Compress jumps along a segment / Painting subarrays offline


ans key is number, value = the minimized size to hold the number
jump is the next element for processing . 
    e.g. jump = [2,2,2,3,4,5], for the first q, has been set with a min size,
             the next process element is the thrid element 


e.g. [[1,4],[2,4],[3,6],[4,4]]
     [2,3,4,5]

Init : 
jump = [0,1,2,3,4], 需要n + 1是因为可能out of bound, search 的数大于最大的q
q = [2,3,4,5]

loop by sorted interval by size 
  1.  a, b = 4, 4 
    update jump to [0,1,3,3,4], 因为q的第二个数(4) 被set 

  2.  a,b = 2, 4
    update jump to [1,3,3,3,4], 第一个q, 第二个q 被set 

  3.  a,b = 1, 4, 不update, search 时候, 把position [0] jump update
    update jump to [3,3,3,3,4], 第一个q, 第二个q 被set 

  4. a, b  = 3, 6 
    update jump to [3,3,3,4,4], 把第四个q set
    

"""
class Solution:
    def minInterval(self, intervals: List[List[int]], queries: List[int]) -> List[int]:
        q = sorted(set(queries))
        lookup = {v: i for i, v in enumerate(q)}
        
        intervals.sort(key = lambda x: x[1] - x[0])
        ans = [-1] * len(q)
        jump = list(range(len(q)+1))
        
        def search(x):
            if jump[x] != x:
                jump[x] = search(jump[x])
            return jump[x]
        
        for l, r in intervals:
            i, j = bisect.bisect_left(q, l), bisect.bisect_right(q, r)
            ind = search(i) #有的已经process的, 通过search 就可以跳过
            while ind < j:
                ans[ind] = r - l + 1
                jump[ind] = ind + 1
                ind = search(ind)
        
        return [ans[lookup[i]] for i in queries]