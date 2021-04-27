class Solution:
    def totalFruit(self, tree: List[int]) -> int:
        res = cur = count_b = a = b = 0
        for c in tree:
            cur = cur + 1 if c in (a, b) else count_b + 1
            count_b = count_b + 1 if c == b else 1
            if b != c: a, b = b, c
            res = max(res, cur)
        return res
        
class Solution:
    def totalFruit(self, tree: List[int]) -> int:
        count, i = {}, 0
        for j, v in enumerate(tree):
            count[v] = count.get(v, 0) + 1
            if len(count) > 2:
                count[tree[i]] -= 1
                if count[tree[i]] == 0: del count[tree[i]]
                i += 1
        return j - i + 1
        
class Solution:
    def totalFruit(self, tree: List[int]) -> int:
        ans = i = 0
        count = collections.Counter()
        for j, x in enumerate(tree):
            count[x] += 1
            while len(count) >= 3:
                count[tree[i]] -= 1
                if count[tree[i]] == 0:
                    del count[tree[i]]
                i += 1
            ans = max(ans, j - i + 1)
        return ans
        