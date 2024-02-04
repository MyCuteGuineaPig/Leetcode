class Solution:
    def minimumTimeToInitialState(self, word: str, k: int) -> int:
        def kmp(word, k):
            n = len(word)
            kmp = [0,]*n
            j = 0
            for i in range(1, n):
                while j > 0 and word[i] != word[j]:
                        j = kmp[j-1]
                if word[i] == word[j]:
                    j+=1 
                kmp[i] = j
            return kmp
        prefix = kmp(word, k)
        n = len(word)
        v = prefix[-1]
        while v and (n-v) % k > 0:
            v = prefix[v-1]
        return (n-v) // k  + (1 if (n-v) % k else 0)


"""
看最后一位kmp 可以最大的prefix是几，如果即是suffix,又是prefix, 可以被k整除就是答案，


n = 13 , k = 2
a b c a b c e a b c a b c
0 0 0 1 2 3 0 1 2 3 4 5 6

j 最后是 6, 如果想保留abcabc
(13 - 6) % 2 == 1   ==》 j = kmp[j-1] = kmp[5] = 3

(13 - 3) % 2 == 0  可以保留 abc, 其他都剔除,  (13-3)/2 = 5



"""

class Solution:
    def minimumTimeToInitialState(self, word: str, k: int) -> int:
        n = len(word)
        kmp = [0,]*n
        j = 0
        for i in range(1, n):
            while j > 0 and word[i] != word[j]:
                    j = kmp[j-1]
            j = kmp[i] = j + (word[i] == word[j])
        while j and (n-j) % k > 0:
            j = kmp[j-1]
        return (n-j) // k  + (1 if (n-j) % k else 0)


class Solution:
    def minimumTimeToInitialState(self, word: str, k: int) -> int:
        return next(t for t in count(1) if word.startswith(word[t * k : ]))
