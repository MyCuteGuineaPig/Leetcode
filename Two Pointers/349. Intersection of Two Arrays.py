"""
349. Intersection of Two Arrays

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].
"""
# binary search
class Solution(object):
    def intersection(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        nums1.sort()
        nums2.sort()
        res = []
        left = 0
        for i in nums1:
            left = bisect.bisect_left(nums2,i,lo=left)
            if left< len(nums2) and nums2[left] == i:
                res.append(i)
                left = bisect.bisect_right(nums2,i,lo=left)
        return res
        

class Solution(object):
    def intersection(self, nums1, nums2):
        return list(set(nums1) & set(nums2))
            

# Two pointer
class Solution(object):
    def intersection(self, nums1, nums2):
        nums1.sort()
        nums2.sort()
        res = []
        l, r = 0, 0
        while l<len(nums1) and r < len(nums2):
            if nums1[l] == nums2[r]:
                if not res or res[-1]!=nums1[l]:
                    res+=[nums1[l]]
                l+=1
                r+=1
            elif nums1[l] < nums2[r]:
                l+=1
            else:
                r+=1
        return res