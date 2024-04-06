class Solution:
    def maximumBooks(self, books: List[int]) -> int:
        n = len(books)

        # Helper function to calculate the sum of books in a given range [l, r]
        def calculateSum(l, r):
            """ 
            比如 r = 2,  l = 0, 
            [0,3,1,5,4]
            左侧实际应该是1，如果l = 0, 拿的book 就是-1, 不可以
            """

            min_cnt = min(books[r], r-l)
            return max((books[r] + (books[r]-min_cnt)) * (min_cnt+1)//2,0)

        stack = []
        dp = [0] * n

        for i in range(n):
            # While we cannot push i, we pop from the stack
            #print("i ",i, stack)
            while stack and books[stack[-1]] - stack[-1] >= books[i] - i :
                stack.pop()
            #print("after i ",i, stack)
            
            # Compute dp[i]
            if not stack:
                dp[i] = calculateSum(0, i)
            else:
                j = stack[-1]
                dp[i] = dp[j] + calculateSum(j + 1, i)

            # Push the current index onto the stack
            stack.append(i)

        # Return the maximum element in the dp array
        return max(dp)