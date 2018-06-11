"""
234. Palindrome Linked List


Example 1:

Input: 1->2
Output: false
Example 2:

Input: 1->2->2->1
Output: true
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def isPalindrome(self, head):
        """
        :type head: ListNode
        :rtype: bool
        """
        if head is None: return True
        rev = None
        slow = head; fast = head
        while fast and fast.next: 
            fast = fast.next.next
            nxt = slow.next
            slow.next = rev
            rev = slow
            slow = nxt
        fast = slow.next if fast else slow
        while fast and rev:
            if fast.val != rev.val: return False
            fast = fast.next
            rev = rev.next
        return True 

class Solution:
    def isPalindrome(self, head):
        """
        :type head: ListNode
        :rtype: bool
        """
        if head is None: return True
        cur = dummy = ListNode(0)
        dummy.next = head
        sl