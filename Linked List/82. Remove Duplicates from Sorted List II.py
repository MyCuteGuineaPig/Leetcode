"""
82. Remove Duplicates from Sorted List II


Example 1:

Input: 1->2->3->3->4->4->5
Output: 1->2->5
Example 2:

Input: 1->1->1->2->3
Output: 2->3
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
            value = cur.next.val
            if cur.next.next.val== value:
                cur.next = cur.next.next
                while cur.next and cur.next.val == value:
                    cur.next = cur.next.next
            else:
                cur = cur.next
        return dummy.next

class Solution:
    def deleteDuplicates(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        cur = dummy = ListNode(0)
        dummy.next = head
        while head and head.next:
            value = head.val
            if head.next.val == value:
                while head.next and head.next.val == value:
                    head.next = head.next.next
                cur.next = head.next
                head = head.next
            else:
                cur = cur.next
                head = head.next
        return dummy.next