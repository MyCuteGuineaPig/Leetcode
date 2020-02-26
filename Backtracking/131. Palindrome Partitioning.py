class Solution:
    def partition(self, s):
        return [[ s[:i+1]]  + rest 
                for i in range(len(s)) 
                if s[:i+1] == s[i::-1] 
                for rest in self.partition(s[i+1:]) ] or [[]]
                
class Solution:
    def partition(self, s):
        def helper(s):
            if not s:
                yield []
            for i in range(len(s)):
                if s[:i+1] == s[i::-1]:
                    for nxt in helper(s[i+1:]):
                        yield [s[:i+1]] + nxt
        return [*helper(s)]
