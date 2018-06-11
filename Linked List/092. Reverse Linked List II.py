"""
92. Reverse Linked List II


Input: 1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL

"""

#提取head.next
class Solution:
    def reverseBetween(self, head, m, n):
        """
        :type head: ListNode
        :type m: int
        :type n: int
        :rtype: ListNode
        """
        cur = dummy = ListNode(0)
        dummy.next = head 
        i = 1
        while i<m: 
            cur = cur.next
            i += 1
        head = cur.next
        while i<n:
            temp = head.next
            head.next = head.next.next
            temp.next = cur.next 
            cur.next = temp
            i+=1
        return dummy.next
        
#提取cur.next 

class Solution:
    def reverseBetween(self, head, m, n):
        """
        :type head: ListNode
        :type m: int
        :type n: int
        :rtype: ListNode
        """
        cur = dummy = ListNode(0)
        dummy.next = head 
        i = 1
        while i<m: 
            cur = cur.next
            i += 1
        head = cur.next
        while i<n:
            temp = cur.next
            cur.next = head.next
            head.next = head.next.next
            cur.next.next = temp
            i+=1
        return dummy.next

#直接把head 变为node起点
class Solution:
    def reverseBetween(self, head, m, n):
        """
        :type head: ListNode
        :type m: int
        :type n: int
        :rtype: ListNode
        """
        cur = dummy = ListNode(0)
        dummy.next = head 
        i = 1
        while i<m: 
            cur = cur.next
            i += 1
        head = cur.next
        start = None
        while i<=n:
            temp = head.next
            head.next = start
            start = head
            head =temp
            i+=1
        cur.next.next = head  #把start的结尾和接下来的node 相连，因为cur.next 被reverse了，cur.next变成最后一个了
        cur.next = start  #把start 提上来
        return dummy.next
