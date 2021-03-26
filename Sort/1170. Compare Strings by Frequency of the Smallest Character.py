class Solution:
    def numSmallerByFrequency(self, queries: List[str], words: List[str]) -> List[int]:
        fw = [0, ]*12 #最大frequency是10， cnt+1最大是11，所以需要12个
        
        def find(s):
            c = s[0]
            cnt = 0
            for letter in s:
                if letter < c:
                    c = letter
                    cnt = 1
                elif letter == c:
                    cnt += 1
            return c, cnt
        
        for word in words:
            c, cnt = find(word)
            fw[cnt] += 1
            
        for i in range(9, -1, -1):
            fw[i] += fw[i+1]
            
        res = []
        for query in queries:
            c, cnt = find(query)
            res.append(fw[cnt+1])
        return res

class Solution:
    def numSmallerByFrequency(self, queries: List[str], words: List[str]) -> List[int]:
        f = sorted(w.count(min(w)) for w in words)
        return [len(f) - bisect.bisect(f, q.count(min(q))) for q in queries]
