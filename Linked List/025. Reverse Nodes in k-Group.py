"""
25. Reverse Nodes in k-Group


Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

#提取下一个
class Solution:
    def reverseKGroup(self, head, k):
        """
        :type head: ListNode
        :type k: int
        :rtype: ListNode
        """
        cur = dummy = ListNode(0)
        dummy.next = head
        while head: 
            length = 0
            end = head
            while end and length<k: 
                end, length = end.next, length+1
            if length<k: break
            while head.next!= end:
                temp = head.next
                head.next = head.next.next
                temp.next = cur.next 
                cur.next = temp
            cur = head #等于这个循环后的最后一个值
            head = head.next  #head是这个循环最后一个值
        return dummy.next


class Solution:
    def reverseKGroup(self, head, k):
        """
        :type head: ListNode
        :type k: int
        :rtype: ListNode
        """
        cur = dummy = ListNode(0)
        dummy.next = head
        while head: 
            length = 0
            end = head
            while end and length<k: 
                end, length = end.next, length+1
            if length<k: break
            while head.next!= end:
               temp = cur.next
               cur.next = head.next
               head.next = head.next.next
               cur.next.next = temp
            cur = head #等于这个循环后的最后一个值
            head = head.next  #head是这个循环最后一个值
        return dummy.next