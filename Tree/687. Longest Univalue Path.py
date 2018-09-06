"""
687. Longest Univalue Path

Given a binary tree, find the length of the longest path where each node in the path has the same value. 
This path may or may not pass through the root.

Note: The length of path between two nodes is represented by the number of edges between them.

Example 1:

Input:

              5
             / \
            4   5
           / \   \
          1   1   5
Output:

2
Example 2:

Input:

              1
             / \
            4   5
           / \   \
          4   4   5
Output:

2


"""


class Solution:
    def longestUnivaluePath(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        def dfs(root):
            if not root: return 0, 0
            left, lmax = dfs(root.left)
            right, rmax = dfs(root.right)
            left = left + 1  if root.left and root.left.val == root.val else 0
            right = right + 1 if root.right and root.right.val == root.val else 0
            res = max(lmax, rmax, left+right)
            return max(left, right), res
        return dfs(root)[1]


class Solution(object):
    def longestUnivaluePath(self, root):
        # Time: O(n)
        # Space: O(n)
        longest = [0]
        def traverse(node):
            if not node:
                return 0
            left_len, right_len = traverse(node.left), traverse(node.right)
            left = (left_len + 1) if node.left and node.left.val == node.val else 0
            right = (right_len + 1) if node.right and node.right.val == node.val else 0
            longest[0] = max(longest[0], left + right)
            return max(left, right)
        traverse(root)
        return longest[0]



class Solution_iterative:
    def longestUnivaluePath(self, root):
        postorder = [(0, root, None)]
        count = 0
        d = {None: 0}
        while postorder:
            seen, node, parent = postorder.pop()
            if node is None:
                continue
            if not seen:
                postorder.append((1, node, parent))
                postorder.append((0, node.right, node.val))
                postorder.append((0, node.left, node.val))
            else:
                if node.val == parent:
                    d[node] = max(d[node.left], d[node.right]) + 1
                else:
                    d[node] = 0
                count = max(count, d[node.left] + d[node.right]) #只有当left == val, d[node.left] 才不是0，同理对于node.right
        return count