"""
4. Median of Two Sorted Arrays
"""
"""
O(log(min(n1,n2)))
ps.2 Why n2 >= n1? Because I have to make sure j is non-nagative since 0 <= i <= n1 and j = (n2 + n1 + 1)/2 - i.
 If n2 < n1 , then j may be nagative, that will lead to wrong result.
 if n2 < n1:  j = (n2 + n1 + 1)/2 - n1 < 2n1/2 - n1 = 0  or  j = (n2+n1+1)/2 - 0 = mid(n1,n2) 大于n2的长度， 可能j为负(当i介于n1, n2长度之间)。可能j大于n2的长度
 但是假如 n2 > n1： j = (n2 + n1 + 1)/2 - n1 > 2n1/n1 > 0 (j肯定大于0),   j = (n2 + n1 + 1)/2 - 0 = mid(n1,n2) < n2（小于nums2的长度)

如果n2 < n1:  
    比如 nums1 = [2], nums2 = [], i = 0, j = (n2 + n1 + 1)/2 - n1 = 2/2 - 0 = 1, 1是大于j的长度的

 n1 <= n2, i < m ==> j = (n1+n2+1)/2 - i > (n1+n2+1)/2 - m >= (2*n1+1)/2 - m >= 0    
 n1 <= n2, i > 0 ==> j = (n1+n2+1)/2 - i < (n1+n2+1)/2 <= (2*n2+1)/2 <= n

"""

class Solution:
    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        n1, n2 = len(nums1), len(nums2)
        if n1 > n2: return self.findMedianSortedArrays(nums2, nums1)
        half = math.ceil((n1+n2)/2)
        l, r = 0, n1
        while l<=r:
            i = (l+r)>>1
            j = half - i

            if i>0 and nums1[i-1]>nums2[j]: r = i-1
            elif i<n1 and nums1[i]<nums2[j-1]: l = i+1
            else:        
                leftmax = max(-10000000 if i==0 else nums1[i-1], -100000 if j==0 else nums2[j-1])
                if (n1+n2)&1:
                    return leftmax
                rightmin = min(10**10 if i==n1 else nums1[i], 10**10 if j == n2 else nums2[j] )
                return (leftmax + rightmin)/2

    
class Solution:
    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        n1, n2 = len(nums1), len(nums2)
        if n1 > n2: return self.findMedianSortedArrays(nums2, nums1)
        half = math.ceil((n1+n2)/2)
        l, r = 0, n1
        while l<r:
            i = (l+r)>>1
            j = half - i
            if nums1[i]<=nums2[j-1]: l = i+1 #保证i一定小于n1
            else: r = i
        i = l
        j = half - i
        leftmax = max(-10000000 if i==0 else nums1[i-1], -100000 if j==0 else nums2[j-1])
        if (n1+n2)&1:
            return leftmax
        rightmin = min(10**10 if i==n1 else nums1[i], 10**10 if j == n2 else nums2[j] )
        return (leftmax + rightmin)/2



"""
O(log(n1+n2))
"""
class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        l = len(nums1) + len(nums2)
        if l % 2 == 1:
            return self.kth(nums1, nums2, l // 2)
        else:
            return (self.kth(nums1, nums2, l // 2) + self.kth(nums1, nums2, l // 2 - 1)) / 2.   

    def kth(self, a, b, k):
        if not a:
            return b[k]
        if not b:
            return a[k]
        ia, ib = len(a) // 2 , len(b) // 2
        ma, mb = a[ia], b[ib]

        # when k is bigger than the sum of a and b's median indices 
        if ia + ib < k:
            # if a's median is bigger than b's, b's first half doesn't include k
            if ma > mb:
                return self.kth(a, b[ib + 1:], k - ib - 1)
            else:
                return self.kth(a[ia + 1:], b, k - ia - 1)
        # when k is smaller than the sum of a and b's indices
        else:
            # if a's median is bigger than b's, a's second half doesn't include k
            if ma > mb:
                return self.kth(a[:ia], b, k)
            else:
                return self.kth(a, b[:ib], k)


class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        a, b = sorted((nums1, nums2), key=len)
        m, n = len(a), len(b)
        after = (m + n - 1) // 2
        lo, hi = 0, m
        while lo < hi:
            i = (lo + hi) // 2
            if after-i-1 < 0 or a[i] >= b[after-i-1]:
                hi = i
            else:
                lo = i + 1
        i = lo
        nextfew = sorted(a[i:i+2] + b[after-i:after-i+2])
        return (nextfew[0] + nextfew[1 - (m+n)%2]) / 2.0


class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        a, b = sorted((nums1, nums2), key=len)
        m, n = len(a), len(b)
        after = (m + n - 1) // 2
        class Range:
            def __getitem__(self, i):
                return after-i-1 < 0 or a[i] >= b[after-i-1]
        i = bisect.bisect_left(Range(), True, 0, m)
        nextfew = sorted(a[i:i+2] + b[after-i:after-i+2])
        return (nextfew[0] + nextfew[1 - (m+n)%2]) / 2.0