"""
529. Minesweeper

"""


class Solution:
    def updateBoard(self, board, click):
        """
        :type board: List[List[str]]
        :type click: List[int]
        :rtype: List[List[str]]
        """
        n, m = len(board), len(board[0])
        def helper(i, j):
            #print(i, j)
            count = 0
            for addx, addy  in ((-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1),(1,0), (1,1)):
                x, y = i + addx, j+addy
                if x <0 or x >= n or y < 0 or  y >= m: continue
                count += 1 if board[x][y] == 'M' else 0
            if count > 0: board[i][j] = str(count)
            else:
                board[i][j] = 'B'
                for addx, addy  in ((-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1),(1,0), (1,1)):
                    x, y = i + addx, j+addy
                    if x <0 or x >= n or y < 0 or  y >= m: continue
                    if board[x][y] == 'E': 
                        helper(x,y)
        if board[click[0]][click[1]] == 'M':
            board[click[0]][click[1]] = 'X'
        else:
            helper(click[0], click[1])
        return board


class Solution:
    def updateBoard(self, board, click):
        (row, col), directions = click, ((-1, 0), (1, 0), (0, 1), (0, -1), (-1, 1), (-1, -1), (1, 1), (1, -1))
        if 0 <= row < len(board) and 0 <= col < len(board[0]):
            if board[row][col] == 'M':
                board[row][col] = 'X'
            elif board[row][col] == 'E':
                n = sum([board[row + r][col + c] == 'M' for r, c in directions if 0 <= row + r < len(board) and 0 <= col + c < len(board[0])])
                board[row][col] = str(n or 'B')
                for r, c in directions * (not n): self.updateBoard(board, [row + r, col + c])
        return board    


class Solution:
    def updateBoard(self, A, click):
        click = tuple(click)
        R, C = len(A), len(A[0])
        
        def neighbors(r, c):
            for dr in range(-1, 2):
                for dc in range(-1, 2):
                    if (dr or dc) and 0 <= r + dr < R and 0 <= c + dc < C:
                        yield r + dr, c + dc
        
        stack = [click]
        seen = {click}
        while stack:
            r, c = stack.pop()
            if A[r][c] == 'M':
                A[r][c] = 'X'
            else:
                mines_adj = sum( A[nr][nc] in 'MX' for nr, nc in neighbors(r, c))
                if mines_adj:
                    A[r][c] = str(mines_adj)
                else:
                    A[r][c] = 'B'
                    for nei in neighbors(r, c):
                        if A[nei[0]][nei[1]] in 'E' and nei not in seen:
                            stack.append(nei)
                            seen.add(nei)
        return A

import collections
class Solution(object):
    def updateBoard(self, board, click):
        if not board:
            return
        m, n = len(board), len(board[0])
        queue = collections.deque()
        queue.append((click[0], click[1]))
        valid_neighbours = lambda (i, j): 0<=i<m and 0<=j<n

        while queue:
            x, y = queue.pop()
            if board[x][y] == 'M':
                board[x][y] = 'X'
            else:
                # Filter out the valid neighbours
                neighbours = filter(valid_neighbours, [(x-1, y), (x+1, y), 
                    (x, y-1), (x, y+1), (x-1, y-1), (x+1, y-1), (x-1, y+1), (x+1, y+1)])
                # Count the number of mines amongst the neighbours
                mine_count = sum([board[i][j]=='M' for i, j in neighbours])
                # If at least one neighbour is a potential mine, store the mine count.
                if mine_count > 0:
                    board[x][y] = str(mine_count)
                # If no neighbour is a mine, then add all unvisited neighbours
                # to the queue for future processing
                else:
                    board[x][y] = 'B'
                    queue.extend([(i, j) for (i, j) in neighbours if board[i][j]=='E'])
        return board