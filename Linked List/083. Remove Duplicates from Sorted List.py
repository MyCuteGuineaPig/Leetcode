"""
83. Remove Duplicates from Sorted List

Example 1:

Input: 1->1->2
Output: 1->2
Example 2:

Input: 1->1->2->3->3
Output: 1->2->3
"""
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None
class Solution:
    def deleteDuplicates(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        cur = dummy = ListNode(0)
        dummy.next = head 
        while cur.next and cur.next.next:
            while cur.next.next and cur.next.val == cur.next.next.val:
                 cur.next.next = cur.next.next.next
            cur = cur.next
        return dummy.next

class Solution:
    def deleteDuplicates(self, head):
        res = head
        while head and head.next:
            while head.next and head.val == head.next.val:
                head.next = head.next.next
            head = head.next
        return res