"""
160. Intersection of Two Linked Lists

A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
"""

# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution(object):
    def getIntersectionNode(self, headA, headB):
        """
        :type head1, head1: ListNode
        :rtype: ListNode
        """
        pA, pB, endA, endB = headA, headB, True, True 
        while pA and pB:
            if pA == pB: return pA
            pA = pA.next 
            pB = pB.next
            if pA is None: 
                if endA:
                    pA = headB
                    endA = False
                else: break
            if pB is None: 
                if endB: 
                    pB = headA
                    endB = False
                else: break
        return None  



class Solution(object):
    def getIntersectionNode(self, headA, headB):
        """
        :type head1, head1: ListNode
        :rtype: ListNode
        """
        if headA is None or headB is None: return None
        pA, pB = headA, headB
        #这两个指针必然会相遇（有两种情况，一种是在交叉处相遇，另一种是到达各自链表的尾部（NULL））
        while pA != pB:
            pA = pA.next if pA else headB
            pB = pB.next if pB else headA
        return pA