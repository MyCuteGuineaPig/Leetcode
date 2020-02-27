class Node:
    def __init__(self,):
        self.dic = collections.defaultdict(Node)
        self.isleaf = False

class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        node = Node()
        res = set()
        def build(words):
            nd = node
            for i in words:
                #print(words, i)
                nd = nd.dic[i]
            nd.isleaf = True
        def loop(cur, t, visited, i, j):
            if t.isleaf:
                res.add(cur)
            dir = [0,-1,0,1,0]
            for x, y in zip([0,-1,0,1],[-1,0,1,0]):
                x_new, y_new = i + x, y + j
                if x_new < 0 or  y_new < 0 or x_new >= len(board) or y_new >= len(board[0]) or board[x_new][y_new] not in t.dic or (x_new, y_new) in visited: 
                    continue
                nxt =  board[x_new][y_new]
                loop(cur + nxt, t.dic[nxt], visited | {(x_new, y_new)}, x_new, y_new)
        for word in words:
            build(word)
        for i, row in enumerate(board):
           for j, v in enumerate(row):
                if v in node.dic:
                    #print("in")
                    loop(v, node.dic[v], set([(i,j)]), i,j )
        return list(res)
