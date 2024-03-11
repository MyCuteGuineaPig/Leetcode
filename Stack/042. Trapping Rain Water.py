"""
42. Trapping Rain Water
Example:

Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6

"""

#Descending Stack 
class Solution:
    def trap(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        stack = []
        area = 0 
        for i,h in enumerate(height):
            if len(stack)>=2 and stack[-1][1] < h:
                while len(stack)>=2 and stack[-1][1] < h: 
                    j, base = stack.pop()
                    curh = min(stack[-1][1], h)
                    j = stack[-1][0]
                    area += (i - j - 1)*(curh-base)
            if stack and stack[-1][1] < h:
                stack = []
            stack.append([i,h])
        return area


class Solution:
    def trap(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        stack = []
        area = 0 
        for i,h in enumerate(height):
            if stack and stack[-1][1] < h:
                while stack and stack[-1][1] < h: 
                    j, base = stack.pop()
                    if not stack: break
                    curh = min(stack[-1][1], h)
                    j = stack[-1][0]
                    area += (i - j - 1)*(curh-base)
            stack.append([i,h])
        return area

# Greedy
class Solution:
    def trap(self, height):
        if not height: return 0
        leftmax, rightmax = height[0], height[-1]
        i, j = 0, len(height)-1
        area = 0 
        while i < j: 
            if height[i] < height[j]:  
                if height[i] < leftmax: area += leftmax - height[i]
                else: leftmax = height[i]
                i += 1 
            else: 
                if height[j] < rightmax: area += rightmax - height[j]
                else: rightmax = height[j]
                j -= 1
        return area 


class Solution:
    def trap(self, height):
        if not height: return 0
        leftmax, rightmax = height[0], height[-1]
        i, j = 0, len(height)-1
        area = 0 
        while i < j: 
            leftmax = max(leftmax, height[i])
            rightmax = max(rightmax, height[j])
            if leftmax < rightmax: 
                area += leftmax - height[i]
                i+=1
            else:
                area += rightmax - height[j]
                j-=1
        return area 



class Solution:
    # @param {integer[]} height
    # @return {integer} 
    def trap(self, height):
        n = len(height)
        l, r, water, minHeight = 0, n - 1, 0, 0
        while l < r:
            while l < r and height[l] <= minHeight:
                water += minHeight - height[l]
                l += 1
            while r > l and height[r] <= minHeight:
                water += minHeight - height[r]
                r -= 1
            minHeight = min(height[l], height[r])
        return water