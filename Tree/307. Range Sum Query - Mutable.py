"""
307. Range Sum Query - Mutable

"""

class BIT:
    def __init__(self, arr):
        self.tree = [0]*(len(arr)+1)
        self.arr = arr
        self.size = len(arr)
        for i, v in enumerate(arr, 1):
            self.update(v,i)
    
    def update(self,delta, index):
        while index <= self.size: 
            self.tree[index] += delta
            index += (index & (-index))
    
    def query(self, index):
        sum_ = 0
        while index > 0: 
           sum_ += self.tree[index]
           index -= index & (-index)
        return sum_

class NumArray:
    def __init__(self, nums):
        self.bit = BIT(nums)

    def update(self, i, val):
        self.bit.update(val - self.bit.arr[i], i+1)
        self.bit.arr[i] = val
        

    def sumRange(self, i, j):
        return self.bit.query(j+1) - self.bit.query(i)





## SegmentTree
class SegmentTreeNode:
    def __init__(self, start, end, val):
        self.start = start
        self.end = end
        self.val = val
        self.left = None
        self.right = None

class SegmentTree:
    def __init__(self, arr):
        self.root = self.buildTree(0, len(arr)-1, arr)
    
    def buildTree(self, s, e, arr):
        if s > e : return None
        if s == e:
            return SegmentTreeNode(s, e, arr[s])
        node = SegmentTreeNode(s,e,0)
        mid = (s+e)//2 
        node.left = self.buildTree(s, mid, arr)
        node.right = self.buildTree(mid+1, e, arr)
        node.val = node.left.val + node.right.val
        return node 
    
    def updateTree(self, node, i, val):
        if i < node.start or i > node.end: 
            return 0
        if i == node.start == node.end:
            diff = val - node.val
            node.val = val
            return diff
        mid = (node.start + node.end)//2
        if i <= mid:        
            diff = self.updateTree(node.left, i, val)
        else:
            diff = self.updateTree(node.right, i, val)
        node.val += diff
        return diff
    
    def query(self, node, s, e):
        if s > node.end or e < node.start: return 0
        if node.start >= s and node.end <= e :
            return node.val
        mid = (node.start + node.end)//2
        return self.query(node.left, s, e) + self.query(node.right, s, e)

class NumArray:
    def __init__(self, nums):
        self.sgt = SegmentTree(nums)

    def update(self, i, val):
        self.sgt.updateTree(self.sgt.root, i, val)

    def sumRange(self, i, j):
        return self.sgt.query(self.sgt.root, i, j)




#Segment Tree Solution2
class Node:
    def __init__(self, left, right, total):
        self.left  = left
        self.right = right
        self.total = total
    
class NumArray:

    def __init__(self, nums):
        """
        :type nums: List[int]
        """
        if not nums: return 
        def build_tree(start, end):
            if start == end:
                return Node(None, None, nums[end])
            left  = build_tree(start, (start + end) // 2)
            right = build_tree((start + end) // 2 + 1, end)
            return Node(left, right, left.total + right.total)
        self.last_index = len(nums) - 1
        self.tree = build_tree(0, self.last_index)
        
    
    def update(self, i, val):
        """
        :type i: int
        :type val: int
        :rtype: void
        """
        def find(node, start, end):
            if not node.left and not node.right:
                node.total = val
                return
            mid = (start + end) // 2
            if i <= mid:
                find(node.left, start, mid)
            else:
                find(node.right, mid + 1, end)
            node.total = node.left.total + node.right.total
        return find(self.tree, 0, self.last_index)
        

    def sumRange(self, i, j):
        """
        :type i: int
        :type j: int
        :rtype: int
        """
        def get_sum(node, start, end):
            if start >= i and end <= j:
                return node.total
            if end < i or start > j:
                return 0
            mid = (start + end) // 2
            return get_sum(node.left, start, mid) + get_sum(node.right, mid + 1, end)
        return get_sum(self.tree, 0, self.last_index)




class NumArray(object):
    def __init__(self, nums):
        self.update = nums.__setitem__
        self.sumRange = lambda i, j: sum(nums[i:j+1])