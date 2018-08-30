"""
654. Maximum Binary Tree

Example 1:
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    / 
     2  0   
       \
        1

"""


class Solution:
    def constructMaximumBinaryTree(self, nums):
        """
        :type nums: List[int]
        :rtype: TreeNode
        """
        stack = []
        for i in nums:
            cur = TreeNode(i)
            if stack and i > stack[-1].val:
                while stack and i > stack[-1].val:
                    prev = stack.pop()
                cur.left = prev
            if stack: 
                stack[-1].right = cur
            stack.append(cur)
        return stack[0]

class Solution:
    def constructMaximumBinaryTree(self, nums):
        """
        :type nums: List[int]
        :rtype: TreeNode
        """
        stack = []
        for i in nums:
            cur = TreeNode(i)
            if stack and i > stack[-1].val:
                while stack and i > stack[-1].val:
                    cur.left = stack.pop()
            if stack: 
                stack[-1].right = cur
            stack.append(cur)
        return stack[0]

#DFS
class Solution:
    def constructMaximumBinaryTree(self, nums):
        if not nums: return None
        root, ind = TreeNode(max(nums)), nums.index(max(nums))
        root.left = self.constructMaximumBinaryTree(nums[:ind])
        root.right = self.constructMaximumBinaryTree(nums[ind+1:])
        return root