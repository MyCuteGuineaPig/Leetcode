"""
149. Max Points on a Line


Example 1:

Input: [[1,1],[2,2],[3,3]]
Output: 3
Explanation:
^
|
|        o
|     o
|  o  
+------------->
0  1  2  3  4
Example 2:

Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
Output: 4
Explanation:
^
|
|  o
|     o        o
|        o
|  o        o
+------------------->
0  1  2  3  4  5  6
"""

# Definition for a point.
# class Point:
#     def __init__(self, a=0, b=0):
#         self.x = a
#         self.y = b

class Solution:
    def maxPoints(self, points):
        """
        :type points: List[Point]
        :rtype: int
        """
        def calslope(a, b):
            if a.x == b.x: return float('inf')
            return (a.y - b.y)/(a.x - b.x)
        res = 0
        for i, value in enumerate(points):
            same = 1
            dic = collections.defaultdict(int)
            for j, v in enumerate(points):
                if j == i: continue
                if v.x == value.x and v.y == value.y: 
                    same += 1 
                    continue
                dic[calslope(v,value)] += 1
            res = max(res, (max(dic.values()) if dic else 0)+same)
        return res