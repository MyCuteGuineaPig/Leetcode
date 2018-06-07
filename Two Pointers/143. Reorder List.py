"""
143. Reorder List

Example 1:

Given 1->2->3->4, reorder it to 1->4->2->3.
Example 2:

Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
"""

class Solution(object):
    def reorderList(self, head):
        """
        :type head: ListNode
        :rtype: void Do not return anything, modify head in-place instead.
        """
        if head is None or head.next is None: return
        slow = fast = head
        while fast.next and fast.next.next: #用fast.next 和 fast.next.next 原因是1-2-3-4-5-6, 让最后fast 停在5，slow停在3
            fast = fast.next.next
            slow = slow.next
        fast = slow.next
        while fast.next: #reverse
            beg = slow.next
            slow.next = fast.next
            fast.next = fast.next.next
            slow.next.next = beg
        prev = slow
        fast = slow
        slow = head
        while slow!=prev:
            nxt = slow.next
            slow.next = fast.next
            fast.next = fast.next.next
            slow.next.next = nxt
            slow = nxt

class Solution(object):
    def reorderList(self, head):
        """
        :type head: ListNode
        :rtype: void Do not return anything, modify head in-place instead.
        """
        if head is None or head.next is None: return
        slow = fast = head
        while fast.next and fast.next.next: #用fast.next 和 fast.next.next 原因是1-2-3-4-5-6, 让最后fast 停在5，slow停在3
            fast = fast.next.next
            slow = slow.next
        fast = slow.next
        slow.next = None
        head2 = None
        while fast: #reverse
            nxt = fast.next
            fast.next = head2#把之前的接在现在的后面
            head2 = fast
            fast = nxt
        fast = head2
        slow = head
        while slow and fast:
            next_front, next_back = slow.next, fast.next
            slow.next, fast.next = fast, next_front
            slow, fast = slow.next.next, next_back
        



class Solution(object):
    def reorderList(self, head):
        def split_list(head):
            slow, fast = head, head.next
            while fast and fast.next:
                slow, fast = slow.next, fast.next.next
            mid = slow.next
            slow.next = None
            return head, mid
        def reverse_list(head):
            last = None
            while head:
                tmp = head.next
                head.next = last
                last = head
                head = tmp
            return last
        def merge_list(front, back):
            head = front
            while front and back:
                next_front, next_back = front.next, back.next
                front.next, back.next = back, next_front
                front, back = next_front, next_back
            return head
        if head and head.next:
            head, mid = split_list(head)
            mid = reverse_list(mid)
            head = merge_list(head, mid)
        