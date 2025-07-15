class Solution:
    def alienOrder(self, words: List[str]) -> str:
        degree = {}
        graph = collections.defaultdict(set)
        for i in range(len(words)):
            for j in range(len(words[i])):
                degree[words[i][j]]=0
        
        for i in range(len(words)-1):
            word1 = words[i]
            word2 = words[i+1]
            idx = 0
            for j in range(min(len(word1),len(word2))):
                if(word1[j]!=word2[j]):
                    key1 = word1[j]
                    key2 = word2[j]
                    if(key2 not in graph[key1]):
                        degree[key2] +=1
                        graph[key1].add(key2)
                    break
            else:
                if len(word1) > len(word2):
                    return ""
        q = collections.deque()
        res = ''
        for i, cnt in degree.items():
            if cnt == 0:
                q.append(i)
        
        while(len(q)!=0):
            c = q.popleft()
            res+= c
            for nxt in graph[c]:
                degree[nxt]-=1
                if(degree[nxt]==0):
                    q.appendleft(nxt)
        if(len(degree)!=len(res)):
            return ""
        return res