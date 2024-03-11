class Solution:
    def minSum(self, nums1: List[int], nums2: List[int]) -> int:
        sa = sum(max(a, 1) for a in nums1)
        sb = sum(max(b, 1) for b in nums2)
        if sa < sb and nums1.count(0) == 0: return -1
        if sa > sb and nums2.count(0) == 0: return -1
        return max(sa, sb)