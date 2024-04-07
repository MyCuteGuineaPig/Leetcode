
class Solution:
    def totalStrength(self, strength: List[int]) -> int:
        mod, n = 10 ** 9 + 7, len(strength)
        
        # Get the first index of the non-larger value to strength[i]'s right.
        right_index = [n] * n
        stack = []
        for i in range(n):
            while stack and strength[stack[-1]] >= strength[i]:
                right_index[stack.pop()] = i
            stack.append(i)

        # Get the first index of the smaller value to strength[i]'s left.
        left_index = [-1] * n
        stack = []
        for i in range(n - 1, -1, -1):
            while stack and strength[stack[-1]] > strength[i]:
                left_index[stack.pop()] = i
            stack.append(i)
            
        # prefix sum of the prefix sum array of strength.
        presum_of_presum =  list(accumulate(accumulate(strength, initial = 0), initial = 0))
        answer = 0
        #print(presum_of_presum)
        #print(list(accumulate(strength, initial = 0)))
        # For each element in strength, we get the value of R_term - L_term.
        for i in range(n):
            # Get the left index and the right index.
            left_bound = left_index[i]
            right_bound = right_index[i]
            
            
            # Get the left_count and right_count (marked as L and R in the previous slides)
            left_count = i - left_bound
            right_count = right_bound - i
            #print(" i = ", i , " left_bound=", left_bound, " right_bound ", right_bound, "left_count", left_count, "right_count", right_count)
            
            # Get positive presum and the negative presum.
            neg_presum = (presum_of_presum[i + 1] - presum_of_presum[left_bound + 1]) % mod
            pos_presum = (presum_of_presum[right_bound + 1] - presum_of_presum[i + 1]) % mod
            
            # The total strength of all subarrays that have strength[i] as the minimum.
            answer += strength[i] * (pos_presum * left_count - neg_presum * right_count)
            answer %= mod
            
        return answer