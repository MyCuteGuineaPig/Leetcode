/*

1028. Recover a Tree From Preorder Traversal
We run a preorder depth first search on the root of a binary tree.

At each node in this traversal, we output D dashes (where D is the depth of this node), 
then we output the value of this node.  (If the depth of a node is D, the depth of its immediate child is D+1.  
The depth of the root node is 0.)

If a node has only one child, that child is guaranteed to be the left child.

Given the output S of this traversal, recover the tree and return its root.

 

Example 1:



Input: "1-2--3--4-5--6--7"
Output: [1,2,5,3,4,6,7]
Example 2:


Input: "1-2--3---4-5--6---7"
Output: [1,2,5,3,null,6,null,4,null,7]
 

Example 3:


Input: "1-401--349---90--88"
Output: [1,401,null,349,88,90]
 

Note:

The number of nodes in the original tree is between 1 and 1000. 
Each node will have a value between 1 and 10^9.

*/


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def recoverFromPreorder(self, S: str) -> TreeNode:
        if not S: 
            return None
        
        def find_level(start):
            level = 0
            for level, cur in enumerate(S[start:]):
                if cur!= '-':
                    return level, level + start
        
        def find_val(start):
            j = start
            for i,cur in enumerate(S[start:],start):
                if cur == '-':
                    return int(S[start:i]), i
            return int(S[start:]), len(S)
        
        val, index = find_val(0)
        stk = [(0,TreeNode(val))]
        while index < len(S):
            level, index = find_level(index)
            val, index = find_val(index)
            newNode = TreeNode(val)
            left = True
            while level <= stk[-1][0]:
                stk.pop()
                left = False
            if left:
                stk[-1][1].left = newNode
            else:
                stk[-1][1].right = newNode
            stk.append((level,newNode))
        return stk[0][1]
                
#Without Level, use stack as level
class Solution:
    def recoverFromPreorder(self, S: str) -> TreeNode:
        if not S: 
            return None
        
        def find_level(start):
            level = 0
            for level, cur in enumerate(S[start:]):
                if cur!= '-':
                    return level, level + start
        
        def find_val(start):
            j = start
            for i,cur in enumerate(S[start:],start):
                if cur == '-':
                    return int(S[start:i]), i
            return int(S[start:]), len(S)
        
        val, index = find_val(0)
        stk = [TreeNode(val)]
        while index < len(S):
            level, index = find_level(index)
            val, index = find_val(index)
            newNode = TreeNode(val)
            left = True
            while level < len(stk):
                stk.pop()
                left = False
            if left:
                stk[-1].left = newNode
            else:
                stk[-1].right = newNode
            stk.append(newNode)
        return stk[0]            
                
            
class Solution:
    def recoverFromPreorder(self, S):
        stack, i = [], 0
        while i < len(S):
            level, val = 0, ""
            while i < len(S) and S[i] == '-':
                level, i = level + 1, i + 1
            while i < len(S) and S[i] != '-':
                val, i = val + S[i], i + 1
            while len(stack) > level:
                stack.pop()
            node = TreeNode(val)
            if stack and stack[-1].left is None:
                stack[-1].left = node
            elif stack:
                stack[-1].right = node
            stack.append(node)
        return stack[0]
