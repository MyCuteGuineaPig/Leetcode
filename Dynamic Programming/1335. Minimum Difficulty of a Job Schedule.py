class Solution:
    def minDifficulty(self, jobDifficulty: List[int], d: int) -> int:
        if len(jobDifficulty) < d:
            return -1
        n = len(jobDifficulty)
        dp = [float('inf') for _ in range(n)]

        curmax = 0
        for j in range(n):
            curmax = max(curmax, jobDifficulty[j])
            dp[j] = curmax
            
        for i in range(1, d):
            for j in range(n-1, -1, -1):
                dp[j] = float('inf')
                curmax = jobDifficulty[j]
                for k in range(j-1, -1, -1):
                    dp[j] = min(dp[j], dp[k]+ curmax)
                    curmax = max(curmax, jobDifficulty[k])
        return dp[-1]
            
        


class Solution:
    def minDifficulty(self, jobDifficulty: List[int], d: int) -> int:
        if len(jobDifficulty) < d:
            return -1
        n = len(jobDifficulty)
        dp = [[float('inf') for _ in range(n)] for _ in range(d)]
        curmax = 0
        for j in range(n):
            curmax = max(curmax, jobDifficulty[j])
            dp[0][j] = curmax
            
        for i in range(1, d):
            for j in range(n):
                curmax = jobDifficulty[j]
                for k in range(j-1, -1, -1):
                    dp[i][j] = min(dp[i][j], dp[i-1][k]+ curmax)
                    curmax = max(curmax, jobDifficulty[k])

        return dp[-1][-1]
            


class Solution:
    def minDifficulty(self, jobDifficulty: List[int], d: int) -> int:
        n = len(jobDifficulty)
        if n < d: return -1
        dp, dp2 = [float('inf')] * n, [0] * n
        for d in range(d):
            stack = []
            for i in range(d, n):
                dp2[i] = dp[i - 1] + jobDifficulty[i] if i else jobDifficulty[i]
                while stack and jobDifficulty[stack[-1]] <= jobDifficulty[i]:
                    j = stack.pop()
                    dp2[i] = min(dp2[i], dp2[j] - jobDifficulty[j] + jobDifficulty[i])
                if stack:
                    dp2[i] = min(dp2[i], dp2[stack[-1]])
                stack.append(i)
            dp, dp2 = dp2, dp
            #print(dp)
        return dp[-1]
            



class Solution:
    def minDifficulty(self, val: List[int], d: int) -> int:
        if len(val)<d:
            return -1
        n,f=len(val),val[:]
        for i in range(1,n):
            f[i]=max(f[i-1],f[i])
        for t in range(1,d):
            temp=[10**9]*t
            st=[(10**9,0,0)]
            for i in range(t,n):
                m,j=f[i-1],i-1
                while st[-1][0]<val[i]:
                    m,j=min(m,st[-1][1]),st[-1][2]
                    st.pop()
                if len(st)>1:
                    temp.append(min(temp[j],m+val[i]))
                else:
                    temp.append(m+val[i])
                st.append((val[i],m,j))
            f=temp