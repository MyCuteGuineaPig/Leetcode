class Solution:
    def maxPalindromesAfterOperations(self, words: List[str]) -> int:
        count = Counter(c for s in words for c in s)
        length = sorted(map(len, words))
        pair = sum(c//2 for c in count.values())
        for i,a in enumerate(length):
            pair -= (a//2) 
            if pair < 0:
                return i 
        return len(words)