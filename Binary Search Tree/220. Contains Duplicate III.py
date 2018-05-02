"""
220	Contains Duplicate III
"""
"""
O(N)的解
"""
class Solution:
    def containsNearbyAlmostDuplicate(self, nums, k, t):
        """
        :type nums: List[int]
        :type k: int
        :type t: int
        :rtype: bool
        """
        if k<1:
            return False
        dic = collections.OrderedDict()
        for num in nums:
            key = num if t == 0 else num//t
            for m in [dic.get(key-1),dic.get(key),dic.get(key+1)]:
                if m is not None and abs(m-num)<=t:
                    return True
            if len(dic) == k:
                dic.popitem(False) #delete 最先insert的, 
            dic[key] = num #不会出现修改之前的key, 因为比如t是3, 之前数是9，现在是11，已经在t范围内，已经return true了
        return False
        

class Solution:
    def containsNearbyAlmostDuplicate(self, nums, k, t):
        """
        :type nums: List[int]
        :type k: int
        :type t: int
        :rtype: bool
        """
        buckets = {}
        for i, v in enumerate(nums):
            bucket_num, offset = (v//t, 1) if t else (v, 0)
            for idx in range(bucket_num - offset, bucket_num + offset + 1):
                if idx in buckets and abs(buckets[idx] - nums[i]) <= t:
                    return True
        
            buckets[bucket_num] = nums[i]
            if len(buckets) > k:
                del buckets[nums[i-k] // t if t else nums[i-k]]
        
        return False

"""
O(N*K)的解
"""
class Solution:
    def equalSol(self, nums, k):
        if k == 0:
            return False
        d = {}
        for i in range(len(nums)):
            if nums[i] in d.keys() and abs(i - d[nums[i]]) <= k:
                return True
            else:
                d[nums[i]] = i
        return False
    
    def containsNearbyAlmostDuplicate(self, nums, k, t):
        """
        :type nums: List[int]
        :type k: int
        :type t: int
        :rtype: bool
        """
        if k == 0:
            return False
        if t == 0:
            return self.equalSol(nums, k)
        for i in range(len(nums)):
            for j in range(1,(k+1)):
                if (i + j) < len(nums) and abs(nums[i] - nums[i+j]) <= t:
                    return True
                if (i - j) >= 0 and abs(nums[i] - nums[i-j]) <=t:
                    return True
        return False

