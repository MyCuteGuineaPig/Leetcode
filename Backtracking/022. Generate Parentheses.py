class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        def generate(p, left, right, parens=[]):
            if left:         generate(p + '(', left-1, right)
            if right > left: generate(p + ')', left, right-1)
            if not right:    parens += p,
            return parens
        return generate('', n, n)
        


class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        def generate(p, left, right):
            if right >= left >= 0:
                if not right: 
                    yield p
                for q in generate(p+'(', left-1, right):
                    yield q
                for q in generate(p+')', left, right-1):
                    yield q
        
        return [*generate('',n,n)]
        
        
class Solution:
    def generateParenthesis(self, n: int, open = 0) -> List[str]:
        if n > 0 <= open:
                return ['(' + p for p in self.generateParenthesis(n-1, open+1)] + \
                       [')' + p for p in self.generateParenthesis(n, open-1)]
        return [')' * open] * (not n)
        
