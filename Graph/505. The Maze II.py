class Solution:
    def shortestDistance(self, maze, start, destination):
        m, n, q, stopped = len(maze), len(maze[0]), [(0, start[0], start[1])], {(start[0], start[1]):0}
        while q:
            dist, x, y = heapq.heappop(q)
            if [x, y] == destination:
                return dist
            for i, j in ((-1, 0), (1, 0), (0, -1), (0, 1)):
                newX, newY, d = x, y, 0
                while 0 <= newX + i < m and 0 <= newY + j < n and maze[newX + i][newY + j] != 1:
                    newX += i
                    newY += j
                    d += 1
                if (newX, newY) not in stopped or dist + d < stopped[(newX, newY)]:
                    stopped[(newX, newY)] = dist + d
                    heapq.heappush(q, (dist + d, newX, newY))
        return -1