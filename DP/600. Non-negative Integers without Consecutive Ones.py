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
