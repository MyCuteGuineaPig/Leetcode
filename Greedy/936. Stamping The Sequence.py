class Solution:
    def movesToStamp(self, stamp: str, target: str) -> List[int]:
        n, m, t, s, res = len(target), len(stamp), list(target), list(stamp), []

        def check(i):
            changed = False
            for j in range(m):
                if t[i + j] == '?': continue
                if t[i + j] != s[j]: return False
                changed = True
            if changed:
                t[i:i + m] = ['?'] * m
                res.append(i)
            return changed

        changed = True
        while changed:
            changed = False
            for i in range(n - m + 1):
                changed |= check(i)
        return res[::-1] if t == ['?'] * n else []



class Solution(object):
    # 判断是否匹配
    def check(self, s, t):
        for i in range(len(s)):
            if t[i] == '?': continue
            if s[i] != t[i]: return False
        return True
        
    def movesToStamp(self, s, target):
        turn = 0 # 匹配轮次，不超过10*len(target)
        n, m = len(s), len(target)
        res = []
        compare = '?' * n
        while turn < 10*m:
            tmp = turn
            for i in range(m-n+1):
                if target[i:i+n] != compare and self.check(s, target[i:i+n]):
                    turn = turn + 1
                    res.append(i)
                    target = target[:i] + compare + target[i+n:]
            # 成功还原，反向返回res
            if target == '?'*m: return res[::-1]
            # 如果一个匹配的都没找到，说明无法还原了，直接break
            if turn == tmp: break
        return []


class Solution:
    def movesToStamp(self, stamp, target):
        def okay(s):
            ret = False
            for c1, c2 in zip(s, stamp):
                if c1 == "?": continue
                elif c1 != c2: return False
                else: ret = True
            return ret
        root, move, mx, arr = "?" * len(target), 0, 10 * len(target), []
        while move < mx:
            pre = move
            for i in range(len(target) - len(stamp) + 1):
                if okay(target[i:i + len(stamp)]):
                    move += 1
                    arr = [i] + arr
                    target = target[:i] + "?" * len(stamp) + target[i + len(stamp):]
            if target == root: return arr
            if move == pre: break
        return []

"""

1. stamp[0] has to be equal with target[0]
2. stamp[-1] has to be equal with target[-1]
3. We keep checking pairs of (stamp[s], target[t]). When checking (s, t). 
    If stamp[s] == target[t],  
         can  move forward to (s+1, t+1). 
    Otherwise,
         we add a new stamp at index t+1 and stamp[0] has to be equal with target[t+1]. move forward to (0, t+1).
        比如  stamp = "abc", target = "ababc", 在 t = 2, s =2, 不match, target[2] 必须要等于 stamp[0] 否则返回false

4. When s == len(stamp), and we can try any i that stamp[i] == target[t].
     In such case, we stamp at index t-i at the begining of the sequence
      so that stamp[:i] will be overwritten by "later" stamps and we move forward to (i, t).

      比如 stamp = "abca"  target = "abcabca", 在target[3] = 'a' 可以insert new stamp, dfs(s = 0, t=3, seq=[3,0])

5. We finish our search when we reach the end of target or t == len(target). Based on rule #2,
     if i == len(stamp) as well, we have a valid sequence.



"""

class Solution:
    def movesToStamp(self, stamp: str, target: str) -> List[int]:
        memo, ls, lt = {}, len(stamp), len(target)
        def dfs(s, t, seqs):
            if t == lt:
                memo[s, t] = seqs if s == ls else []
            if (s, t) not in memo:
                if s == ls:
                    for i in range(ls):
                        cand = dfs(i, t, [t-i]+seqs)
                        if cand:
                            memo[s, t] = cand
                            break
                    else: 
                        memo[s, t] = []
                elif target[t] == stamp[s]:
                    cand = dfs(s+1, t+1, seqs)
                    memo[s, t] = cand if cand else dfs(0, t+1, seqs+[t+1])
                else:
                    memo[s, t] = []
            return memo[s, t]
        return dfs(0, 0, [0])