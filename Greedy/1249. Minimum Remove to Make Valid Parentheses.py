class Solution:
    def minRemoveToMakeValid(self, s: str) -> str:
        cur, left, right = [], [0]*len(s), [0]*len(s)
        for i, st in enumerate(s): 
            if s[i] != '(' and s[i] != ')':
                continue 
            elif s[i] == '(':  cur.append(i)
            elif cur: 
                left[cur.pop()] = right[i] = 1
        return "".join(map(lambda i: i[1] if i[1] !='(' and i[1]!=')' or left[i[0]] or right[i[0]] else "" ,enumerate(s)))
                
                
                
class Solution:
    def minRemoveToMakeValid(self, s: str) -> str:
        cur, bad = [], []
        for i, st in enumerate(s): 
            if s[i] != '(' and s[i] != ')':
                continue 
            elif s[i] == '(':  cur.append(i)
            elif cur: cur.pop()
            else: bad.append(i)
        pre, res = 0, ""
        for i in sorted(bad + cur):
            res = res + s[pre:i]
            pre = i + 1
        return res + s[pre:]
 
 
 #from forum
 class Solution:
    def minRemoveToMakeValid(self, s: str) -> str:
        res = []
        left = 0
        for c in s:
            if c != ')' or left > 0:
                res.append(c)
            if c == '(':
                left += 1
            if c == ')' and left > 0:
                left -= 1
        for i in range(len(res)-1,-1,-1):
            if left == 0: break
            if res[i] == '(':
                res[i] = ''
                left -= 1
        return ''.join(res)
