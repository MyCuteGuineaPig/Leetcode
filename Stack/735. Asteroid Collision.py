"""
735. Asteroid Collision


Example 1:
Input: 
asteroids = [5, 10, -5]
Output: [5, 10]
Explanation: 
The 10 and -5 collide resulting in 10.  The 5 and 10 never collide.
Example 2:
Input: 
asteroids = [8, -8]
Output: []
Explanation: 
The 8 and -8 collide exploding each other.
Example 3:
Input: 
asteroids = [10, 2, -5]
Output: [10]
Explanation: 
The 2 and -5 collide resulting in -5.  The 10 and -5 collide resulting in 10.
Example 4:
Input: 
asteroids = [-2, -1, 1, 2]
Output: [-2, -1, 1, 2]
Explanation: 
The -2 and -1 are moving left, while the 1 and 2 are moving right.
Asteroids moving the same direction never meet, so no asteroids will meet each other.
"""


class Solution:
    def asteroidCollision(self, asteroids):
        """
        :type asteroids: List[int]
        :rtype: List[int]
        """
        stk = []
        for i in asteroids:
            if stk and stk[-1] > 0 and i < 0:
                while stk and stk[-1] > 0 and i <0:
                    need = False
                    if stk[-1] == -i:
                        stk.pop()
                        break
                    elif stk[-1] > -i:
                        break
                    else:
                        need = True
                        stk.pop()
                if need: stk.append(i)
            else :
                stk.append(i)
        return stk


class Solution:
    def asteroidCollision(self, asteroids):
        """
        :type asteroids: List[int]
        :rtype: List[int]
        """
        stk = []
        for i in asteroids:
            while stk and stk[-1] > 0 and stk[-1]< - i:
                stk.pop()
            if not stk or i>0 or stk[-1] < 0: 
                stk.append(i)
            elif stk and stk[-1] == -i:
                stk.pop()
        return stk
            