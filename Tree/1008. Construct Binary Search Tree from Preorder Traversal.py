class Solution:
    def bstFromPreorder(self, preorder: List[int]) -> TreeNode:
        i = [0]
        def dfs(bound):
            if i[0]  == len(preorder) or preorder[i[0]] > bound:
                return None 
            cur = TreeNode(preorder[i[0]])
            i[0] = i[0] + 1
            cur.left = dfs(cur.val)
            cur.right = dfs(bound)
            return cur
        return dfs(float('inf'))


#Stack 
class Solution:
    def bstFromPreorder(self, preorder: List[int]) -> TreeNode:
        if not preorder:
            return None 
        res = TreeNode(preorder[0])
        stk = [res]
        for v in preorder[1:]:
            cur = TreeNode(v)
            if stk[-1].val > v:
                stk[-1].left = cur
            else:
                while stk and stk[-1].val < v:
                    last = stk.pop()
                last.right = cur 
            stk.append(cur)
        return res



# Morris Traversal
class Solution:
    def bstFromPreorder(self, pre_order: List[int]) -> TreeNode:
        root = current = None
        for val in pre_order:
            node = TreeNode(val)
            if current is not None:
                if node.val < current.val:
                    node.right = current
                    current.left = current = node
                else:
                    while current.right is not None and node.val > current.right.val:
                        current.right, current = None, current.right

                    node.right = current.right
                    current.right = current = node
            else:
                root = current = node

        while current.right is not None:                 #比如 [8,5,1]      #    8 
            current.right, current = None, current.right                   #   /  
                                                                          #   5 
                                                                         # /     \ 
        return root                                                     # 1        8 
                                                                        #   \ 
                                                                        #    5    current = 1, recursive remove 1 from 5, remove 8 from 5

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def bstFromPreorder(self, preorder: List[int]) -> TreeNode:
        if not preorder:
            return None 
        root = node = TreeNode(preorder[0])
        for v in preorder[1:]:
            cur = TreeNode(v)
            if node.val > v:
                cur.right = node
                node.left = node = cur  #cannot write as node = node.left = cur,  left associative node = node.left then node.left =cur 
                 # 这样node 先等于node.left了,  
            else:
                while node.right and node.right.val < v:
                    node.right, node = None, node.right
                cur.right = node.right
                node.right = node = cur #cannot write as node = node.right = cur
                
        while node.right:
            node.right, node = None, node.right
        return root