class Solution:
    def minAbsoluteSumDiff(self, nums1: List[int], nums2: List[int]) -> int:
        v = [i for i in nums1]
        v.sort()
        gap = float('-inf')
        for ind, (i, j) in enumerate(zip(nums1, nums2)):
            k = bisect.bisect_right(v, j)
            if k < len(nums1):
                gap = max(gap, abs(i-j) - abs(j-v[k]))
            if k > 0:
                gap = max(gap, abs(i-j) - abs(j-v[k-1]))
        return (sum(abs(i-j) for i, j in zip(nums1, nums2)) - gap)%(10**9 + 7)