"""
134. Gas Station


Example 1:

Input: 
gas  = [1,2,3,4,5]
cost = [3,4,5,1,2]

Output: 3

Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.
Example 2:

Input: 
gas  = [2,3,4]
cost = [3,4,3]

Output: -1

Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.

"""

class Solution:
    def canCompleteCircuit(self, gas, cost):
        """
        :type gas: List[int]
        :type cost: List[int]
        :rtype: int
        """
        if sum(gas) < sum(cost): return -1
        res = -1
        curgas = curcost = maxdeficit = 0
        for i, (g, c) in enumerate(zip(gas,cost)):
            curgas, curcost = curgas+g, curcost+c
            if curcost - curgas > maxdeficit:
                maxdeficit = curcost - curgas
                res = i
        return res+1

class Solution:
    def canCompleteCircuit(self, gas, cost):
        start, end = len(gas)-1, 0
        cur = gas[start] - cost[start]
        while start > end:
            if cur >= 0: 
                cur += gas[end] - cost[end]
                end += 1 
            else: 
                start -=1 
                cur+= gas[start] - cost[start]
        
        return -1 if cur < 0 else start