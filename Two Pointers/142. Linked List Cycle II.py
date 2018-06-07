"""
142. Linked List Cycle II

"""
# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution(object):
    def detectCycle(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        slow = fast = head
        while fast and fast.next:
            fast = fast.next.next 
            slow = slow.next
            if slow == fast:
                fast = head
                while slow != fast:
                    slow = slow.next 
                    fast = fast.next 
                return slow
        return None