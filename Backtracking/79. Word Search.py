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
        