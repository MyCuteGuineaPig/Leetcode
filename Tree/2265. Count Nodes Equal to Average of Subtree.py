class Solution:
    def averageOfSubtree(self, root: Optional[TreeNode]) -> int:
        result = 0
		
        def traverse(node):
            nonlocal result
            
            if not node:
                return 0, 0
            
            left_sum, left_count = traverse(node.left)
            right_sum, right_count = traverse(node.right)
            
            s = node.val + left_sum + right_sum
            c = 1 + left_count + right_count
            
            if s // c == node.val:
                result += 1
            
            return s, c
        
        traverse(root)
        
        return result