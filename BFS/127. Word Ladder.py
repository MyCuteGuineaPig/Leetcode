class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        if endWord not in wordList or len(wordList) == 0:
            return 0 
        dic = collections.defaultdict(list)
        for word in wordList:
            for i in range(len(word)):
                dic[word[:i]+"*"+word[i+1:]].append(word)
        
        qbegin = collections.deque([(beginWord, 1)]); 
        qend = collections.deque([(endWord,1)])
        
        
        vbegin = {beginWord: 1}
        vend = {endWord: 1}
        
        def search(q, visited, othervisited):
            word, level = q.popleft()
            for i in range(len(word)):
                cur = word[:i]+"*"+word[i+1:]
                for nxt in dic[cur]:
                    if nxt in othervisited:
                        return level + othervisited[nxt]
                    if nxt not in visited:
                        visited[nxt] = level + 1
                        q.append((nxt, level + 1))
                dic[cur] = []
            return None 
        
        while qbegin or qend:
            if qbegin:
                ans = search(qbegin, vbegin, vend)
                if ans: return ans
            if qend:
                ans = search(qend, vend, vbegin)
                if ans: return ans
        return 0