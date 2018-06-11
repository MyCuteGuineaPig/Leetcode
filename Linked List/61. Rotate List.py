"""
61. Rotate List

Example 1:

Input: 1->2->3->4->5->NULL, k = 2
Output: 4->5->1->2->3->NULL
Explanation:
rotate 1 steps to the right: 5->1->2->3->4->NULL
rotate 2 steps to the right: 4->5->1->2->3->NULL
Example 2:

Input: 0->1->2->NULL, k = 4
Output: 2->0->1->NULL
Explanation:
rotate 1 steps to the right: 2->0->1->NULL
rotate 2 steps to the right: 1->2->0->NULL
rotate 3 steps to the right: 0->1->2->NULL
rotate 4 steps to the right: 2->0->1->NULL


"""
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def rotateRight(self, head, k):
        """
        :type head: ListNode
        :type k: int
        :rtype: ListNode
        """
        if head is None or head.next is None or k == 0: return head
        length = 1
        lastone = head
        while lastone.next: 
            lastone, length = lastone.next, length+1
        forward = length - k%length
        if forward == length: return head
        cur = head 
        for i in range(1,forward):
            cur = cur.next
        temp = cur.next 
        cur.next = None #断链
        lastone.next = head #让尾和头相连
        return temp


class Solution:
    def rotateRight(self, head, k):
        """
        :type head: ListNode
        :type k: int
        :rtype: ListNode
        """
        if head is None or head.next is None or k == 0: return head
        length = 1
        lastone = head
        while lastone.next: 
            lastone, length = lastone.next, length+1
        forward = length - k%length
        if forward == length: return head
        lastone.next = head
        for i in range(0,forward):
            lastone = lastone.next
        temp = lastone.next 
        lastone.next = None #断链
        return temp