class Solution:
    def bagOfTokensScore(self, tokens: List[int], P: int) -> int:
        res = cur = 0
        d = collections.deque(sorted(tokens))
        while d and (d[0] <= P or cur):
            if d[0] <= P:
                P -= d.popleft()
                cur += 1
            else:
                P += d.pop()
                cur -= 1
            res = max(res, cur)
        return res


class Solution:
    def bagOfTokensScore(self, tokens: List[int], P: int) -> int:
        tokens.sort()
        l, r, score = 0, len(tokens) - 1, 0
        while l <= r:
            if P >= tokens[l]:
                P -= tokens[l]
                score += 1
                l += 1
            elif score and l != r:
                P += tokens[r]
                score -= 1
                r -= 1
            else:
                break
        return score