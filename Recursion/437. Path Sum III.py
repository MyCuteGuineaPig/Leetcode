"""
437. Path Sum III

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11

"""
class Solution:
    def pathSum(self, root, sum):
        """
        :type root: TreeNode
        :type sum: int
        :rtype: int
        """
        dict = collections.defaultdict(int)
        dict[0] = 1
        def dfs(root,tot):
            if root is None: return 0
            tot += root.val
            res = 0
            if tot - sum in dict:
                res += dict[tot- sum]
            dict[tot] += 1
            l,r = dfs(root.left,tot), dfs(root.right,tot)
            dict[tot] -= 1
            return l+r+res
        return dfs(root,0)