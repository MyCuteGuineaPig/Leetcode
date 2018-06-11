"""
328. Odd Even Linked List

Example 1:

Input: 1->2->3->4->5->NULL
Output: 1->3->5->2->4->NULL
Example 2:

Input: 2->1->3->5->6->4->7->NULL
Output: 2->3->6->7->1->5->4->NULL
"""
class Solution:
    def oddEvenList(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        if head is None or head.next is None: return head
        oddhead = odd = head
        evenhead = even = head.next 
        head = head.next.next
        while head:
            odd.next = head
            odd = odd.next
            if head.next:
                even.next = head.next
                even = even.next
                head = head.next.next            
            else: head = head.next 
        even.next = None
        odd.next = evenhead
        return oddhead


class Solution:
    def oddEvenList(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        if head is None or head.next is None: return head
        odd = head
        evenhead = even = head.next 
        while even and even.next:#even.next 有基数链没有断掉
           odd.next = odd.next.next
           even.next = even.next.next
           odd = odd.next
           even = even.next

        odd.next = evenhead
        return head


class Solution:
    def oddEvenList(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        if head is None or head.next is None: return head
        odd = head
        even = head.next 
        while even and even.next:
           evenhead = odd.next #奇数的结尾就是偶数的开始
           odd.next = even.next
           even.next = even.next.next#跳过下个已经添加的奇数
           odd.next.next = evenhead
           
           odd = odd.next
           even = even.next
        return head