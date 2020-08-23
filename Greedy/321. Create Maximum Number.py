class Solution:
    def maxNumber(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[int]
        """
        def Generate(arr, k):
            stk = []
            n = len(arr)
            for i, v in enumerate(arr): 
                while stk and stk[-1]<v and k - len(stk) <  n - i:
                    stk.pop()
                if len(stk) < k:
                    stk.append(v)
            return stk
        
        def isGreater(arr1, arr2, i, j):
            while i<len(arr1) and j < len(arr2) and arr1[i] == arr2[j]:
                i+=1
                j+=1
            return j==len(arr2) and i<len(arr1) or i<len(arr1) and arr1[i] > arr2[j]

        def toOneNumber(arr1, arr2):
            i, j = 0, 0
            res = []
            while i< len(arr1) or j < len(arr2):
                if isGreater(arr1, arr2, i, j):
                    res.append(arr1[i]); i+=1
                else: 
                    res.append(arr2[j]);j+=1
            return res         

        n1, n2 = len(nums1), len(nums2)
        res = [0]*k
        for i in range(max(0, k - n2), min(k+1, n1+1)): # is num of ele from nums1
            cur1, cur2 = Generate(nums1, i), Generate(nums2, k - i) 
            res = max(res, toOneNumber(cur1, cur2))
        return list(res)


        


class Solution:
    def maxNumber(self, nums1, nums2, k):
        def prep(nums, k):
            drop = len(nums) - k
            out = []
            for num in nums:
                while drop and out and out[-1] < num:
                    out.pop()
                    drop -= 1
                out.append(num)
            return out[:k]

        def merge(a, b):
            return [max(a, b).pop(0) for _ in a+b]

        return max(merge(prep(nums1, i), prep(nums2, k-i))
                for i in range(k+1)
                if i <= len(nums1) and k-i <= len(nums2))


