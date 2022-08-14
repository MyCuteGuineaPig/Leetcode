class Solution:
    def countExcellentPairs(self, nums: List[int], k: int) -> int:
        dic = Counter(map(int.bit_count, set(nums)))
        return sum(v*s for m, v in dic.items() for j,s in dic.items() if m + j >= k )
    
    
class Solution:
    def countExcellentPairs(self, nums: List[int], k: int) -> int:
        hamming = sorted([self.hammingWeight(num) for num in set(nums)])
        ans = 0
        for h in hamming:
            ans += len(hamming) - bisect.bisect_left(hamming, k - h)
        return ans
        
    def hammingWeight(self, n):
        ans = 0
        while n:
            n &= (n - 1)
            ans += 1
        return ans


# Two pointer
class Solution:
    def countExcellentPairs(self, A: List[int], k: int) -> int:
        # Count number of bits in (n) in binary
        def numOfBits(n):
            ans = 0
            while n:
                ans += (n & 1)
                n >>= 1
            return ans
        
        # Sort the number of bits of each distinct number from A
        B = sorted([numOfBits(a) for a in set(A)])
        
        # Right pointer start at n - 1.
        n, j, ans = len(B), len(B) - 1, 0

        for i in range(n):
            # If the starting i, j don't meet the condition, continue for the next i.
            if B[i] + B[j] < k: 
                continue
            
            # Move until j = 0 or B[i] + B[j] < k
            while j >= 1 and B[i] + B[j - 1] >= k:
                j -= 1
                
            # All the number to the right of the pointer j (inclusive) make no less
            # sum of bits with B[i]
            ans += n - j
        
        return ans