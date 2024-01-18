# brute force
class Solution:
    def countSubstrings(self, s: str) -> int:
        N = len(s)
        res = 0
        for center in range(2*N - 1):
            left = center // 2
            right = left + center % 2
            while left >= 0 and right < N and s[left] == s[right]:
                res += 1
                left -= 1 
                right += 1
        return res

# dp
class Solution:
    def countSubstrings(self, s: str) -> int:
        N = len(s)
        res = 0
        dp = [[0, ]*N for _ in range(N)]
        for i in range(N):
            for j in range(i+1):
                if i == j:
                    dp[j][i] = 1
                elif i == j + 1:
                    dp[j][i] = 1 if s[i] == s[j] else 0
                else:
                    dp[j][i] = dp[j+1][i-1] if s[i] == s[j] else 0

        return sum(sum(dp, []))

# manacher
class Solution:
    def countSubstrings(self, s: str) -> int:
        text = "$#"
        for i in s: 
            text += i + "#"
        text += "^"
        p = [0,]* len(text)
        right = center = -1
        res = 0
        for i in range(1, len(text)-1):
            if i < right:
                p[i] = min(p[2*center - i], right - i)
            else:
                p[i] = 1
            while text[i + p[i]] == text[i-p[i]]:
                p[i] += 1 
            res += p[i] //2 
            if i + p[i] > right:
                right, center = i + p[i], i
        return res
        