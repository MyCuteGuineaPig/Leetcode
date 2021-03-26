class Solution:
    def expand(self, s: str) -> List[str]:
        option = ['']
        multi = False
        char = []
        for i in s:
            if i == ',':
                continue
            elif i == '{':
                multi = True
            elif i == '}':
                option = [ o + c for o in option for c in char]
                multi = False
                char = []
            elif multi:
                char += i,
            else:
                option = [o + i for o in option]
                
        return sorted(option)

class Solution:
    def expand(self, s: str) -> List[str]:                           # e.g. "{a,b}c{d,e}f"
        A = s.replace('{', ' ').replace('}', ' ').strip().split(' ') # ['a,b', 'c', 'd,e', 'f']
        B = [sorted(a.split(',')) for a in A]                       # [['a', 'b'], ['c'], ['d', 'e'], ['f']]
        return [''.join(c) for c in itertools.product(*B)]

        # list(itertools.product(*B)) 等于 list(itertools.product(['a','b'],['c'],['d','e'],['f']))
        # Give [('a', 'c', 'd', 'f'), ('a', 'c', 'e', 'f'), ('b', 'c', 'd', 'f'), ('b', 'c', 'e', 'f')]


class Solution(object):
    def expand(self, S):
        """
        :type S: str
        :rtype: List[str]
        """
        self.res = []
        def helper(s, word):
            if not s:
                self.res.append(word)
            else:
                if s[0] == "{":
                    i = s.find("}")
                    for letter in s[1:i].split(','):
                        helper(s[i+1:], word+letter)
                else:
                    helper(s[1:], word + s[0])
        helper(S, "")
        self.res.sort()
        return self.res