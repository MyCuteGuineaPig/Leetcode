class Solution:
    def isSubPath(self, head: ListNode, root: TreeNode) -> bool:
        if not head and not root:
            return True
        if not head or not root:
            return False
        def helper(hd, cur):
            #print("start ", hd, cur)
            if not hd and not cur:
                return True
            if not hd or not cur or hd.val != cur.val:
                return False

            return not hd.next or helper(hd.next, cur.left) or helper(hd.next, cur.right)
        def dfs(hd, cur):
            if not cur:
                return False 
            if hd.val == cur.val and helper(hd, cur):
                return True 
            return dfs(hd, cur.left) or dfs(hd, cur.right)
        return dfs(head, root)