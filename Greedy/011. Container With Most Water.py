"""
11. Container With Most Water

Example:

Input: [1,8,6,2,5,4,8,3,7]
Output: 49

"""


class Solution:
    def maxArea(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        h = min(height[0], height[-1]) 
        i, j = 0, len(height)-1
        water = 0
        while i<j:
            water = max(water, (j - i)*h)
            while i<j and height[i]<=h: i+=1
            while i<j and height[j]<=h: j-=1
            h = min(height[i], height[j])
        return water

class Solution:
    def maxArea(self, height):
        i, j = 0, len(height)-1
        water = 0
        while i<j:
            if height[i] < height[j]:
                water = max(water, (j-i)*height[i])
                i+=1
            else:
                water = max(water, (j-i)*height[j])
                j-=1
        return water