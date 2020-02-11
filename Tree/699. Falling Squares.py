"""
699. Falling Squares


Input: [[1, 2], [2, 3], [6, 1]]
Output: [2, 5, 5]
Explanation:

After the first drop of positions[0] = [1, 2]:
_aa
_aa
-------
The maximum height of any square is 2.


After the second drop of positions[1] = [2, 3]:
__aaa
__aaa
__aaa
_aa__
_aa__
--------------
The maximum height of any square is 5.  
The larger square stays on top of the smaller square despite where its center
of gravity is, because squares are infinitely sticky on their bottom edge.


After the third drop of positions[1] = [6, 1]:
__aaa
__aaa
__aaa
_aa
_aa___a
--------------
The maximum height of any square is still 5.

Thus, we return an answer of [2, 5, 5].
"""


class Solution:
    def fallingSquares(self, positions: List[List[int]]) -> List[int]:
        res = []
        mp = []
        for start, h in positions:
            end = start + h 
            j = it = bisect.bisect_right(mp, [start, float('inf')])
            n = len(mp)
            preh = baseh = 0 if it == 0 else mp[it-1][1]
            while j < n and mp[j][0] < end:
                preh = mp[j][1]
                baseh = max(baseh, mp[j][1])
                j+=1
            mp.append([start, baseh + h])
            if j < n and mp[j][0] != end or j == n:
                mp.append([end, preh])
            mp[it:j] = []
            mp.sort(key = lambda x: x[0] )
            res.append( max(res[-1], baseh+h) if res else baseh + h )
        return res

"""
Solution 1: 
跟218. The Skyline Problem 解法类似， 画出square的轮廓
"""
            
class Solution:
    def fallingSquares(self, positions):
        """
        :type positions: List[List[int]]
        :rtype: List[int]
        """
        h = [0]
        pos = [-1]
        maxh = 0
        res = []
        for x, side in positions:
            i = bisect.bisect_right(pos, x)
            j = bisect.bisect_left(pos, x+side)
            #print(x, side, i,j, "h",h,"pos",pos)
            h0,h1 = max(h[i-1:j]),h[j-1] #不用考虑 h[j] == x + side then  = h[j]
            """
            因为同一点，可以在list 有很多点，比如[[4,2],[3,1],[1,3],[4,5]],
            在【3，1]之后，
            pos = [0, 3, 4, 4, 6] height = [0, 1, 0, 2, 0], 而最后的[4,5]的点的height获取的点是第一个比4大的点 biset_right，
            所以i -1不会是[3,1]或者[1,3]的边界，因为是bisect_right，选取第一个大于4的点，而是[4,2]
            
            假如j是等于 x + side, 但是很为pos[i,j] 也不会把j点删除掉，只把j的前一点删除
            """
            pos[i:j] = [x, x+side] 
            h[i: j] = [h0+side, h1]
            maxh = max(maxh, h0+side)
            res.append(maxh)
        return res
            
        
"""

Solution 2  Offline Propagation, 
"""
class Solution:
    def fallingSquares(self, positions):
        """
        :type positions: List[List[int]]
        :rtype: List[int]
        """
        height = [0]*len(positions)
        res = []
        maxh = 0
        for i, (x, y) in enumerate(positions):
            height[i] += y
            maxh = max(maxh, height[i])
            res.append(maxh)
            end = x + y
            for j, (x1, y1) in enumerate(positions[i+1:], i+1):
                end2 = x1 + y1
                if x < end2 and x1 <end:
                    height[j] = max(height[j], height[i])
        return res
        
            
#solution 3 Segment Tree
class SegmentTreeNode:
    def __init__ (self,val, s, e):
        self.left = None 
        self.right = None
        self.val = val
        self.s = s
        self.e = e

class SegmentTree:
    def __init__ (self,count):
        self.root = self.buildTree(0, count)
        self.lazy = self.buildTree(0, count)
    
    def buildTree(self,s, e):
        if s > e: return None
        node = SegmentTreeNode(0, s, e)
        if s == e: return node
        mid = (s + e)//2
        node.left = self.buildTree(s,mid)
        node.right = self.buildTree(mid+1, e)
        return node
    
    def dfs(self,root):
        if not root: return 
        print(root.s, root.e, root.val)
        self.dfs(root.left)
        self.dfs(root.right)
    
    def update(self, L, R, h):
        return self.updateUtil(L,R, h, self.root, self.lazy)
    
    def updateUtil(self, L, R, h, tree, lazy):
        if lazy.val != 0:
            self.updateLazy(lazy,tree)
        if R < tree.s or L>tree.e: return tree.val
        if L<=tree.s <= tree.e <= R:
            tree.val = max(tree.val, h)
            if tree.s != tree.e:
                lazy.left.val = max(lazy.left.val, h)
                lazy.right.val = max(lazy.right.val, h)
            return tree.val
        tree.val = max(self.updateUtil(L,R,h, tree.left, lazy.left), self.updateUtil(L,R,h, tree.right, lazy.right))
        return tree.val
    
    def query(self, L, R):
        return self.queryUtil(L,R,self.root, self.lazy)

    def queryUtil(self, L, R, tree, lazy):
        if lazy.val != 0:
            self.updateLazy(lazy,tree)
        if R < tree.s or L>tree.e: return 0
        if L<=tree.s <= tree.e <= R:
            return tree.val
        return max(self.queryUtil(L, R, tree.left, lazy.left), self.queryUtil(L, R, tree.right, lazy.right))


    def updateLazy(self,lazy,tree):
        update = lazy.val
        tree.val = max(lazy.val, tree.val)
        lazy.val = 0
        if lazy.s!=lazy.e:
            lazy.left.val = max(lazy.left.val, update)
            lazy.right.val = max(lazy.right.val, update)


class Solution:
    def fallingSquares(self, positions):
        """
        :type positions: List[List[int]]
        :rtype: List[int]
        """
        coordinate = set(x[0] for x in positions).union(x[0]+x[1]-1 for x in positions)
        coordinate = sorted(list(coordinate))
        segment = SegmentTree(len(coordinate)-1)
        maxh = 0
        res = []
        for x, y in positions:
            l = bisect.bisect_left(coordinate,x)
            r = bisect.bisect_left(coordinate, x+y-1)
            h = segment.query(l,r) + y
            maxh = max(h, maxh)
            res.append(maxh)
            segment.update(l,r,h)
        return res

      
