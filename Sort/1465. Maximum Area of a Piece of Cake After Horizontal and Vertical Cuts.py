class Solution:
    def maxArea(self, h: int, w: int, horizontalCuts: List[int], verticalCuts: List[int]) -> int:
        horizontalCuts.sort()
        verticalCuts.sort()
        res1, res2 = horizontalCuts[0], verticalCuts[0]
        for i in range(len(horizontalCuts)):
            if i < len(horizontalCuts)-1:
                res1 = max(res1, horizontalCuts[i+1] - horizontalCuts[i])
            else:
                 res1 = max(res1, h - horizontalCuts[i])
            
        for i in range(len(verticalCuts)):
            if i < len(verticalCuts)-1:
                res2 = max(res2, verticalCuts[i+1] - verticalCuts[i])
            else:
                res2 = max(res2, w - verticalCuts[i]) 
        
        return res1 * res2 % (10**9 + 7)

class Solution:
    def maxArea(self, h: int, w: int, horizontalCuts: List[int], verticalCuts: List[int]) -> int:
        horizontalStrips = [0] + sorted(horizontalCuts) + [h]
        verticalStrips = [0] + sorted(verticalCuts) + [w]
        
        maxStripWidth = max([horizontalStrips[i + 1] - horizontalStrips[i] for i in range(len(horizontalStrips) - 1)])
        maxStripHeight = max([verticalStrips[i + 1] - verticalStrips[i] for i in range(len(verticalStrips) - 1)])
        
        return (maxStripWidth * maxStripHeight) % ((10 ** 9) + 7)