"""
652. Find Duplicate Subtrees

Example 1:

        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
The following are two duplicate subtrees:

      2
     /
    4
and

    4

"""
#Memory O(n), Speed O(n)
class Solution:
    def findDuplicateSubtrees(self, root: TreeNode) -> List[TreeNode]:
        def getid(root):
            if root:
                id = treeid[root.val, getid(root.left), getid(root.right)] #如果没有返回值, 返回None
                trees[id].append(root)
                return id
        trees = collections.defaultdict(list)
        treeid = collections.defaultdict()
        treeid.default_factory = treeid.__len__
        getid(root)
        return [root[0] for root in trees.values() if root[1:]]


class Solution:
    def findDuplicateSubtrees(self, root):
        """
        :type root: TreeNode
        :rtype: List[TreeNode]
        """
        dic = collections.defaultdict(int)
        res = []
        def helper(root):
            if not root: return ""
            out = "{}({})({})".format(root.val, helper(root.left), helper(root.right))
            if dic[out] == 1:
                res.append(root)
            dic[out] += 1
            return out
        helper(root)
        return res

class Solution:
    def findDuplicateSubtrees(self, root):
        paths = collections.defaultdict(list)
        def serialize(root):
            if not root:
                return "#"
            path = "{0} {1} {2}".format(root.val, serialize(root.left), serialize(root.right))
            paths[path].append(root)
            return path
        
        serialize(root)
        
        return [v[0] for k,v in paths.items() if len(v) > 1]


    
class Solution:
    def findDuplicateSubtrees(self, root):
        from hashlib import sha256
        def hash_(x):
            S = sha256()
            S.update(x)
            return S.hexdigest()

        def merkle(node):
            if not node:
                return '#'
            m_left = merkle(node.left)
            m_right = merkle(node.right)
            node.merkle = hash_(m_left + str(node.val) + m_right)
            count[node.merkle].append(node)
            return node.merkle

        count = collections.defaultdict(list)
        merkle(root)
        return [nodes.pop() for nodes in count.values() if len(nodes) >= 2]


class Solution:
    def findDuplicateSubtrees(self, root):
        def trv(root):
            if not root: return "null"
            struct = "%s,%s,%s" % (str(root.val), trv(root.left), trv(root.right))
            nodes[struct].append(root)
            return struct
        
        nodes = collections.defaultdict(list)
        trv(root)
        return [nodes[struct][0] for struct in nodes if len(nodes[struct]) > 1]
