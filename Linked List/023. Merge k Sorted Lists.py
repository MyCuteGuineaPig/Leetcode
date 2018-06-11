"""
23. Merge k Sorted Lists

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None
class Solution:
    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        def merge(l1, l2):
            cur = dummy = ListNode(0)
            while l1 and l2:
                if l1.val < l2.val:
                    cur.next, l1= l1, l1.next
                else:
                    cur.next, l2= l2, l2.next
                cur = cur.next
            cur.next = l1 if l1 else l2
            return dummy.next
        l = 0; r = len(lists)-1
        if r<0: return None            
        while r>0:
            if l>=r:
                l = 0
            lists[l] = merge(lists[l], lists[r])
            l+=1
            r-=1
        return lists[0]


# Time:  O(nlogk)
# Space: O(logk)
# Divide and Conquer solution.
class Solution:      
    """
    比如size =  5, 
    1. split(0,2), split(3,4)
    2. split(0,1), split(2,2)
    3. merge(0, 1), return lists[2] 
    4. merge(0, 2)
    5. split(3,3), split(4,4)
    6. merge(3,4)
    7. merge((0,2),(3,4))
    
    """
    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        def split(begin, end):
            if begin>end: return None
            elif begin == end: return lists[begin]
            mid = (begin+end)>>1
            return merge(split(begin,mid),split(mid+1,end))

        def merge(l1, l2):
            cur = dummy = ListNode(0)
            while l1 and l2:
                if l1.val < l2.val:
                    cur.next, l1= l1, l1.next
                else:
                    cur.next, l2= l2, l2.next
                cur = cur.next
            cur.next = l1 if l1 else l2
            return dummy.next
        return split(0,len(lists)-1)

#heap 不能直接放listnode， 没法直接比较

import heapq

class Solution:
    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        
        # iterators through each list
        its = [l for l in lists]

        # sorted by minimum node value. each
        # elm is a tuple (val, list_id)
        min_heap = []
        k = len(lists)

        for list_id in range(k):

            it = lists[list_id]
            while it:

                heapq.heappush(min_heap, (it.val, list_id))
                it = it.next 

        sorted_head = None
        sorted_it = sorted_head

        while min_heap:

            # next min elm
            list_id = heapq.heappop(min_heap)[1]
            next_node = its[list_id]
            its[list_id] = its[list_id].next

            # first node in sorted list
            if not sorted_head:
                sorted_head = next_node #初始化head

            else:
                sorted_it.next = next_node

            sorted_it = next_node

        return sorted_head

