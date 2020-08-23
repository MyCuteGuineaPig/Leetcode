class Solution:
    def integerReplacement(self, n):
        """
        :type n: int
        :rtype: int
        """
        step = 0
        while n != 1: 
            if n == 3: return step + 2
            step += 1
            if n & 1:  
                n = n - 1 if ((n-1)& 3 == 0) else n + 1
            else: 
                n //= 2
        return step

#recursion
class Solution(object):
    def integerReplacement(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n == 1:
            return 0
        if n % 2:
            return 1 + min(self.integerReplacement(n+1), self.integerReplacement(n-1))
        else:
            return 1 + self.integerReplacement(n/2)


class Solution:
    def integerReplacement(self, n):
        k = 0
        while n!=1:
            #print (n,bin(n),bin(n)[-3:])
            if n%2==0:
                n//=2
            elif n!=3 and bin(n+1).count('1')<=bin(n-1).count('1'):
                n=n+1
            else:
                n=n-1
            k+=1
        return k