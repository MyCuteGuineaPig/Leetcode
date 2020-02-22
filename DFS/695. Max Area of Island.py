def maxAreaOfIsland(self, grid):
    grid = {i + j*1j: val for i, row in enumerate(grid) for j, val in enumerate(row)}
    def area(z):
        return grid.pop(z, 0) and 1 + sum(area(z + 1j**k) for k in range(4))
    return max(map(area, set(grid)))
 
 """
  grid.pop(z,0) 如果有z, pop dictionary value, 否则pop 0
  
  z + 1j**k for k in range(4): z的四个方向
  
  比如 z = 1+4j
  
  1+4j + 1j**0 = 2 + 4j
  1+4j + 1j**1 = 1 + 5j
  1+4j + 1j**2 = 0 + 4j
  1+4j + 1j**3 = 1 + 3j
  
  
 """
