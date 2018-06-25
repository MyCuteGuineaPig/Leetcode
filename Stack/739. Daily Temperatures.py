"""
739. Daily Temperatures

temperatures = [73, 74, 75, 71, 69, 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0]
"""

#ascendning stack, 每次push是小的，在后面都是大的，如果stack top小于当前的 pop
class Solution:
    def dailyTemperatures(self, temperatures):
        """
        :type temperatures: List[int]
        :rtype: List[int]
        """
        n = len(temperatures)
        res, stk = [0]*n, []
        for i in range(n-1, -1, -1):
            while stk and temperatures[i] >= temperatures[stk[-1]]: 
                stk.pop()
            if stk:
                res[i] = stk[-1] - i
            stk.append(i)
        return res

#descending stack, push的数是越来越小的
class Solution:
    def dailyTemperatures(self, temperatures):
        """
        :type temperatures: List[int]
        :rtype: List[int]
        """
        n = len(temperatures)
        res, stk = [0]*n, []
        for i in range(n):
            while stk and temperatures[i] > temperatures[stk[-1]]: 
                res[stk[-1]] = i-stk[-1]
                stk.pop()
            stk.append(i)
        return res