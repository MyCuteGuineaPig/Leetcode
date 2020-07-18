"""
764. Largest Plus Sign
"""
class Solution:
    def orderOfLargestPlusSign(self, N, mines):
        """
        :type N: int
        :type mines: List[List[int]]
        :rtype: int
        """
        dp = [[N,]*N for _ in range(N)]
        for i,j in mines:
            dp[i][j] = 0
        for i in range(N):
            u, d , l, r = 0 , 0, 0, 0
            j, k = 0, N-1
            while j<=N-1 :
                l = (l + 1) if dp[i][j] != 0 else 0
                r = (r + 1) if dp[i][k] != 0 else 0
                u = (u + 1) if dp[j][i] != 0 else 0
                d = (d + 1) if dp[k][i] != 0 else 0
                
                dp[i][j] = min(dp[i][j], l)
                dp[i][k] = min(dp[i][k], r)
                dp[j][i] = min(dp[j][i], u)
                dp[k][i] = min(dp[k][i], d)
                
                
                j+=1
                k-=1
        return max(v for i in dp for v in i)



class Solution:
    def orderOfLargestPlusSign(self, N: int, mines: List[List[int]]) -> int:
        rows = [[-1, N] for _ in range(N)]
        cols = [[-1, N] for _ in range(N)]
        for r, c in mines:
            rows[r].append(c)
            cols[c].append(r)
        for i in range(N):
            rows[i].sort()
            cols[i].sort()
        mxp = 0
        for r in range(N):
            for i in range(len(rows[r])-1):
                left_b = rows[r][i]
                right_b = rows[r][i+1]
                for c in range(left_b+mxp+1, right_b-mxp):  #mxp是现有答案，所以找可能大于mxp 才有可能更新mxp，就是 left_b + mxp+1
                    idx = bisect.bisect_right(cols[c], r)-1 #找col[c]中大于r行的
                    up_b = cols[c][idx]
                    down_b = cols[c][idx+1]
                    mxp = max(mxp, min(c-left_b, right_b-c, r-up_b, down_b-r))
        return mxp
    


class Solution:
    def orderOfLargestPlusSign(self, N: int, mines: List[List[int]]) -> int:
        rows = [[-1, N] for _ in range(N)]
        cols = [[-1, N] for _ in range(N)]
        for r, c in mines:
            rows[r].append(c)
            cols[c].append(r)
        for i in range(N):
            rows[i].sort()
            cols[i].sort()
        cols = [iter(col) for col in cols]
        up_b = [next(col) for col in cols]
        down_b = [next(col) for col in cols]
        mxp = 0
        for r in range(N):
            for i in range(len(rows[r])-1):
                left_b = rows[r][i]
                right_b = rows[r][i+1]
                for c in range(left_b+mxp+1, right_b-mxp):
                    while down_b[c] <= r:
                        up_b[c] = down_b[c]
                        down_b[c] = next(cols[c])
                    mxp = max(mxp, min(c-left_b, right_b-c, r-up_b[c], down_b[c]-r))
        return mxp