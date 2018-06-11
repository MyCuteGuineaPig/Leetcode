"""
445. Add Two Numbers II

Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def addTwoNumbers(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        stk1,  stk2 = [], []
        while l1: 
            stk1.append(l1.val)
            l1 = l1.next 
        while l2:
            stk2.append(l2.val)
            l2 = l2.next
        carry = 0
        head = None
        while stk1 or stk2 or carry:
            if stk1:
                carry+=stk1[-1]
                stk1.pop()
            if stk2: 
                carry += stk2[-1]
                stk2.pop()
            node = ListNode(carry%10)
            carry = carry // 10
            node.next = head
            head = node 
        return head

class Solution:
    def addTwoNumbers(self, l1, l2):  #python 可以处理大的int, C++ 不行
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        x1, x2 = 0, 0
        while l1:
            x1 = x1*10+l1.val
            l1 = l1.next
        while l2:
            x2 = x2*10+l2.val
            l2 = l2.next
        x = x1 + x2
        
        dummyhead = ListNode(0)
        if x == 0: return dummyhead 
        while x:
            v, x = x%10, x//10
            # 倒退填充
            dummyhead.next, dummyhead.next.next = ListNode(v), dummyhead.next
            
        return dummyhead.next

class Solution:
    def addTwoNumbers(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        m1,m2=[],[]
        h=l1
        while h: 
            m1.append(str(h.val))
            h=h.next
        h=l2
        while h:
            m2.append(str(h.val))
            h=h.next
        m1=int("".join(m1))
        m2=int("".join(m2))
        m=str(m1+m2)
        h=ListNode(0)
        h0=h
        for i in range(len(m)):
            h.next=ListNode(int(m[i]))
            h=h.next
        return h0.next
        