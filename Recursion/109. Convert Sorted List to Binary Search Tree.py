"""
109. Convert Sorted List to Binary Search Tree

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example:

Given the sorted linked list: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5

"""


# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def sortedListToBST(self, head,tail = None):
        """
        :type head: ListNode
        :rtype: TreeNode
        """
        if head == tail: return None
        if head.next == tail: return TreeNode(head.val)
        fast = head
        slow = head
        while fast.next!=tail and fast.next.next!=tail:
            fast = fast.next.next
            slow = slow.next
        root = TreeNode(slow.val)
        root.left = self.sortedListToBST(head,slow)
        root.right = self.sortedListToBST(slow.next,tail)
        return root



class Solution:
    def sortedListToBST(self, head):
        """
        :type head: ListNode
        :rtype: TreeNode
        """
        if head is None: return None
        if head.next is None: return TreeNode(head.val)
        fast = head.next.next
        slow = head
        while fast and fast.next:
            fast = fast.next.next
            slow = slow.next
        root = TreeNode(slow.next.val)
        r = slow.next.next
        slow.next = None
        root.left = self.sortedListToBST(head)
        root.right = self.sortedListToBST(r)
        return root


class Solution:
    def sortedListToBST(self, head):
        """
        :type head: ListNode
        :rtype: TreeNode
        """
        def getTree(s, e):
            if s>e: return None
            mid = (s+e)>>1
            left = getTree(s,mid-1)
            root = TreeNode(self.head.val)
            self.head = self.head.next
            root.left = left
            root.right = getTree(mid+1,e)
            return root
        cur = head
        self.head = head
        n = 0
        while cur: 
            n+=1
            cur = cur.next
        return getTree(0,n-1)