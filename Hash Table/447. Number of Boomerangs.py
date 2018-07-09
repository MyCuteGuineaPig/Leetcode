"""
447. Number of Boomerangs


Input:
[[0,0],[1,0],[2,0]]

Output:
2

Explanation:
The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]]
"""


class Solution:
    def numberOfBoomerangs(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        def caldis(a, b):
            return (a[0]-b[0])**2 + (a[1]-b[1])**2
        res = 0
        for i, v in enumerate(points):
            dic = collections.defaultdict(int)
            for j, w in enumerate(points):
                if i == j: continue
                dic[caldis(v, w)]+=1
            for v in dic.values():  
                res += (v-1)*v
        return res

class Solution:
    def numberOfBoomerangs(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        ans = 0
        for p in points:
            dic = {}
            for p1 in points:
                f = p1[0] - p[0]
                s = p1[1] - p[1]
                d = f*f + s*s
                dic[d] = 1 + dic.get(d,0)
            for count in dic.values():
                ans += count*(count-1)
        return ans