class Codec:

    def serialize(self, root):
        def doit(node):
            if node:
                vals.append(str(node.val))
                doit(node.left)
                doit(node.right)
            else:
                vals.append('#')
        vals = []
        doit(root)
        return ' '.join(vals)

    def deserialize(self, data):
        def doit():
            val = next(vals)
            if val == '#':
                return None
            node = TreeNode(int(val))
            node.left = doit()
            node.right = doit()
            return node
        vals = iter(data.split())
        return doit()
        
        
        
  class Codec:

    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        def help(root):
            if root:
                res.append(root.val)
                help(root.left)
                help(root.right)
            else:
                res.append("#")
            
        res = []
        help(root)
        return ','.join(str(i) for i in res)
        

    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """
        def help():
            if self.index >= len(data):
                return None 
            if data[self.index] == '#':
                self.index += 1
                return None
            tree = TreeNode(data[self.index])
            self.index+=1 
            tree.left = help()
            tree.right = help()
            return tree
            
        data = data.split(',')
        self.index = 0
        return help()
