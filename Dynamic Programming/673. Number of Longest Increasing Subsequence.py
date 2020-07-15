class Solution:
    def findNumberOfLIS(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        cnt = [1,]*n   
        maxLen = [1,]*n
        res, curmax = 0, 1
        for i in range(n):
            for j in range(i):
                if nums[i]>nums[j] and maxLen[j]+1 > maxLen[i]:
                     maxLen[i] = maxLen[j]+1 
                     cnt[i] = cnt[j]
                     if maxLen[i] > curmax:
                         curmax = maxLen[i]
                         res = 0 #找到新的最长的，更新结果为0

                elif maxLen[j] + 1 == maxLen[i]:
                    cnt[i] += cnt[j]
            if maxLen[i] == curmax: #如果现在长度等于最长的，加上现在count的
                res += cnt[i]
        return res


class Solution:
    def findNumberOfLIS(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        cnt = [1,]*n   
        maxLen = [1,]*n
        curmax = 1
        for i in range(n):
            for j in range(i):
                if nums[i]>nums[j] and maxLen[j]+1 > maxLen[i]: #新的长度大于老的长度
                     maxLen[i] = maxLen[j]+1 
                     cnt[i] = cnt[j] # 更新cnt[i]
                elif nums[i]>nums[j] and maxLen[j] + 1 == maxLen[i]: #新的长度等于老的长度
                     cnt[i] += cnt[j]
            curmax = max(maxLen[i], curmax)
        return sum( cnt[i] for i in range(n) if maxLen[i] == curmax)


class Solution(object):
    def findNumberOfLIS(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        dp = [[1, 1] for i in range(len(nums))]
        max_for_all = 1
        for i, num in enumerate(nums):
            max_len, count = 1, 0
            for j in range(i):
                if nums[j] < num:
                    if dp[j][0] + 1 > max_len:
                        max_len = dp[j][0] + 1
                        count = 0 
                    if dp[j][0] == max_len - 1:
                        count += dp[j][1]
            dp[i] = [max_len, max(count, dp[i][1])]
            max_for_all = max(max_len, max_for_all)
        return sum([item[1] for item in dp if item[0] == max_for_all])




class Solution:
    def findNumberOfLIS(self, nums: List[int]) -> int:
        if not nums: return 0
        
        from collections import defaultdict
        # LIS_table: index is length of LIS, value is the smallest number with that length
        LIS_table = [-float('inf')]
        #hash table: length of LIS --> all numbers has that length --> count how many happens
        hash_table = defaultdict(lambda : defaultdict(int))  #存的是长度
        hash_table[0][-float('inf')] = 1
        
        for num in nums:
            # insert num to the LIS_table in bisect way
            LIS_length = bisect.bisect_left(LIS_table, num)  
            #比如[1,3,5,4,7]
            #在5 时候, LIS_table = [-inf, 1,3,5]
            #在4时候,  LIS_table = [-inf, 1,3,4]
            #在7时候,  LIS_table = [-inf, 1,3,4,7]

            if LIS_length == len(LIS_table): LIS_table.append(num)
            else:                            LIS_table[LIS_length] = num
                
            # update the hash table
            # count the number of LIS with this num by looking at all the LIS_length-1 and append count 
            # count = hash_table[LIS_length-1][val] if val<num
            hash_table[LIS_length][num] += sum([hash_table[LIS_length-1][val]  #加上长度减去1，值小于num的长度和
                                                for val in hash_table[LIS_length-1] if val<num])
        
        return sum(hash_table[len(LIS_table)-1].values())