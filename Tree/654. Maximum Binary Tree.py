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
    def constructMaximumBinaryTree(self, nums: List[int]) -> TreeNode:
        stk = []
        for v in nums:
            cur = TreeNode(v)
            while stk and stk[-1].val < v:
                    cur.left = stk.pop()
            if stk and stk[-1].val > v: 
                stk[-1].right = cur
            stk.append(cur)
        return stk[0]

"""
if stk and stk[-1].val > v: 
    stk[-1].right = cur
 比如: 
 #[48,259,222,129,17,245,174,68,8,261]
 
 在259的tree             在245 tree
 
           259              245
          /   \             /  \
         48    222       222    174
                 \        \       \ 
                 129      129      68
                   \       \        \
                    17      17       8 
                    
 如果没有 if 条件句 这句当, 259 右侧 连不上245 会变成dangling  
                     

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

#DFS
class Solution:
    def constructMaximumBinaryTree(self, nums):
        if not nums: return None
        root, ind = TreeNode(max(nums)), nums.index(max(nums))
        root.left = self.constructMaximumBinaryTree(nums[:ind])
        root.right = self.constructMaximumBinaryTree(nums[ind+1:])
        return root
