"""
179. Largest Number


Input: [10,2]
Output: "210"
Example 2:

Input: [3,30,34,5,9]
Output: "9534330"
"""

# solution 1
class Comparable:
    # object that can be sorted thanks to magic methods.
    def __init__(self, num):
        self.value = str(num)
    def __lt__(self, other):
        # '82' is before '824' because '82|824' is greater than '824|82'
        return self.value + other.value > other.value + self.value
    def __gt__(self, other):
        return self.value + other.value < other.value + self.value
    def __eq__(self, other):
        return self.value + other.value == other.value + self.value


class Solution:
    def largestNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: str
        """
        numStrings = [Comparable(n) for n in nums]
        numStrings.sort()
        output = ''.join((e.value for e in numStrings))
        return output.lstrip('0') or '0'


class cmp:
    def __init__(self,value):
        self.value = str(value)
    def __lt__(self,other):
        return self.value + other.value < other.value + self.value
    def __gt__(self,other):
        return self.value + other.value > other.value + self.value
    def __eq__(self,other):
        return self.value + other.value == other.value + self.value
class Solution:
    def largestNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: str
        """
        numstring = [cmp(n) for n in nums]
        numstring.sort(reverse = True)
        if numstring[0].value.startswith("0"): return '0'
        return "".join(e.value for e in numstring)



# solution 2
class Solution:
    def largestNumber(self, A):
        """
        :type A: List[int]
        :rtype: str
        """
        A[:] = [str(x) for x in A] 
        A.sort(key=order_str)
        return ''.join(A).lstrip('0') or '0'

class order_str(str):
    def __lt__(x, y):
        return x+y > y+x   



# solution 3
class Solution:
    def largestNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: str
        """
        def bigger(a,b):
            i = 0
            while i<len(a) and i<len(b):
                if int(a[i]) > int(b[i]):
                    return 1
                if int(a[i]) < int(b[i]):
                    return -1
                i= i + 1
            if i==len(a) and i==len(b):
                return 1
            elif i==len(a):
                return bigger(a,b[i:])
            else:
                return bigger(a[i:],b)
        
        
        import functools
        nums = map(str, nums)
        nums = sorted(nums, key=functools.cmp_to_key(bigger), reverse=True)
        ans=''.join(nums)
        if int(ans) == 0:
            return "0"
        return(ans)


# solution 4
class LargerNumKey(str):
    def __lt__(x, y):
        return x+y > y+x
        
class Solution:
    def largestNumber(self, nums):
        largest_num = ''.join(sorted(map(str, nums), key=LargerNumKey))
        return '0' if largest_num[0] == '0' else largest_num