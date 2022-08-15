class Solution:   
    def smallestNumber(self, s):
        res, stack = [], []
        for i,c in enumerate(s + 'I', 1):
            stack.append(str(i))
            if c == 'I':
                res += stack[::-1]
                stack = []
        return ''.join(res)


class Solution:
    def smallestNumber(self, s):
        res = []
        for i,c in enumerate(s + 'I', 1):
            if c == 'I':
                res += range(i, len(res), -1)
        return ''.join(map(str,res))

"""
"IIIDIDDD"
0 ['1']
0 ['1', '2']
0 ['1', '2', '3']
1 ['1', '2', '3', '5', '4']
3 ['1', '2', '3', '5', '4', '9', '8', '7', '6']
"""

class Solution:
    def smallestNumber(self, s):
        res, pool = [], list('987654321')
        for k in map(len,s.split('I')):
            res += [pool.pop() for _ in range(k + 1)][::-1]
        return ''.join(res)



class Solution:
    def smallestNumber(self, pattern: str) -> str:
        ans = [1]
        for ch in pattern: 
            if ch == 'I': 
                m = ans[-1]+1
                while m in ans: m += 1
                ans.append(m)
            else: 
                ans.append(ans[-1])
                for i in range(len(ans)-1, 0, -1): 
                    if ans[i-1] == ans[i]: ans[i-1] += 1
        return ''.join(map(str, ans))