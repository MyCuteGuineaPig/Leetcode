#72. Edit Distance

class Solution:
    def minDistance(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        table = [[0 for _ in range(len(word2)+1)] for _ in range(len(word1) + 1)]
        for i in range(len(word1)):
            table[i+1][0] = i+1
        for j in range(len(word2)):
            table[0][j+1] = j+1

        for i, x in enumerate(word1):
            for j, y in enumerate(word2):
                if x == y:
                    table[i+1][j+1] = table[i][j]
                else: 
                    table[i+1][j+1] = 1 + min(table[i][j],table[i+1][j],table[i][j+1])
        return table[-1][-1]

class Solution:
    def minDistance(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        table={} 
        table[0,0] = 0
        for i in range(len(word1)):
            table[i+1,0] = i+1
        for j in range(len(word2)):
            table[0,j+1] = j+1

        for i, x in enumerate(word1):
            for j, y in enumerate(word2):
                if x == y:
                    table[i+1,j+1] = table[i,j]
                else: 
                    table[i+1,j+1] = 1 + min(table[i,j],table[i+1,j],table[i,j+1])
        return table[len(word1),len(word2)]


class Solution:
    def minDistance(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        dp = {}
        def edit(i, j):
            if (i, j) not in dp:
                if not (i and j):
                    dp[i, j] = i + j
                elif word1[i - 1] == word2[j - 1]:
                    dp[i, j] = edit(i - 1, j - 1)
                else:
                    dp[i, j] = min(edit(i - 1, j) + 1, edit(i, j - 1) + 1,
                                   edit(i - 1, j - 1) + 1)
            return dp[i, j]

        return edit(len(word1), len(word2))