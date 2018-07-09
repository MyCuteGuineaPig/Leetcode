"""
825. Friends Of Appropriate Ages

Example 1:

Input: [16,16]
Output: 2
Explanation: 2 people friend request each other.
Example 2:

Input: [16,17,18]
Output: 2
Explanation: Friend requests are made 17 -> 16, 18 -> 17.
Example 3:

Input: [20,30,100,110,120]
Output: 
Explanation: Friend requests are made 110 -> 100, 120 -> 110, 120 -> 100.
"""

class Solution:
    def numFriendRequests(self, ages):
        """
        :type ages: List[int]
        :rtype: int
        """
        dic = collections.defaultdict(int)
        for a in ages:
            dic[a]+=1
        res = 0
        for k1, v1 in dic.items():
            for k2, v2 in dic.items():
                if 0.5*k1 + 7 < k2 <= k1:
                    res += ( v1*v2 if k1 != k2 else v1*(v1-1))
        return res