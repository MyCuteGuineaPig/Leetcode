"""
863. All Nodes Distance K in Binary Tree

Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2

Output: [7,4,1]

Explanation: 
The nodes that are a distance 2 from the target node (with value 5)
have values 7, 4, and 1.

"""
"""
Solution DFS:
不可以杂交
比如:
 l = dfs(l.left, K, dis == -1 ? -1: dis + 1, res)
 r = dfs(r.right, K, dis == -1 ? -1: max(l, dis) + 1, res)
 
这样可能有个后果，比如K=4, target = 1, 
                1
               /  \
              2    4
             /      \
            3        5
左面运行完 l = 2, 带进右侧tree, 到5的时候dis 就变成了4, 4的左侧右侧都没node, return dis = 4 到4， 再到1
这样就把4, 1也算进了node, 实际上都不应该算
"""



class Solution:
    def distanceK(self, root, target, K):
        res = []
        def dfs(node, path):
            if not node: return path
            if node == target: path = K #开始的地方
                
            l = dfs(node.left, path - 1)
            r = dfs(node.right, path - 1)
            if path < 0 and (l >0 or r > 0) : 
                path = max(l, r)-1
                dfs(node.right, l-2) if l > 0 else dfs(node.left, r-2)#-2是跨过现在的, 只能有一侧大于0
            if path == 0:     #可能 K = 0
                res.append(node.val)  
            return path
        dfs(root, -1)
        return res 

# DFS + BFS
class Solution:
    def distanceK(self, root, target, K):
        adj = collections.defaultdict(list)
        def dfs(node, parent):
            if not node: return
            if parent: 
                adj[node.val].append(parent.val)
                adj[parent.val].append(node.val)
            dfs(node.left, node)
            dfs(node.right, node)
        
        dfs(root, None)
        visited = set([target.val])
        bfs = [target.val]
        for _ in range(K):
            bfs = [kid for node in bfs for kid in adj[node] if kid not in visited]
            visited |= set(bfs)
        return bfs


# two DFS
class Solution:
    def distanceK(self, root, target, K):
        adj, res, visited = collections.defaultdict(list), [], set()
        def dfs(node):
            if node.left:
                adj[node].append(node.left)
                adj[node.left].append(node)
                dfs(node.left)
            if node.right:
                adj[node].append(node.right)
                adj[node.right].append(node)
                dfs(node.right)
        dfs(root)
        def dfs2(node, d):
            if d < K:
                visited.add(node)
                for v in adj[node]:
                    if v not in visited:
                        dfs2(v, d + 1)
            else:
                res.append(node.val)
        dfs2(target, 0)
        return res




# Another DFS
class Solution:
    def distanceK(self, root, target, K):
        """
        :type root: TreeNode
        :type target: TreeNode
        :type K: int
        :rtype: List[int]
        """
        def findAtK(root, K):
            if not root or K < 0:
                return []
            elif K == 0:
                return [root.val]
            else:
                return findAtK(root.left, K-1) + findAtK(root.right, K-1)
        
        def find(root, target, K):
            if not root:
                return float("-inf"), []
            elif root.val == target.val:
                return K-1, findAtK(root, K)#它的kid
            else:
                lh, lv = find(root.left, target, K)
                rh, rv = find(root.right, target, K)
                reth = max(lh, rh) - 1
                retv = lv + rv
                if lh == 0 or rh == 0:
                    retv += [root.val]
                elif lh > 0:
                    retv += findAtK(root.right, lh-1)
                elif rh > 0:
                    retv += findAtK(root.left, rh-1)
                return reth, retv
        
        return find(root, target, K)[1]     