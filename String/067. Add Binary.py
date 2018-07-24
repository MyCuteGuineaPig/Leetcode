"""
67. Add Binary

"""


class Solution:
    def addBinary(self, a, b):
        """
        :type a: str
        :type b: str
        :rtype: str
        """
        i = len(a)-1; j = len(b)-1
        carry = 0
        res = ""
        while i >= 0 or j >= 0 or carry > 0:
            carry += ord(a[i]) - ord('0') if i >= 0 else 0
            carry += ord(b[j]) - ord('0') if j >= 0 else 0
            res+=str(carry%2)
            carry >>= 1
            i-=1
            j-=1
        return res[::-1]
            
class Solution:
    def addBinary(self, a, b):
        """
        :type a: str
        :type b: str
        :rtype: str
        """
        ## convert the number a and b into interger with base 2
        ## convert the sum of a and b into the binary string
        return bin(int(a,2) + int(b,2))[2:]

class Solution:
    def addBinary(self, a, b):
        """
        :type a: str
        :type b: str
        :rtype: str
        """
        return '{0:b}'.format(int(a, 2) + int(b, 2))

   class Solution:
        def addBinary(self, a, b):
            if len(a)==0: return b
            if len(b)==0: return a
            if a[-1] == '1' and b[-1] == '1':
                return self.addBinary(self.addBinary(a[0:-1],b[0:-1]),'1')+'0'
            if a[-1] == '0' and b[-1] == '0':
                return self.addBinary(a[0:-1],b[0:-1])+'0'
            else:
                return self.addBinary(a[0:-1],b[0:-1])+'1'