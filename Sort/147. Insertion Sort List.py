"""
147. Insertion Sort List


"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

"""
complexity: O(n^2) 
space O(1)
"""
class Solution:
    def insertionSortList(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        newhead = ListNode(0)
        newhead.next = head
        prev = newhead
        while head:
            if head.next and head.next.val < head.val:
                while prev.next and prev.next.val<head.next.val:
                    prev = prev.next
                temp = prev.next
                prev.next = head.next
                head.next = head.next.next
                prev.next.next = temp
                prev = newhead
            else:
                head = head.next
        return newhead.next


class Solution:
    def insertionSortList(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        cur = dummy = ListNode(0)
        while head:
            if cur and cur.val > head.val:
                cur = dummy
            while cur.next and cur.next.val < head.val:
                cur = cur.next
            cur.next, cur.next.next, head = head, cur.next, head.next 
        return dummy.next

"""
complexity: O(nlogn) 
space O(n)
"""
class Solution:
    def insertionSortList(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        node = head
        num_arr = []

        while node:
            num_arr.append(node.val)
            node = node.next

        num_arr.sort()

        head = ListNode(0)
        node = head

        for num in num_arr:
            new_node = ListNode(num)
            node.next = new_node
            node = node.next

        return head.next




