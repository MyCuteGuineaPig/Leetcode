"""
600. Non-negative Integers without Consecutive Ones

"""

class Solution:
    def findIntegers(self, num):
        """
        :type num: int
        :rtype: int
        """
        fb = [1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578];
        def dfs(num, index):
            if num<=2:
                return num+1
            for i in range(index,-1, -1):
                if num & (1<<i):
                    if i>0 and num&(1<<(i-1)):
                        return fb[i+1]
                    else:
                        return fb[i] + dfs(num & (~(1<<i)),i-2)
        return dfs(num,31)


class Solution:
    def findIntegers(self, num):
        """
        :type num: int
        :rtype: int
        """
        fb = [1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578];
        def dfs(num, index):
            if num<=2:
                return num+1
            for i in range(index,-1, -1):
                if num & (1<<i):
                    return fb[i+1] if i>0 and num&(1<<(i-1)) else fb[i] + dfs(num & (~(1<<i)),i-2)
        return dfs(num,31)


class Solution:
    def findIntegers(self, num):
        """
        :type num: int
        :rtype: int
        """
        fb = [1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578];
        digit = 30;
        prev_digit, res = 0, 0
        while digit>=0 :
            if num & (1<<digit):
                res += fb[digit]
                if prev_digit == 1:
                    return res
                prev_digit = 1
            else:
                prev_digit = 0
            digit -= 1
        return res + 1




class Solution:
    def findIntegers(self, num: int) -> int:
        bits = []

        while num:
            bits.append( num & 1)
            num = num >> 1
        n = len(bits)
        ones = [1]
        zeros = [1]
        for i in range(1, n):
            ones.append(zeros[-1])
            zeros.append(zeros[-1] + ones[-2])
            
        res = zeros[n-1] + ones[n-1]
        for i in range(n-2, -1, -1):
            if bits[i+1] == bits[i] == 1:
                break
            elif bits[i+1] == bits[i] == 0:
                res -= ones[i]
        return res
            

"""
num & 1 and num & 2 will check if num ends with 11 in binary.
Why can I use fibonacci numbers?
a(n) = the number of valid integers less than 2^n
a(5) = the number of valid integers less than 0b100000
It equals to the number of valid integers in [0b0, 0b10000[ and in [0b10000, 0b11000[.
The number of valid integers [0b0, 0b10000[, which is like '0b0XXXX', equals to a(4).
The number of valid integers [0b10000, 0b11000[, which is like '0b101XX', equals to a(3).
So a(5) = a(4) + a(3).
This rule is the same for other values of n, and it is the same as Fibonacci numbers recurrence relation definition.
"""

# Why num += 1?
# Question: result <= num
#   solved: result < num



class Solution:
    def findIntegers(self, num: int) -> int:
        x, y = 1, 2
        res = 0
        num += 1
        while num:
            if num & 1 and num & 2:
                res = 0
            res += x * (num & 1)
            num >>= 1
            x, y = y, x + y
        return res
            

"""
比如 1234

1234 = 0b10011010010, A = [1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0].


dp =    [[1, 1], 
         [1, 1], 
         [1, 2], 
         [3, 3], 
         [3, 5], 
         [3, 8], 
         [11, 13], 
         [11, 21], 
         [32, 34], 
         [55, 55], 
         [55, 89], 
         [55, 144], 
         [199, 233]]


dp[i][1] 表示 当最高位i位是1，所有的可能性
dp[i][0]

dp[i+2][0] = dp[i+1][A[i]] + A[i] * dp[i][i>0 and A[i-1]]
if A[i] = 0 and A[i-1] = 0:
    dp[i+2][0] = dp[i+1][0] 没有新加的可能性
if A[i] = 1 and A[i-1] = 1:
    dp[i+2][0] = dp[i+1][1] + dp[i][1]
    表示 11xxx 可以是 xxxx 和 10xxx 组合

if A[i] = 0 and A[i-1] = 1:
    dp[i+2][0] = dp[i+1][0]: 没有新加的可能性

if A[i] = 1 and A[i-1] = 0:
    dp[i+2][0] = dp[i+1][1] + dp[i][0]: 10xxx 可以是 xxxx, 也可以是 10xxx( dp[i][0])

"""
class Solution:
    def findIntegers(self, num: int) -> int:
        A = list(map(int, bin(num)[2:]))
        A = A[::-1]
        print(A)
        N = len(A)
        dp = [[0, 0] for _ in range(N+2)]
        dp[0] = dp[1] = [1, 1]

        for i in range(N):
            dp[i+2][0] = dp[i+1][A[i]] + A[i] * dp[i][i>0 and A[i-1]]
            dp[i+2][1] = dp[i+1][1] + dp[i][1]
        return dp[N+1][0]
