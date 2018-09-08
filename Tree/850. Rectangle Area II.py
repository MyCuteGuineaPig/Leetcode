"""
850. Rectangle Area II

Input: [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
Output: 6
Explanation: As illustrated in the picture.
Example 2:

Input: [[0,0,1000000000,1000000000]]
Output: 49
Explanation: The answer is 10^18 modulo (10^9 + 7), which is (10^9)^2 = (-7)^2 = 49.
"""
class Solution:
    def rectangleArea(self, rectangles):
        """
        :type rectangles: List[List[int]]
        :rtype: int
        """
        xcoordinate = set(x[0] for x in rectangles).union(x[2] for x in rectangles)
        xcoordinate = sorted(list(xcoordinate))
        x_index = dict((v,i) for i, v in enumerate(xcoordinate))
        count = [0]*len(xcoordinate)

        height = collections.defaultdict(list)
        for x1, y1, x2, y2 in rectangles:
            height[y1].append([1, x1, x2])
            height[y2].append([-1, x1, x2])
        height = sorted(height.items())
        preh, area, base, mod = 0, 0, 0, 10**9+7
        for h, li in height: 
            area =  (area + (h - preh)*base)%mod 
            for sign, s, e in li:
                s, e = x_index[s], x_index[e]
                for i in range(s, e):
                    count[i] += sign
            
            base = sum([xcoordinate[i+1] - xcoordinate[i] for i, v in enumerate(count) if v > 0])
            preh = h
        return area

class Solution:
    def rectangleArea(self, rectangles):
        xs = sorted(set([x for x1, y1, x2, y2 in rectangles for x in [x1, x2]] + [0]))
        x_i = {v: i for i, v in enumerate(xs)}
        count = [0] * len(x_i)
        L = []
        for x1, y1, x2, y2 in rectangles:
            L.append([y1, x1, x2, 1])
            L.append([y2, x1, x2, -1])
        L.sort()
        cur_y = cur_x_sum = area = 0
        for y, x1, x2, sig in L:
            area += (y - cur_y) * cur_x_sum
            cur_y = y
            for i in range(x_i[x1], x_i[x2]):
                count[i] += sig
            cur_x_sum = sum(x2 - x1 if c else 0 for x1, x2, c in zip(xs, xs[1:], count))
        return area % (10 ** 9 + 7)


class Solution:
    def rectangleArea(self, rectangles):
        """
        :type rectangles: List[List[int]]
        :rtype: int
        """
        height = collections.defaultdict(list)
        for x1, y1, x2, y2 in rectangles:
            height[x1].append([1, y1, y2])
            height[x2].append([-1, y1, y2])
        height = sorted(height.items())

        open = []
        area, mod, prex, = 0, 10**9 + 7, 0
        for x, h in height:
            if open: 
                lower, cnt = -1, 0 
                for di, gao in open: 
                    if lower >= gao: continue
                    lower = max(lower, di)
                    cnt += gao - lower
                    lower = gao 
                area  = (area + (x - prex)*cnt)%mod
            for sign, di, gao in h: 
                if sign > 0: 
                    open.append((di,gao))
                else:
                    del open[open.index((di,gao))]
            open.sort()
            prex = x
        return area


class Solution:
    def rectangleArea(self, rectangles):
        """
        :type rectangles: List[List[int]]
        :rtype: int
        """
        xcoord = set(x[0] for x in rectangles).union(x[2] for x in rectangles)
        ycoord = set(x[1] for x in rectangles).union(x[3] for x in rectangles)
        xcoord = sorted(xcoord)
        ycoord = sorted(ycoord)
        x_index = dict((v,i) for i, v in enumerate(xcoord))
        y_index = dict((v,i) for i, v in enumerate(ycoord))
        rect = [[0,]*len(ycoord) for _ in range(len(xcoord))]
        area, mod = 0, 10**9 + 7 
        for x1, y1, x2, y2 in rectangles:
            for i in range(x_index[x1], x_index[x2]):
                for j in range(y_index[y1], y_index[y2]):
                    if rect[i][j] == 0:
                        area = (area + (xcoord[i+1]-xcoord[i])*(ycoord[j+1]-ycoord[j]))%mod
                    rect[i][j] += 1
        return area

