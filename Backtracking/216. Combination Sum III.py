"""
216. Combination Sum III
Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.


Example 1:

Input: k = 3, n = 7

Output:

[[1,2,4]]

Example 2:

Input: k = 3, n = 9

Output:

[[1,2,6], [1,3,5], [2,3,4]]
"""

//write by own
class Solution:
    def combinationSum3(self, k: int, n: int) -> List[List[int]]:
        def generate(cur, k, n, start):
            if n==0 and k == 0:
                yield cur
            for i in range(start,min(n+1,10)):
                for p in generate(cur+[i], k-1, n-i, i+1):
                    yield p 
        return [*generate([],k,n,1)]

    
//write by own
class Solution:
    def combinationSum3(self, k: int, n: int) -> List[List[int]]:
        def generate(k, n, start):
            if n==0 and k == 0:
                return [[]]
            return [[x] + c for x in range(start, min(n+1, 10)) for c in generate(k-1, n-x, x+1)]
            
        return generate(k,n,1)
    
    
class Solution:
    def combinationSum3(self, k, n):
        """
        :type k: int
        :type n: int
        :rtype: List[List[int]]
        """
        return [c for c in itertools.combinations(range(1,10),k) if sum(c) == n]


class Solution:
    def combinationSum3(self, k, n):
        import functools;
        return [ c for c in functools.reduce(lambda nexts, _ : [next_+[first] for next_ in nexts for first in range(next_[-1]+1 if next_ else 1, 10)], range(k), [[]]) if sum(c) == n]
    
    
