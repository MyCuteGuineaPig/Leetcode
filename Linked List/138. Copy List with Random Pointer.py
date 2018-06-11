"""
138. Copy List with Random Pointer
"""
# Definition for singly-linked list with a random pointer.
# class RandomListNode(object):
#     def __init__(self, x):
#         self.label = x
#         self.next = None
#         self.random = None
class Solution(object):
    def copyRandomList(self, head):
        """
        :type head: RandomListNode
        :rtype: RandomListNode
        """
        if head is None: return None
        temp = head 
        while temp:
            nxt = temp.next 
            temp.next = RandomListNode(temp.label)
            temp.next.next = nxt
            temp = nxt
        temp = head
        while temp:
            if temp.random:
                temp.next.random = temp.random.next 
            temp = temp.next.next
            
        res = head.next
        cur = res
        origin = head
        while origin: #不能是cur.next 比如list只有一个元素，然后cur.next 为0，但是还没断链
            origin.next = origin.next.next
            if cur.next:
                cur.next = cur.next.next
            origin  = origin.next
            cur = cur.next
        return res 