"""
407. Trapping Rain Water II

Given the following 3x6 height map:
[
  [1,4,3,1,3,2],
  [3,2,1,3,2,4],
  [2,3,3,2,3,1]
]

Return 4.
"""
import heapq
class Solution:
    def trapRainWater(self, heightMap):
        """
        :type heightMap: List[List[int]]
        :rtype: int
        """
        if not heightMap or not heightMap[0]: return 0
        n = len(heightMap); m = len(heightMap[0])
        heap = []
        visited = [[0 for _ in range(m)] for _ in range(n)]
        for i in range(n):
            heapq.heappush(heap,[heightMap[i][0], i,0])
            heapq.heappush(heap,[heightMap[i][m-1],i,m-1])
            visited[i][0] = visited[i][m-1] = 1
        for j in range(1,m-1):
            heapq.heappush(heap,[heightMap[0][j],0,j])
            heapq.heappush(heap,[heightMap[n-1][j],n-1,j])
            visited[0][j] = visited[n-1][j] = 1
        vol = 0;
        while heap:
            [h, i, j] = heapq.heappop(heap)
            for x,y in [[0,-1],[-1,0],[1,0],[0,1]]:
                x += i
                y += j
                if x<0 or y<0 or x>=n or y>=m or visited[x][y]: continue
                if h > heightMap[x][y]: vol += h-heightMap[x][y]
                heapq.heappush(heap,[max(h,heightMap[x][y]), x, y])
                visited[x][y] = 1
        return vol    
        




