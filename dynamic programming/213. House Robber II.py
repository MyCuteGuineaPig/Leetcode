
class Solution:
    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if(len(nums)==1): return nums[0] # 1的时候不work 两个dp，一个从第一位开始，一个从倒数第二位结束
        last, now = 0, 0 
        last1, now1 = 0, 0
        for i, n in enumerate(nums):
            if i<len(nums)-1:
                last, now = now, max(n+last,now)
                print(now, last)
            if i>0:
                last1, now1 = now1, max(n+last1,now1)
        return max(now,now1)