"""
24. Swap Nodes in Pairs

Given 1->2->3->4, you should return the list as 2->1->4->3.
"""
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None


#提出下一个
class Solution:
    def swapPairs(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        cur = dummy = ListNode(0)
        dummy.next = head
        while cur.next and cur.next.next:
            temp = cur.next
            cur.next = cur.next.next #断下一个和下下一个
            temp.next = cur.next.next
            cur.next.next = temp
            cur = temp
        return dummy.next

#提出下下一个
class Solution:
    def swapPairs(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        cur = dummy = ListNode(0)
        dummy.next = head
        while cur.next and cur.next.next:
            temp = cur.next.next 
            cur.next.next = cur.next.next.next
            temp.next = cur.next
            cur.next = temp
            cur = cur.next.next
        return dummy.next


#换value的
class Solution:
    def swapPairs(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        node = head
        while node and node.next :
            node.val, node.next.val = node.next.val, node.val
            node = node.next.next
        return head
