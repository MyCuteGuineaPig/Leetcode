"""
350. Intersection of Two Arrays II

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].
"""

# binary Search
class Solution(object):
    def intersect(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        nums1.sort()
        nums2.sort()
        l, n = 0, len(nums2)
        res = []
        for i in nums1:
            l = bisect.bisect_left(nums2,i, lo = l)
            if l < n and nums2[l] == i:
                res+=[i]
                l+=1
        return res


# two pointer
class Solution(object):
    def intersect(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        nums1.sort()
        nums2.sort()
        l, n1, r, n2 = 0, len(nums1),0, len(nums2)
        res = []
        while l < n1 and r < n2:
            if nums1[l] == nums2[r]:
                res.append(nums1[l])
                l+=1 
                r+=1
            elif nums1[l]<nums2[r]:
                l+=1
            else:
                r+=1
        return res


class Solution:
    def intersect(self, nums1, nums2):
        a, b = map(collections.Counter, (nums1, nums2))
        return list((a & b).elements())  #是双方都有的key的, (a & b)还是counter 