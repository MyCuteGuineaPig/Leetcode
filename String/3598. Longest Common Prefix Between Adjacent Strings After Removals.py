class Solution:
    def longestCommonPrefix(self, words: List[str]) -> List[int]:

        n = len(words)
        suffix = [0] * n
        prefix = [0] * n

        if n == 1:
            return [0]

        @lru_cache(None)    
        def lcp(s1, s2):
         
            res = 0
            for a, b in zip(s1, s2):
                if a != b: return res
                res+=1
            return res

            
        for i in range(n-2, -1, -1):
            suffix[i] = max(suffix[i+1], lcp(words[i], words[i+1]))

        for i in range(1, n):
            prefix[i] = max(prefix[i-1], lcp(words[i], words[i-1]))

        ans = []
        
        for i in range(n):
            if i-1 < 0:
                ans.append(suffix[i+1])
                continue
                
            if i+1 == n:
                ans.append(prefix[i-1])
                continue

            ans.append(max(prefix[i-1], suffix[i+1], lcp(words[i-1], words[i+1])))

        return ans

class Solution:
    def longestCommonPrefix(self, words: List[str]) -> List[int]:
        def lcp(i, j):
            for k, (w_a, w_b) in enumerate(zip(words[i], words[j])):
                if w_a !=  w_b:
                    return k
            return min(len(words[i]), len(words[j]))
        
        L = [lcp(i, i+1) for i in range(len(words)-1)]
        cur_lcp = list(accumulate(L, max, initial=0))
        rev_lcp = list(accumulate(L[::-1], max, initial=0))[::-1]

        res = [0] * len(words)
        if len(words) == 1 :
            return res
        res[0] = rev_lcp[1]
        res[-1] = cur_lcp[-2]
        for i in range(1,len(words)-1):
            res[i] = max(cur_lcp[i-1], rev_lcp[i+1], lcp(i-1, i+1))
        return res

