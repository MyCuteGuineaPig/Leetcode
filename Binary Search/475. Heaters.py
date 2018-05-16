"""
475. Heaters

Input: [1,2,3],[2]
Output: 1
Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
Example 2:
Input: [1,2,3,4],[1,4]
Output: 1
Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be warmed.

"""

class Solution(object):
    def findRadius(self, houses, heaters):
        """
        :type houses: List[int]
        :type heaters: List[int]
        :rtype: int
        """
        heaters.sort()
        houses.sort()
        res = [float('inf'),]*len(houses)
        j = 0; i = 0
        while i<len(houses) and j<len(heaters):
            if houses[i]<=heaters[j]:
                res[i] = heaters[j] - houses[i]
                i+=1
            else: j+=1
        i = len(houses)-1; j = len(heaters)-1 
        while i>=0 and j>=0:
            if houses[i]>heaters[j]:
                res[i] = min(res[i],houses[i]-heaters[j])
                i-=1
            else: j-=1
        return max(res)


class Solution(object):
    def findRadius(self, houses, heaters):
        heaters = [float('-inf')]+sorted(heaters)+[float('inf')]
        return max([min(h - heaters[bisect.bisect_right(heaters,h)-1],heaters[bisect.bisect_right(heaters,h)]-h) for h in houses])

class Solution(object):
    def findRadius(self, houses, heaters):
        heaters = [float('-inf')]+sorted(heaters)+[float('inf')]
        res = [min(h - heaters[bisect.bisect_left(heaters,h)-1],heaters[bisect.bisect_left(heaters,h)]-h) for h in houses]
        return max(res)

class Solution(object):
    def findRadius(self, houses, heaters):
        heaters.sort()
        rslt=0
        for h in houses:
            pos=bisect.bisect_left(heaters,h)
            if pos==0:
                rslt=max(rslt,heaters[0]-h)
            elif pos==len(heaters):
                rslt=max(rslt,h-heaters[-1])
            else:                
                rslt=max(rslt,min(h-heaters[pos-1],heaters[pos]-h))
        return rslt      