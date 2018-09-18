"""
452. Minimum Number of Arrows to Burst Balloons

Input:
[[10,16], [2,8], [1,6], [7,12]]

Output:
2

Explanation:
One way is to shoot one arrow for example at x = 6 (bursting the balloons [2,8] and [1,6]) and 
another arrow at x = 11 (bursting the other two balloons).

"""
""" 逐渐减小interval """

#sort by end,  burst点在e; 最后能到达的点是e，所以只要看下个点是不是小于等于e，就可以在e点burst，如果不行，需要新的arrow,
class Solution:
    def findMinArrowShots(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        if not points: return 0
        points.sort(key = lambda x: x[1])
        arrow = 1 
        pt = iter(points)
        _, e = next(pt)
        for curs, cure in pt: 
            if curs > e: 
                arrow += 1 
                e = cure
        return arrow


#sort by start
class Solution:
    def findMinArrowShots(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        if not points: return 0
        points.sort(key = lambda x: x[0])
        arrow = 1 
        pt = iter(points)
        _, e = next(pt)
        for curs, cure in pt: 
            if curs > e: 
                arrow += 1 
                e = cure
            else: e = min(e, cure)
        return arrow

class Solution(object):
    def findMinArrowShots(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        points = sorted(points, key = lambda x: x[1])
        res, end = 0, -float('inf')
        for interval in points:
            if interval[0] > end:
                res += 1
                end = interval[1]
        return res