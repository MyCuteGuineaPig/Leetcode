class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        seen = set(forbidden)
        n = len(word)
        dp = [n] * (n + 1)
        res = 0
        for i in range(n - 1, -1, -1):
            dp[i] = dp[i + 1]
            for j in range(i, min(dp[i], n, i + 10)):
                if word[i:j + 1] in seen:
                    dp[i] = j
                    break
            res = max(res, dp[i] - i)
        return res


class Solution:
    def longestValidSubstring(self, word: str, forbidden: List[str]) -> int:
        T = lambda: defaultdict(T)
        trie = T()
        for w in forbidden:
            reduce(dict.__getitem__, w, trie)['#'] = True
        n = len(word)
        last = n
        res = 0

        for i in range(n - 1, -1, -1):
            t = trie
            for j in range(i, min(i + 10, last)):
                if word[j] not in t: break
                t = t[word[j]]
                if '#' in t:
                    last = j
                    break
            res = max(res, last - i)
        return res