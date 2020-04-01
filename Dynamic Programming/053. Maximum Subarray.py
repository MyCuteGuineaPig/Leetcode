class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        for i in range(1, len(nums)):
            if nums[i-1] > 0:
                nums[i] += nums[i-1]
        return max(nums)

class Solution:
    # @param A, a list of integers
    # @return an integer
    # 6:57
    def maxSubArray(self, A):
        if not A:
            return 0

        curSum = maxSum = A[0]
        for num in A[1:]:
            curSum = max(num, curSum + num)
            maxSum = max(maxSum, curSum)

        return maxSum


#Divide Conquer
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        def divide_conquer(l,r):
            if l == r: return nums[l]
            m = (l + r )>>1
            leftmax = divide_conquer(l, m)
            rightmax = divide_conquer(m+1, r)
            
            lres, rres = nums[m], nums[m+1]
            tmp = 0 
            for i in reversed(nums[l:m+1]):
                tmp += i
                lres = max(lres, tmp)
            tmp = 0 
            for i in nums[m+1:r+1]:
                tmp += i 
                rres = max(rres, tmp)
            return max(leftmax, rightmax, lres + rres)
        return divide_conquer(0, len(nums)-1)


class Solution:
    def maxSubArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def divide_and_conquer(nums, i, j):
            if i == j-1:
                return nums[i],nums[i],nums[i],nums[i]
            
            # we will compute :
            # a which is max contiguous sum in nums[i:j] including the first value
            # m which is max contiguous sum in nums[i:j] anywhere 
            # b which is max contiguous sum in nums[i:j] including the last value
            # s which is the sum of all values in nums[i:j]
                
            # compute middle index to divide array in two halves
            i_mid = i+(j-i)//2
            
            # compute a, m, b, s for left half
            a1, m1, b1, s1 = divide_and_conquer(nums, i, i_mid)
            
            # compute a, m, b, s for right half
            a2, m2, b2, s2 = divide_and_conquer(nums, i_mid, j)
            
            # combine a, m, b, s values from left and right halves to form a, m, b, s for whole array (bottom up)
            a = max(a1, s1+a2)
            b = max(b2, s2+b1)
            m = max(m1,m2,b1+a2)
            s = s1+s2
            return a,m,b,s
                  
        _,m,_,_ = divide_and_conquer(nums, 0, len(nums))
        return m