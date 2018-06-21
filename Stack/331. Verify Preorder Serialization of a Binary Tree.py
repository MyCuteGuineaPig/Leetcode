""""
331. Verify Preorder Serialization of a Binary Tree

Example 1:

Input: "9,3,4,#,#,1,#,#,2,#,6,#,#"
Output: true
Example 2:

Input: "1,#"
Output: false
Example 3:

Input: "9,#,#,1"
Output: false
"""

class Solution:
    def isValidSerialization(self, preorder):
        stk = [1]
        if preorder == '#': return True
        for i in preorder.split(','):
            if not stk: return False
            if i != '#':
                stk.append(2)
            else:     
                if stk[-1] == 2: stk[-1]-=1
                else:
                    while stk and stk[-1] == 1:
                        stk.pop()
                    if stk: stk[-1] -=1
        return not stk


class Solution:
    def isValidSerialization(self, preorder):
        degree = -1
        for i in preorder.split(','):
            degree += 1
            if degree > 0: return False
            if i != '#': 
                degree -= 2
        return degree == 0