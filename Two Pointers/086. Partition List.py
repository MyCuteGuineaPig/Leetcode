"""
86. Partition List

Example:

Input: head = 1->4->3->2->5->2, x = 3
Output: 1->2->2->4->3->5

"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def partition(self, head, x):
        """
        :type head: ListNode
        :type x: int
        :rtype: ListNode
        """
        node = ListNode(0)
        node.next = head
        slow = node
        fast = node
        while slow.next and slow.next.val < x:
            slow = slow.next
            fast = fast.next
        while fast.next:
            while fast.next and fast.next.val >= x:
                fast = fast.next
            if fast.next:
                nex = slow.next 
                slow.next = fast.next
                fast.next = fast.next.next
                slow.next.next = nex 
                slow = slow.next #向前进一位，保持原来顺序，否则顺序reverse了
        return node.next


class Solution:
    def partition(self, head, x):
        slow = slowhead = ListNode(0)
        fast = fasthead = ListNode(0)
        while head:
            if head.val < x:
                slow.next = head
                slow = slow.next
            else:
                fast.next = head
                fast = fast.next
            head = head.next
        fast.next = None
        slow.next = fasthead.next
        return slowhead.next