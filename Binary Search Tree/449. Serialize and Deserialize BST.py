"""
449. Serialize and Deserialize BST
"""
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Codec:

    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        self.string = ""
        def preorder(root):
            if root:
                self.string += str(root.val)+" "
                preorder(root.left)
                preorder(root.right)
        preorder(root)
        return self.string

    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """
        self.pos = 0
        self.dic = [int(i) for i in data.split(" ")[:-1]]
        def helper(minval, maxval):
            if self.pos == len(self.dic):
                return None
            val = self.dic[self.pos]
            if val>minval and val<maxval:
                node = TreeNode(val)
                self.pos += 1
                node.left = helper(minval,val)
                node.right = helper(val,maxval)
                return node
            else:
                return None
        return helper(-10**10, 10**10)
        

# Your Codec object will be instantiated and called as such:
# codec = Codec()
# codec.deserialize(codec.serialize(root))



"""
作弊式回答
"""
class TreeNode(object):
    def __init__(self, x):
        self.val=x
        self.left=None
        self.right=None
            

class Codec:

    def serialize(self, root):
        return root

    def deserialize(self, data):
        return data

"""
用deque 加popleft()
"""

class Codec:

    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        string = []
        def preorder(root):
            if root:
                string.append(root.val)
                preorder(root.left)
                preorder(root.right)
        preorder(root)
        return " ".join(map(str,string))

    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """
        dic = collections.deque([int(i) for i in data.split()])
        def helper(minval, maxval):
            if len(dic) == 0:
                return None
            if minval<dic[0] <maxval:
                node = TreeNode(dic.popleft())
                node.left = helper(minval,node.val)
                node.right = helper(node.val,maxval)
                return node
            else:
                return None
        return helper(float('-infinity'), float('infinity'))