#79. Word Search


class Solution:
    def exist(self, board, word):
        """
        :type board: List[List[str]]
        :type word: str
        :rtype: bool
        """
        if not board:
            return False
        for i in range(len(board)):
            for j in range(len(board[i])):
                if board[i][j] == word[0] and self.dfs(board, i, j, word):
                    return True;
        return False
    
    def dfs(self,board, i, j, endWord):
        if 0 == len(endWord):
            return True
        if i<0 or i>=len(board) or j<0 or j>=len(board[0]) or board[i][j]!=endWord[0]:
            return False
        ch = board[i][j]
        board[i][j] = "#";
        exist = self.dfs(board,i-1, j, endWord[1:]) or self.dfs(board,i, j-1, endWord[1:]) or self.dfs(board,i+1, j, endWord[1:]) or self.dfs(board,i, j+1, endWord[1:])
        board[i][j] = ch
        return exist
        
 
class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        if not board or not(board[0]):
            return False 
        def dfs(i, j, word, visited):
            if not word:
                return True
            dir = [0,-1, 0, 1, 0]
            for x, y in zip(dir[:-1], dir[1:]):
                x_new, y_new = i + x, j + y 
                if x_new < 0 or y_new < 0 or x_new >= len(board) or y_new >= len(board[0]) or (x_new,y_new) in visited:
                    continue 
                if word[0] == board[x_new][y_new] and dfs(x_new, y_new, word[1:], visited | {(x_new, y_new)}):
                    return True
            return False
        return any(dfs(i, j, word[1:], set([(i,j)])) for i in range(len(board)) for j in range(len(board[0])) if board[i][j] == word[0])
