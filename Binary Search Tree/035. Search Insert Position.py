class Solution:
    def balanceBST(self, root: TreeNode) -> TreeNode:
        cnt = []
        def f(c):
            if not c:
                return 
            f(c.left)
            cnt.append(c.val)
            f(c.right)
        f(root)
        def con(i, j):
            if i > j: return None
            if i == j:
                return TreeNode(cnt[i])
            mid = (i+j)//2
            cur = TreeNode(cnt[mid])
            cur.left = con(i, mid-1)
            cur.right = con(mid+1, j)
            return cur
        return con(0, len(cnt)-1)