"""
662. Maximum Width of Binary Tree

Example 1:
Input: 

           1
         /   \
        3     2
       / \     \  
      5   3     9 

Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
Example 2:
Input: 

          1
         /  
        3    
       / \       
      5   3     

Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).
Example 3:
Input: 

          1
         / \
        3   2 
       /        
      5      

Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).
Example 4:
Input: 

          1
         / \
        3   2
       /     \  
      5       9 
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).



"""

#DFS
class Solution:
    def widthOfBinaryTree(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        self.stack = []
        self.res = 0
        def dfs(node, l, index):
            if not node: return 
            if l >= len(self.stack): 
                self.stack.append(index)
            self.res = max(self.res, index - self.stack[l]+1)
            dfs(node.left, l+1, 2*index-1)
            dfs(node.right, l+1, 2*index)
        dfs(root, 0, 1)
        return self.res


#BFS
class Solution:
    def widthOfBinaryTree(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        if not root: return 0
        left = []
        queue = collections.deque(); queue.append((root,1))
        res = 0 
        while queue:
            size = len(queue)
            left = queue[0][1]
            for _ in range(size):
                cur, ind = queue.popleft()
                res = max(res, ind - left+1)
                if cur.left: 
                    queue.append((cur.left, 2*ind - 1))
                if cur.right:
                    queue.append((cur.right, 2*ind))
        return res
        

class Solution:
    def widthOfBinaryTree(self, root):
        width = 0
        level = [(1, root)]
        while level:
            width = max(width, level[-1][0] - level[0][0] + 1)
            level = [kid
                    for number, node in level
                    for kid in enumerate((node.left, node.right), 2 * number)
                    if kid[1]]
        return width

class Solution:
    def widthOfBinaryTree(self, root):
        def dfs(node, depth = 0, pos = 0):
            if node:
                yield depth, pos
                yield from dfs(node.left, depth + 1, pos * 2)
                yield from dfs(node.right, depth + 1, pos * 2 + 1)

        left = {}
        right = {}
        ans = 0
        for depth, pos in dfs(root):
            left[depth] = min(left.get(depth, pos), pos)
            right[depth] = max(right.get(depth, pos), pos)
            ans = max(ans, right[depth] - left[depth] + 1)

        return ans