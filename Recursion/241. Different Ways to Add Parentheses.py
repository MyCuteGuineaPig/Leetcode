"""
241. Different Ways to Add Parentheses

Example 1:

Input: "2-1-1"
Output: [0, 2]
Explanation: 
((2-1)-1) = 0 
(2-(1-1)) = 2
Example 2:

Input: "2*3-4*5"
Output: [-34, -14, -10, -10, 10]
Explanation: 
(2*(3-(4*5))) = -34 
((2*3)-(4*5)) = -14 
((2*(3-4))*5) = -10 
(2*((3-4)*5)) = -10 
(((2*3)-4)*5) = 10

"""


class Solution:
    def diffWaysToCompute(self, input):
        """
        :type input: str
        :rtype: List[int]
        """
        def generater(start, end):
            return [a + b if c == '+' else a-b if c=='-' else  a*b
                    for i, c in enumerate(input[start: end+1]) if c in '+-*' 
                    for a in generater(start,start+i-1) for b in generater(start+i+1,end)] or [int(input[start:end+1])]
        return generater(0,len(input)-1) 