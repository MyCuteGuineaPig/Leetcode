"""
554. Brick Wall

Input: 
[[1,2,2,1],
 [3,1,2],
 [1,3,2],
 [2,4],
 [3,1,2],
 [1,3,1,1]]
Output: 2
Explanation: 
"""

class Solution:
    def leastBricks(self, wall):
        """
        :type wall: List[List[int]]
        :rtype: int
        """
        dic = collections.defaultdict(int)
        for w in wall:
            cur = 0
            for i in w[:-1]:
                cur+=i
                dic[cur]+=1
        return len(wall) - ( max(dic.values()) if dic else 0 ) #or len(wall)-max(d.values()+[0])