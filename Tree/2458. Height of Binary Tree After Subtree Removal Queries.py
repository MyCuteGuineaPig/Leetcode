class Solution:
    def treeQueries(self, root: Optional[TreeNode], queries: List[int]) -> List[int]:
        ans = {}
        ht = lru_cache(maxsize= 20000)(lambda r: 1 + max(ht(r.left), ht(r.right)) if r else 0)
        def dfs(r, depth ,maxHeight):
            if not r: 
                return 
            ans[r.val] = maxHeight
            dfs(r.left, depth + 1, max(maxHeight, depth + ht(r.right)))
            dfs(r.right, depth + 1, max(maxHeight, depth + ht(r.left)))
        dfs(root, 0, 0)
        return [ans[i] for i in queries]

class Solution: 
    def treeQueries(self, root: Optional[TreeNode], queries: list[int]) -> list[int]:
        
        @functools.cache
        def h(n): return 1 + max(h(n.left), h(n.right)) if n else 0
        
        def dfs(n, d, m):
            if not n: return
            result[n.val] = m
            dfs(n.left, d+1, max(m, d + h(n.right))) 
            dfs(n.right, d+1, max(m, d + h(n.left))) 
        
        result = [0] * 100001
        dfs(root, 0, 0)
        
        return [result[q] for q in queries]


# swap and run dfs twice
class Solution:
    def treeQueries(self, root: Optional[TreeNode], queries: List[int]) -> List[int]:
        res = defaultdict(int)

        def dfs(root, h, maxh):
            if not root: return maxh
            res[root.val] = max(res[root.val], maxh)
            root.left, root.right = root.right, root.left
            return dfs(root.right, h + 1, dfs(root.left, h + 1, max(maxh, h)))

        dfs(root, 0, 0)
        dfs(root, 0, 0)
        return [res[q] for q in queries]

# depth - 1 + height (from the same level)
class Solution:
    def treeQueries(self, root: Optional[TreeNode], queries: List[int]) -> List[int]:
    
        height, depths, levels = {}, {}, defaultdict(list)
        
        def dfs(n, d):
            if not n: return 0
            h = 1 + max(dfs(n.left, d+1), dfs(n.right, d+1))
            levels[d].append(n.val)
            height[n.val] = h
            depths[n.val] = d
            return h
        
        @functools.cache
        def query(q):
            max_height = max([height[v] for v in levels[depths[q]] if v != q] or [0])
            return depths[q] - 1 + max_height
        
        dfs(root, 0)     
        
        return [query(q) for q in queries]
