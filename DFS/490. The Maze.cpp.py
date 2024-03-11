class Solution:
    def hasPath(self, maze: List[List[int]], start: List[int], destination: List[int]) -> bool:
        def fn(y, x):
            if grid.pop((y, x), 0):
                if [y, x] == destination:
                    result.add(1)
                    return
                #print("after y, x" , y, x)
                for dy, dx in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                    y_, x_ = y, x
                    while grid_src.get((y_ + dy, x_ + dx)):
                        y_, x_ = y_ + dy, x_ + dx
                    fn(y_, x_)

        grid = {(y, x): 1 - val for y, row in enumerate(maze) for x, val in enumerate(row)}
        grid_src, result = grid.copy(), set()
        return fn(*start) or result