 """
 368. Largest Divisible Subset

 """
 


class Solution:
    def largestDivisibleSubset(self, nums):
        if len(nums) == 0 : 
            return []
        nums.sort()
        dp = [0]*len(nums)
        prev = [-1]*len(nums)
        largestIndex = 0;
        for i in range(len(nums)):
            for j in range(0,i):
                if nums[i]%nums[j]==0 and dp[i] < dp[j]+1 :
                    dp[i] = dp[j]+1
                    prev[i] = j
            if dp[i] > dp[largestIndex]: 
                #print("  larget ",largestIndex)
                largestIndex = i
        
        #print(dp, prev,largestIndex)
        res, i = [], largestIndex
        while i!=-1 :
            res.append(nums[i])
            i = prev[i]
        return res

def largestDivisibleSubset(self, nums):
    S = {-1: set()}
    for x in sorted(nums):
        S[x] = max((S[d] for d in S if x % d == 0), key=len) | {x}
    return list(max(S.values(), key=len))

"""
My S[x] is the largest subset with x as the largest element,
 i.e., the subset of all divisors of x in the input. With S[-1] = emptyset as useful base case. Since divisibility is transitive, 
 a multiple x of some divisor d is also a multiple of all elements in S[d], 
 so it’s not necessary to explicitly test divisibility of x by all elements in S[d]. Testing x % d suffices.

While storing entire subsets isn’t super efficient, it’s also not that bad. To extend a subset, 
the new element must be divisible by all elements in it, meaning it must be at least twice as large as the largest element in it. 
So with the 31-bit integers we have here, the largest possible set has size 31 (containing all powers of 2).
"""

class Solution:
    def largestDivisibleSubset(self, nums):
        S = {1:{}}
        for i in sorted(nums):
            S[i] = max(S[d] for d in S if d % i == 0, key = len) | {i}
        return list(max(S, key = len))


class Solution(object):
    def largestDivisibleSubset(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        if not nums: return []
        nums.sort()
        d={}
        bestlen=1
        d[1]=[[nums[0]]]
        
        for i in nums[1:]:
            toadd=[]
            for j in range(bestlen,0,-1):
                for k in d[j]:
                    if i%k[-1]==0:
                        toadd=k+[i]
                        bestlen=max(bestlen,j+1)
                        break
                if toadd: break
            else:
                toadd=[i]
            if len(toadd) in d:
                d[len(toadd)].append(toadd)
            else:
                d[len(toadd)]=[toadd]
                
        return d[bestlen][0]