"""
Basic Math
999....999 % 3 == 0
1000....000 % 3 == 1
a000....000 % 3 == a % 3
abcdefghijk % 3 == (a+b+c+..+i+j+k) % 3


Explanation
1. Calculate the sum of digits total = sum(A)
2. If total % 3 == 0, we got it directly
3. If total % 3 == 1 and we have one of 1,4,7 in A:
    we try to remove one digit of 1,4,7
4. If total % 3 == 2 and we have one of 2,5,8 in A:
    we try to remove one digit of 2,5,8
5. If total % 3 == 2:
    we try to remove two digits of 1,4,7
6. If total % 3 == 1:
    we try to remove two digits of 2,5,8
7. Submit

Complexity
Time O(nlogn), where I use quick sort.
We can also apply counting sort, so it will be O(n)
Space O(sort)
"""

class Solution:
    def largestMultipleOfThree(self, digits: List[int]) -> str:
        cc = collections.Counter(digits)
        tot = sum(digits)
        digits.sort(reverse=1)
        def f(a):
            if cc[a]:
                digits.remove(a)  
                cc[a]-=1
            if not digits:
                return ""
            if digits[0] == 0:
                return '0' 
            if sum(digits) % 3 == 0:  #如果digits 为空也可以返回
                return "".join(map(str, digits))
        
        if tot % 3 == 0:
            return f(-1)
        if tot % 3 == 1 and cc[1] + cc[4] + cc[7]:
            return f(1) or f(4) or f(7)
        if tot % 3 == 2 and cc[2] + cc[5] + cc[8]:
             return f(2) or f(5) or f(8)
        if tot % 3 == 2:
            return f(1) or f(1) or f(4) or f(4) or f(7) or f(7)
        return f(2) or f(2) or f(5) or f(5) or f(8) or f(8)
            
        

#Heap Solution                             
import heapq
class Solution:
    def largestMultipleOfThree(self, digits: List[int]) -> str:
        def dump(r: int) -> str:
            if r:
                if heaps[r]:
                    heapq.heappop(heaps[r])
                elif len(heaps[-r]) > 1: #比如r =  1, 没有除以3 余1的, 就pop 两个除以3余2的,  (2+2)%3 = 1, 
                    #同理如果没有除以 3余2的，就pop 两个除以3余1的
                    heapq.heappop(heaps[-r])
                    heapq.heappop(heaps[-r])
            if any(heaps):
                return str(int(''.join(sorted(sum(heaps, []), reverse=True))))
            return ''

        heaps, total = [[], [], []], 0
        for digit in digits:
            total += digit
            heapq.heappush(heaps[digit % 3], str(digit))
        return dump(total % 3)               

class Solution:
    def largestMultipleOfThree(self, d: List[int]) -> str:
        d1 = sorted([i for i in d if i%3 ==1])
        d2 = sorted([i for i in d if i%3 ==2])
        d3 = [i for i in d if i%3 ==0]
        if sum(d) % 3 == 1:
            if len(d1) != 0:
                res = d1[1:] + d2 + d3
            else:
                res = d2[2:]+ d3
        elif sum(d) % 3 == 2:
            if len(d2) != 0:
                res = d1 + d2[1:] + d3
            else:
                res = d1[2:] +d3
        else:
            res = d
        res.sort(reverse = True)
        if not res: return ''
        return str(int(''.join([str(i) for i in res])))