class Solution:
    def resultGrid(self, image: List[List[int]], threshold: int) -> List[List[int]]:
        n, m = len(image), len(image[0])
        res = [[[0,0] for _ in range(m) ] for _ in range(n)]
        final = [[[0] for _ in range(m) ] for _ in range(n)]

        def verify(i, j):
            if i < 2 or j < 2 :
                return 0, 0
            tmp_sum = 0
            for prev_i in range(i-2, i+1):
                for prev_j in range(j-2, j+1):
                    pos = [-1, 0, 1, 0]
                    tmp_sum += image[prev_i][prev_j]
                    for k in range(len(pos)-1):
                        next_i = prev_i + pos[k]
                        next_j = prev_j + pos[k+1]
                        if i-2 <= next_i <= i and  j-2 <= next_j <= j:
                            if abs(image[next_i][next_j] - image[prev_i][prev_j]) > threshold:
                                return 0,0
            return tmp_sum//9, 1

        for i in range(n):
            for j in range(m):
                tmp_sum, increment = verify(i, j)
                if increment:
                    for prev_i in range(i-2, i+1):
                        for prev_j in range(j-2, j+1):
                            res[prev_i][prev_j][0] += tmp_sum 
                            res[prev_i][prev_j][1] += increment
        for i in range(n):
            for j in range(m):
                if res[i][j][1]:
                    final[i][j] = res[i][j][0] // res[i][j][1]
                else:
                    final[i][j] = image[i][j]
        return final
        

class Solution:
    def resultGrid(self, image: List[List[int]], threshold: int) -> List[List[int]]:
        n, m = len(image), len(image[0])
        cur = [[0, ]*m for _ in range(n)]
        res = [[[0,0] for _ in range(m) ] for _ in range(n)]
        final = [[[0] for _ in range(m) ] for _ in range(n)]

        def verify(i, j):
            if i < 2 or j < 2 :
                return False
            for prev_i in range(i-2, i+1):
                for prev_j in range(j-2, j+1):
                    pos = [-1, 0, 1, 0]
                    for k in range(len(pos)-1):
                        next_i = prev_i + pos[k]
                        next_j = prev_j + pos[k+1]
                        if i-2 <= next_i <= i and  j-2 <= next_j <= j:
                            if abs(image[next_i][next_j] - image[prev_i][prev_j]) > threshold:
                                print(i, j, prev_i, prev_j,image[prev_i][prev_j],  next_i, next_j, image[next_i][next_j])
                                return False
            return True

        for i in range(n):
            for j in range(m):
                cur[i][j] = image[i][j] + (cur[i-1][j] if i > 0 else 0 )  \
                                        + (cur[i][j-1] if j > 0 else 0 ) \
                                        -  (cur[i-1][j-1] if j > 0 and i > 0 else 0 ) 
                if verify(i, j):
                    cnt = cur[i][j] - (cur[i-3][j] if i > 2 else 0) \
                                    - (cur[i][j-3] if j > 2 else 0) \
                                    + (cur[i-3][j-3] if i>2 and j > 2 else 0)
                    cnt = cnt // 9
                    for prev_i in range(i-2, i+1):
                        for prev_j in range(j-2, j+1):
                            res[prev_i][prev_j][0] += cnt 
                            res[prev_i][prev_j][1] += 1
        for i in range(n):
            for j in range(m):
                if res[i][j][1]:
                    final[i][j] = res[i][j][0] // res[i][j][1]
                else:
                    final[i][j] = image[i][j]
        return final
        
                    