//52. N-Queens II

class Solution:
    def totalNQueens(self, n):
        """
        :type n: int
        :rtype: int
        """
        result=[]
        self.DFS(n,0,"",[],[],[],result)
        print(result)
        return len(result) 
            
    def DFS(self, n, row, sss, check_col,check_diag1,check_diag2, result):
        """ sss is solution string, all other checks are checks for occupied places """
        if (len(sss) == n):
            result.append('.')
            return
        
        for col in range(0,n):
            if (col in check_col): continue
            if (row+col in check_diag1): continue
            if (row-col in check_diag2): continue
            self.DFS(n, row+1, sss+str(col), check_col+[col], 
                 check_diag1+[row+col], check_diag2+[row-col],result)
        

class Solution:
    def totalNQueens(self, n):
        """
        :type n: int
        :rtype: int
        """
        def isValid(l,index):
            for i in range(index):
                if l[i] == l[index] or abs(l[i]-l[index]) == index-i: 
                    return False
            return True
        
        def dfs(l,index):
            if(len(l) == n):
                self.res+=1
                return
            for i in range(n):
                if isValid(l+[i],index):
                    dfs(l+[i],index+1)
        self.res = 0
        dfs([],0)
        return self.res
    
#2020
class Solution:
    def totalNQueens(self, n: int) -> int:
        self.res = 0
        def dfs(rows, dia1, dia2):
            row = len(rows)
            if row == n:
                self.res += 1
            if row < n:
                for j in range (n):
                    if j not in rows and row + j not in dia1 and row - j not in dia2:
                        dfs(rows | {j}, dia1 | {row + j}, dia2 | {row - j} )
                    
        dfs(set(), set(), set())
        return self.res
#2020
class Solution:
    def totalNQueens(self, n: int) -> int:
        col = [0 for _ in range(n)]
        dia1, dia2 = [0 for _ in range(2*n-1)], [0 for _ in range(2*n-1)]
        self.res = 0
        def dfs(i):
            if i == n:
                self.res += 1
                return 
            if i < n:
                for j in range (n):
                    if isValid(i, j):
                        assign(i,j,1)
                        dfs(i+1)
                        assign(i, j, 0)
        
        def isValid(i, j):
            return not (col[j] or dia1[n-1+i-j] or dia2[i+j])
        
        def assign(i, j, val):
            col[j] = val
            dia1[n-1+i-j] = val 
            dia2[i+j] = val
        dfs(0)
        return self.res
