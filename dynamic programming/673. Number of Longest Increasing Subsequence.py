"""
673. Number of Longest Increasing Subsequence

Example 1:
Input: [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].
Example 2:
Input: [2,2,2,2,2]
Output: 5
Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1,

"""

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
            #print(i, curmax)
        #print(maxLen, cnt)
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


                