"""
473. Matchsticks to Square

Example 1:
Input: [1,1,2,2,2]
Output: true

Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.
Example 2:
Input: [3,3,3,3,4]
Output: false

Explanation: You cannot find a way to form a square with all the matchsticks.
"""

class Solution:
    def makesquare(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        n = len(nums)
        if n == 0: return False
        peri = sum(nums)
        if peri % 4: return False
        nums.sort(key = lambda x: -x)
        side = [peri/4]*4
        def backtrack(index):
            if index == n:
                print(index, side)
                return  side[0] == side[1] == side[2] == side[3] == 0
            for i in range(4):
                if side[i] < nums[index]: continue
                j = i-1
                while j>=0 and side[j] != side[i]:
                    j -= 1
                if j != -1: continue
                side[i] -= nums[index]
                if backtrack(index+1) : return True
                side[i] += nums[index]
            return False
        return backtrack(0)


class Solution:
    def makesquare(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        
        s = sum(nums)
        if s < 4 or s%4 != 0:
            return False
        goal = s//4
        nums.sort(reverse = True)
        if nums[0] > goal:
            return False
        
        visited = [False]*len(nums)
        cache = {}
        def dp(k,i,currSum):  #i是nums的index, k是边，currsum是当前边的长                          # dp(k,i,currSum) returns True/False of reaching k goals from index=i successfully
            if (k,i,currSum) in cache:                  # currSum is the current Sum under this k...which is in [0, goal]
                return cache[(k,i,currSum)]
            if k == 0:
                return True
            if currSum == goal: #fill next 边
                cache[(k,i,currSum)] = dp(k-1,0,0)
                return cache[(k,i,currSum)]
            for j in range(i, len(nums)):
                if visited[j] == False and currSum+nums[j] <= goal:
                    visited[j] = True
                    if dp(k,j+1,currSum+nums[j]) == True:
                        cache[(k,i,currSum)] = True
                        return True
                    else:
                        visited[j] = False
            cache[(k,i,currSum)] = False
            return False
        return dp(4, 0, 0)
        