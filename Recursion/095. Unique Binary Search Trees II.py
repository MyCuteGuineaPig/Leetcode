"""
95. Unique Binary Search Trees II

Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

"""


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def generateTrees(self, n):
        """
        :type n: int
        :rtype: List[TreeNode]
        """
        def generater(start, end):
            if start>end:
                return [None]
            if start == end:
                return [TreeNode(start)]
            li = []
            for i in range(start,end+1):
                left = generater(start,i-1)
                right = generater(i+1,end)
                for l in left:
                    for r in right:
                        tree = TreeNode(i)
                        tree.left = l 
                        tree.right = r
                        li.append(tree)
            return li
        return [] if n == 0 else generater(1,n)




class Solution:
   def generateTrees(self, n):
        dp = collections.defaultdict(lambda: collections.defaultdict(lambda: None))
        def generater(start, end):
            if start in dp and end in dp[start]: return dp[start][end]
            if start>end:
                return [None]
            if start == end:
                return [TreeNode(start)]
            li = []
            for i in range(start,end+1):
                left = generater(start,i-1)
                right = generater(i+1,end)
                for l in left:
                    for r in right:
                        tree = TreeNode(i)
                        tree.left = l 
                        tree.right = r
                        li.append(tree)
            dp[start][end] = li
            return li
        return [] if n == 0 else generater(1,n)
      
      
      
      
      
def generateTrees(self, n):
    def node(val, left, right):
        node = TreeNode(val)
        node.left = left
        node.right = right
        return node
    def trees(first, last):
        return [node(root, left, right)
                for root in range(first, last+1)
                for left in trees(first, root-1)
                for right in trees(root+1, last)] or [None]
    return trees(1, n)
