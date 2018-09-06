"""
889. Construct Binary Tree from Preorder and Postorder Traversal

Example 1:

Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
Output: [1,2,3,4,5,6,7]
 

Note:

1 <= pre.length == post.length <= 30
pre[] and post[] are both permutations of 1, 2, ..., pre.length.
It is guaranteed an answer exists. If there exists multiple answers, you can return any of them.

"""

# use self.index 
class Solution:
    def constructFromPrePost(self, pre, post):
        """
        :type pre: List[int]
        :type post: List[int]
        :rtype: TreeNode
        """
        self.ind = 0
        postmap = dict((v, i) for i, v in enumerate(post))
        def createTree(end): #end 是post的当前右边界
            if self.ind >= len(pre) or end < postmap[pre[self.ind]]: return None
            val = pre[self.ind]; self.ind += 1
            node = TreeNode(val)
            node.left = createTree(postmap[val])
            if node.left:
                node.right = createTree(postmap[node.val])
            return node 
        return createTree(len(post))


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None
class Solution:
    def constructFromPrePost(self, pre, post):
        if not pre: return None
        root = TreeNode(pre[0])
        if len(pre) == 1: return root
        # O(n) for lookup, can use a hashmap to store the index
        L = post.index(pre[1]) + 1
        root.left = self.constructFromPrePost(pre[1:L+1], post[:L])
        root.right = self.constructFromPrePost(pre[L+1:], post[L:-1])
        return root

class Solution:
    def constructFromPrePost(self, pre, post):
        q = [TreeNode(pre[0])]
        j, n = 0, len(post)
        for v in pre[1:]:
            cur = TreeNode(v)
            if not q[-1].left: q[-1].left = cur
            else: q[-1].right = cur
            q.append(cur)
            while j < n-1 and q[-1].val == post[j]:
                q.pop()
                j+=1
        return q[0]


class Solution():
    def constructFromPrePost(self, pre, post):
        vals = [TreeNode(pre[0])]
        j = 0
        for i in pre[1:]:
            n = TreeNode(i)
            while vals[-1].val == post[j]:
                vals.pop()
                j += 1
            if not vals[-1].left:
                vals[-1].left = n
            else:
                vals[-1].right = n
            vals.append(n)
        return vals[0]