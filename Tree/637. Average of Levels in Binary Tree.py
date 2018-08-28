"""
637. Average of Levels in Binary Tree
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
"""

#DFS
class Solution:
    def averageOfLevels(self, root):
        """
        :type root: TreeNode
        :rtype: List[float]
        """
        li = []
        def dfs(root, level = 1):
            if not root: return 
            if len(li) < level: 
                li.append([])
            li[level-1].append(root.val)
            dfs(root.left, level + 1)
            dfs(root.right, level + 1)
        dfs(root)
        return [sum(l)/len(l) for l in li]


#BFS
class Solution:
    def averageOfLevels(self, root):
        queue = collections.deque()
        if root:
            queue.append(root)
        res = []
        while queue:
            size = len(queue)
            sum = 0
            for i in range(size):
                node = queue.popleft()
                sum += node.val
                if node.left: queue.append(node.left)
                if node.right: queue.append(node.right)
            res += [sum / size]
        return res 


class Solution:
    def averageOfLevels(self, root):
        queue = collections.deque()
        if root:
            queue.append(root)
            queue.append(None)
        res = []
        sum = count = 0
        while queue:
            node = queue.popleft()
            if not node:
                res.append(sum /count)
                sum = count = 0
                if queue: queue.append(None)
            else:
                sum += node.val
                count += 1
                if node.left: queue.append(node.left)
                if node.right: queue.append(node.right)
        return res 


import statistics
class Solution:
    def averageOfLevels(self, root):
        def levelOrder(root):
            res = []
            level = [root]
            while any(level):
                res.append([node.val for node in level])
                level = [kid for node in level for kid in (node.left, node.right) if kid]
            return res
        return [*map(statistics.mean, levelOrder(root))]